/*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#include "input.h"
#include "reportoutput.h"
#include "Primitive.h"
#include "validate_prim_toporel.h"
#include "Surface.h"
#include "Solid.h"
#include "COError.h"
#include <tclap/CmdLine.h>
#include <time.h>  
#include "nlohmann-json/json.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace val3dity;
using json = nlohmann::json;

std::string VAL3DITY_VERSION = "2.0.2";


std::string print_summary_validation(std::map<std::string, std::vector<Primitive*>>& dPrimitives, std::map<std::string, COError>& dCOerrors, IOErrors& ioerrs);
std::string unit_test(std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, COError>& dCOerrors, IOErrors& ioerrs);
void        write_report_json(json& jr, std::string ifile, std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, COError >& dCOerrors, double snap_tol, double overlap_tol, double planarity_d2p_tol, double planarity_n_tol, IOErrors ioerrs, bool onlyinvalid);
void        print_license();


class MyOutput : public TCLAP::StdOutput
{
public:
  
  virtual void usage(TCLAP::CmdLineInterface& c)
  {
    std::cout << "===== val3dity =====" << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::list<TCLAP::Arg*> args = c.getArgList();
    for (TCLAP::ArgListIterator it = args.begin(); it != args.end(); it++) {
      if ( ((*it)->getName() == "ishell") || ((*it)->getName() == "output_off") )
        continue;
      if ((*it)->getFlag() == "")
        std::cout << "\t--" << (*it)->getName() << std::endl;
      else
        std::cout << "\t-" << (*it)->getFlag() << ", --" << (*it)->getName() << std::endl;
      std::cout << "\t\t" << (*it)->getDescription() << std::endl;
    }
    std::cout << "==SOME EXAMPLES==" << std::endl;
    
    std::cout << "\tval3dity CityGMLinput.gml" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in CityGMLinput.gml" << std::endl;
    std::cout << "\t\tand outputs a summary per city object" << std::endl;
    
    std::cout << "\tval3dity input.json -r /home/elvis/temp/r" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in input.json (CityJSON file)" << std::endl;
    std::cout << "\t\tand outputs a detailed report '/home/elvis/temp/r/report.html'" << std::endl;
    
    std::cout << "\tval3dity input.gml --overlap_tol 0.05" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in input.gml," << std::endl;
    std::cout << "\t\ta tolerance of 0.05 unit is used for the CompositeSolids and BuildingParts" << std::endl;
    
    std::cout << "\tval3dity input.json --verbose" << std::endl;
    std::cout << "\t\tAll details of the validation are printed out" << std::endl;
    
    std::cout << "\tval3dity input.obj" << std::endl;
    std::cout << "\t\tValidates the geometries in input.obj as if they were a Solid (default)" << std::endl;
    
    std::cout << "\tval3dity input.off -p MultiSurface" << std::endl;
    std::cout << "\t\tValidates the geometries in input.off as a MultiSurface" << std::endl;
    
    std::cout << "\tval3dity input.gml --snap_tol 0.1" << std::endl;
    std::cout << "\t\tThe vertices in input.gml closer than 0.1unit are snapped together" << std::endl;
  }

  virtual void failure(TCLAP::CmdLineInterface& c, TCLAP::ArgException& e)
  {
    std::cout << "ERROR: " << e.argId() << std::endl; 
    std::cout << "       " << e.error() << endl;
    std::cout << std::endl;
    std::cout << "USAGE: val3dity [OPTION] myinput.json" << std::endl;
    std::cout << std::endl;
    std::cout << "Try `val3dity --help` for more options" << std::endl;
    exit(1);
  }

};


int main(int argc, char* const argv[])
{
  IOErrors ioerrs;
  std::streambuf* savedBufferCLOG;
  std::ofstream mylog;

  //-- tclap options
  std::vector<std::string> primitivestovalidate;
  primitivestovalidate.push_back("Solid");  
  primitivestovalidate.push_back("CompositeSurface");   
  primitivestovalidate.push_back("MultiSurface");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);

  TCLAP::CmdLine cmd("Allowed options", ' ', VAL3DITY_VERSION);
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::UnlabeledValueArg<std::string>   inputfile(
                                              "inputfile", 
                                              "input file in either GML, CityJSON, OBJ, or OFF",
                                              true, 
                                              "", 
                                              "string");
    TCLAP::MultiArg<std::string>            ishellfiles(
                                              "", 
                                              "ishell", 
                                              "one interior shell (in POLY format only; more than one possible)",
                                              false, 
                                              "string");
    TCLAP::ValueArg<std::string>            report("r",
                                              "report",
                                              "output report in HTML format",
                                              false,
                                              "",
                                              "string");    
    TCLAP::ValueArg<std::string>            report_json("",
                                              "report_json",
                                              "output report in JSON format",
                                              false,
                                              "",
                                              "string");
    TCLAP::ValueArg<std::string>            primitives("p",
                                              "primitive",
                                              "which geometric primitive to validate <Solid|CompositeSurface|MultiSurface>",
                                              false,
                                              "Solid",
                                              &primVals);
    TCLAP::SwitchArg                        verbose("",
                                              "verbose",
                                              "verbose output",
                                              false);
    TCLAP::SwitchArg                        license("",
                                              "license",
                                              "see the software license",
                                              false);
    TCLAP::SwitchArg                        unittests("",
                                              "unittests",
                                              "unit tests output",
                                              false);
    TCLAP::SwitchArg                        onlyinvalid("",
                                              "onlyinvalid",
                                              "only invalid primitives are reported",
                                              false);
    TCLAP::SwitchArg                        ignore204("",
                                              "ignore204",
                                              "ignore error 204",
                                              false);    
    TCLAP::SwitchArg                        geom_is_sem_surfaces("",
                                              "geom_is_sem_surfaces",
                                              "geometry of a CityGML object is formed by its semantic surfaces",
                                              false);
    TCLAP::ValueArg<std::string>            output_off("",
                                              "output_off",
                                              "output each shell/surface in OFF format",
                                              false,
                                              "",
                                              "string");        
    TCLAP::ValueArg<double>                 snap_tol("",
                                              "snap_tol",
                                              "tolerance for snapping vertices in GML (default=0.001; no-snapping=-1)",
                                              false,
                                              0.001,
                                              "double");
    TCLAP::ValueArg<double>                 overlap_tol("",
                                              "overlap_tol",
                                              "tolerance for testing overlap CompositeSolids and BuildingParts (default=0.0)",
                                              false,
                                              -1,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_d2p_tol("",
                                              "planarity_d2p_tol",
                                              "tolerance for planarity distance_to_plane (default=0.01)",
                                              false,
                                              0.01,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_n_tol("",
                                              "planarity_n_tol",
                                              "tolerance for planarity based on normals deviation (default=20.0degree)",
                                              false,
                                              20.0,
                                              "double");

    cmd.add(planarity_d2p_tol);
    cmd.add(planarity_n_tol);
    cmd.add(snap_tol);
    cmd.add(overlap_tol);
    cmd.add(verbose);
    cmd.add(primitives);
    cmd.add(geom_is_sem_surfaces);
    cmd.add(ignore204);
    cmd.add(unittests);
    cmd.add(onlyinvalid);
    cmd.add(output_off);
    // cmd.add(inputfile);
    // cmd.add(license);
    cmd.xorAdd( inputfile, license );
    cmd.add(ishellfiles);
    cmd.add(report);
    cmd.add(report_json);
    cmd.parse( argc, argv );

    //-- map with Primitives
    //-- ["Primitives"] --> [] if there are no CityObjects, thus dPrimitives.size() == 1
    //-- ["Building|id2"] --> [] if there are CityObjects
    std::map<std::string, std::vector<Primitive*>> dPrimitives;
    //-- if a CO has errors specific to it (6xx), then its key is also in that dico
    std::map<std::string, COError> dCOerrors;
    
    InputTypes inputtype = OTHER;
    std::string extension = inputfile.getValue().substr(inputfile.getValue().find_last_of(".") + 1);
    if ( (extension == "gml") || (extension == "GML") || (extension == "xml") || (extension == "XML") ) 
      inputtype = GML;
    else if ( (extension == "poly") || (extension == "POLY") ) 
      inputtype = POLY;    
    else if ( (extension == "json") || (extension == "JSON") ) 
      inputtype = JSON;
    else if ( (extension == "obj") || (extension == "OBJ") ) 
      inputtype = OBJ;
    else if ( (extension == "off") || (extension == "OFF") ) 
      inputtype = OFF;

    //-- if verbose == false then log to a file
    if (verbose.getValue() == false)
    {
      savedBufferCLOG = clog.rdbuf();
      mylog.open("val3dity.log");
      std::clog.rdbuf(mylog.rdbuf());
    }
    if (license.getValue() == true)
    {
      print_license();
      if (verbose.getValue() == false)
      {
        clog.rdbuf(savedBufferCLOG);
        mylog.close();
      }
      return(0);
    }
    
    if (inputtype == OTHER) {
      std::stringstream ss;
      ss << "Input file (" << inputfile.getValue() << ") not supported.";
      ioerrs.add_error(901, ss.str());
    }

    Primitive3D prim3d;
    if ( (inputtype == JSON) || (inputtype == GML) )
    {
      prim3d = ALL;
    }
    else {
      if (primitives.getValue() == "Solid")
        prim3d = SOLID;
      else if (primitives.getValue() == "MultiSurface")
        prim3d = MULTISURFACE;
      else if (primitives.getValue() == "CompositeSurface")
        prim3d = COMPOSITESURFACE;
      if ((prim3d == COMPOSITESURFACE) && (ishellfiles.getValue().size() > 0))
        ioerrs.add_error(903, "POLY files having inner shells cannot be validated as CompositeSurface (only Solids)");
    }

    std::string licensewarning =
    "---\nval3dity Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  \n"
    "This program comes with ABSOLUTELY NO WARRANTY.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions; for details run val3dity with the '--license' option.\n---";
    std::cout << licensewarning << std::endl;


    if (ioerrs.has_errors() == false)
    {
      if (inputtype == GML)
      {
        try
        {
          read_file_gml(inputfile.getValue(), 
                        dPrimitives,
                        ioerrs, 
                        snap_tol.getValue(),
                        geom_is_sem_surfaces.getValue());
          if (ioerrs.has_errors() == true) {
            std::cout << "Errors while reading the input file, aborting." << std::endl;
            std::cout << ioerrs.get_report_text() << std::endl;
          }
          if (ishellfiles.getValue().size() > 0)
          {
            std::cout << "No inner shells allowed when GML file used as input." << std::endl;
            ioerrs.add_error(901, "No inner shells allowed when GML file used as input.");
          }
        }
        catch (int e)
        {
          if (e == 901)
            ioerrs.add_error(901, "Invalid GML structure, or that particular construction of GML is not supported yet. Please report at https://github.com/tudelft3d/val3dity/issues and provide the file.");
        }
      }
      else if (inputtype == JSON)
      {
        read_file_cityjson(inputfile.getValue(), 
                           dPrimitives,
                           ioerrs, 
                           snap_tol.getValue());
        if (ioerrs.has_errors() == true) {
          std::cout << "Errors while reading the input file, aborting." << std::endl;
          std::cout << ioerrs.get_report_text() << std::endl;
        }
        if (ishellfiles.getValue().size() > 0)
        {
          std::cout << "No inner shells allowed when GML file used as input." << std::endl;
          ioerrs.add_error(901, "No inner shells allowed when GML file used as input.");
        }
      }
      else if (inputtype == POLY)
      {
        Surface* sh = read_file_poly(inputfile.getValue(), 0, ioerrs);
        if ( (ioerrs.has_errors() == false) & (prim3d == SOLID) )
        {
          Solid* s = new Solid;
          s->set_oshell(sh);
          int sid = 1;
          for (auto ifile : ishellfiles.getValue())
          {
            Surface* sh = read_file_poly(ifile, sid, ioerrs);
            if (ioerrs.has_errors() == false)
            {
              s->add_ishell(sh);
              sid++;
            }
          }
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(s);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
        {
          CompositeSurface* cs = new CompositeSurface;
          cs->set_surface(sh);
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(cs);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == MULTISURFACE) )
        {
          MultiSurface* ms = new MultiSurface;
          ms->set_surface(sh);
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(ms);
        }      
      }
      else if (inputtype == OFF)
      {
        Surface* sh = read_file_off(inputfile.getValue(), 0, ioerrs);
        if ( (ioerrs.has_errors() == false) & (prim3d == SOLID) )
        {
          Solid* s = new Solid;
          s->set_oshell(sh);
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(s);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
        {
          CompositeSurface* cs = new CompositeSurface;
          cs->set_surface(sh);
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(cs);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == MULTISURFACE) )
        {
          MultiSurface* ms = new MultiSurface;
          ms->set_surface(sh);
          if (ioerrs.has_errors() == false)
            dPrimitives["Primitives"].push_back(ms);
        }
      }    
      else if (inputtype == OBJ)
      {
        read_file_obj(dPrimitives,
                      inputfile.getValue(), 
                      prim3d,
                      ioerrs, 
                      snap_tol.getValue());
        if (ioerrs.has_errors() == true) {
          std::cout << "Errors while reading the input file, aborting." << std::endl;
          std::cout << ioerrs.get_report_text() << std::endl;
        }
        if (ishellfiles.getValue().size() > 0)
        {
          std::cout << "No inner shells allowed when GML file used as input." << std::endl;
          ioerrs.add_error(901, "No inner shells allowed when GML file used as input.");
        }
      }
    }

    if (ioerrs.has_errors() == false) 
    {
      std::cout << "Primitive(s) validated: ";
      if (prim3d == SOLID)        
        std::cout << "Solid" << std::endl;
      else if (prim3d == MULTISURFACE)        
        std::cout << "MultiSurface" << std::endl;
      else if (prim3d == COMPOSITESURFACE)        
        std::cout << "CompositeSurface" << std::endl;
      else
        std::cout << "All" << std::endl;
        std::cout << "(CityGML/CityJSON have all their 3D primitives validated)" << std::endl;
    }
    double planarity_n_tol_updated = planarity_n_tol.getValue();
    //-- report on parameters used
    if (ioerrs.has_errors() == false)
    {
      if (ignore204.getValue() == true)
        planarity_n_tol_updated = 180.0;
      std::cout << "Parameters used for validation:" << std::endl;
      if (snap_tol.getValue() < 1e-8)
        std::cout << "   snap_tol"    << setw(22)  << "none" << std::endl;
      else
        std::cout << "   snap_tol"    << setw(22)  << snap_tol.getValue() << std::endl;
      std::cout << "   planarity_d2p_tol"     << setw(13)  << planarity_d2p_tol.getValue() << std::endl;
      std::cout << "   planarity_n_tol"       << setw(15) << planarity_n_tol_updated << std::endl;
      if (overlap_tol.getValue() < 1e-8)
        std::cout << "   overlap_tol" << setw(19)  << "none" << std::endl;
      else
        std::cout << "   overlap_tol" << setw(19)  << overlap_tol.getValue() << std::endl;
    }

    //-- now the validation starts
    if ( (dPrimitives.empty() == false) && (ioerrs.has_errors() == false) )
    {
      // std::cout << "Validating " << dPrimitives.size();
      int i = 1;
      for (auto& co : dPrimitives)
      {
        if ( (i % 10 == 0) && (verbose.getValue() == false) )
          printProgressBar(100 * (i / double(dPrimitives.size())));
        i++;
        std::clog << std::endl << "######### Validating " << co.first << " #########" << std::endl;
        bool bValid = true;
        COError coerrs;
        if (co.second.empty() == true) {
          coerrs.add_error(609, "City Object has no geometry defined.", "");
          dCOerrors[co.first] = coerrs;
        }
        for (auto& p : co.second)
        {
          std::clog << "======== Validating Primitive ========" << std::endl;
          switch(p->get_type())
          {
            case 0: std::clog << "Solid"             << std::endl; break;
            case 1: std::clog << "CompositeSolid"    << std::endl; break;
            case 2: std::clog << "MultiSolid"        << std::endl; break;
            case 3: std::clog << "CompositeSurface"  << std::endl; break;
            case 4: std::clog << "MultiSurface"      << std::endl; break;
            case 5: std::clog << "All"               << std::endl; break;
          }
          std::clog << "id: " << p->get_id() << std::endl;
          std::clog << "--" << std::endl;
          if (p->validate(planarity_d2p_tol.getValue(), planarity_n_tol_updated, overlap_tol.getValue()) == false)
          {
            std::clog << "======== INVALID ========" << std::endl;
            bValid = false;
          }
          else
            std::clog << "========= VALID =========" << std::endl;
        }
        //-- if Building then do extra checks  
        if ( (bValid == true) && 
             (co.first.find("Building|") != std::string::npos) &&
             (co.second.size() > 1)
           )
        {
          std::clog << "--- Interactions between BuildingParts ---" << std::endl;
          if (do_primitives_overlap(co.second, coerrs, overlap_tol.getValue()) == true)
          {
            std::clog << "Error: overlapping building parts" << std::endl;
            dCOerrors[co.first] = coerrs;
          }
        }
        std::clog << "#########################################" << std::endl;
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }

    //-- summary of the validation
    std::cout << "\n" << print_summary_validation(dPrimitives, dCOerrors, ioerrs) << std::endl;        

   //-- output shells/surfaces in OFF format
    if (output_off.getValue() != "") 
    {
      std::cout << std::endl << std::endl;
      boost::filesystem::path outpath(output_off.getValue());
      if (boost::filesystem::exists(outpath.parent_path()) == false)
        std::cout << "Error OFF output: file " << outpath << " impossible to create, wrong path." << std::endl;
      else {
        if (boost::filesystem::exists(outpath) == false)
          boost::filesystem::create_directory(outpath);
        std::cout << "OFF files saved to: " << outpath << std::endl;
        for (auto& co : dPrimitives)
        {
          std::string coid = co.first.substr(co.first.find_first_of("|") + 1);
          int noprim = 0;
          for (auto& p : co.second)
          {
            std::string theid = coid + "." + std::to_string(noprim);
            if (p->get_type() == SOLID)
            {
              boost::filesystem::path outfile = outpath / (theid + ".0.off");
              std::ofstream o(outfile.string());
              Solid* ts = dynamic_cast<Solid*>(p);
              o << ts->get_off_representation(0) << std::endl;                                
              o.close();
              for (int i = 1; i <= ts->num_ishells(); i++)
              {
                outfile = outpath / (theid + "." + std::to_string(i) + ".off");
                o.open(outfile.string());
                o << ts->get_off_representation(1) << std::endl;                                
                o.close();
              }
            }
            else if (p->get_type() == MULTISURFACE)
            {
              boost::filesystem::path outfile = outpath / (theid + ".off");
              std::ofstream o(outfile.string());
              MultiSurface* ts = dynamic_cast<MultiSurface*>(p);
              o << ts->get_off_representation() << std::endl;                                
              o.close();
            }
            else if (p->get_type() == COMPOSITESURFACE)
            {
              boost::filesystem::path outfile = outpath / (theid + ".off");
              std::ofstream o(outfile.string());
              CompositeSurface* ts = dynamic_cast<CompositeSurface*>(p);
              o << ts->get_off_representation() << std::endl;                                
              o.close();
            }            
            else {
              std::cout << "OFF OUTPUT: these primitive types are not supported (yet). Sorry." << std::endl;
            }
            noprim++;
          }
        }
      }
      std::cout << std::endl;
    }

    //-- output report
    if ( (report.getValue() != "") || (report_json.getValue() != "") )
    {
      json jr;
      write_report_json(jr, 
                       inputfile.getValue(),
                       dPrimitives,
                       dCOerrors,
                       snap_tol.getValue(),
                       overlap_tol.getValue(),
                       planarity_d2p_tol.getValue(),
                       planarity_n_tol_updated,
                       ioerrs,
                       onlyinvalid.getValue());
      // HTML report
      if (report.getValue() != "") {
        boost::filesystem::path outpath(report.getValue());
        if (boost::filesystem::exists(outpath.parent_path()) == false)
          std::cout << "Error: file " << outpath << " impossible to create, wrong path." << std::endl;
        else {
          if (boost::filesystem::exists(outpath) == false)
            boost::filesystem::create_directory(outpath);
          boost::filesystem::path outfile = outpath / "report.html";
          std::ofstream o(outfile.string());
          o << indexhtml << std::endl;                                
          std::cout << "Full validation report (in HTML format) saved to " << outfile << std::endl;
          o.close();

          outfile = outpath / "report.js";
          o.open(outfile.string());
          o << "var report =" << jr << std::endl;                                
          o.close();

          outfile = outpath / "CityObjects.html";
          o.open(outfile.string());
          o << cityobjectshtml << std::endl;                                
          o.close();

          outfile = outpath / "Primitives.html";
          o.open(outfile.string());
          o << primitiveshtml << std::endl;                                
          o.close();
          
          outfile = outpath / "treeview.js";
          o.open(outfile.string());
          o << treeviewjs << std::endl;                                
          o.close();

          outfile = outpath / "val3dityconfig.js";
          o.open(outfile.string());
          o << val3dityconfigjs << std::endl;                                
          o.close();
          
          outfile = outpath / "index.css";
          o.open(outfile.string());
          o << indexcss << std::endl;                                
          o.close();
        }
      }
      // JSON report
      if (report_json.getValue() != ""){
        boost::filesystem::path outpath(report_json.getValue());
        if (boost::filesystem::exists(outpath.parent_path()) == false)
          std::cout << "Error: file " << outpath << " impossible to create, wrong path." << std::endl;
        else {
          if (boost::filesystem::extension(outpath) != ".json")
            outpath += ".json";
          std::ofstream o(outpath.string());
          o << jr.dump(2) << std::endl;                                
          std::cout << "Full validation report (in JSON format) saved to " << outpath << std::endl;
        }
      }
    }
    else
      std::cout << "-->The validation report wasn't saved, use option '--report' (or '--report_json')." << std::endl;

    //-- unittests 
    if (unittests.getValue() == true)
      std::cout << "\n" << unit_test(dPrimitives, dCOerrors, ioerrs) << std::endl;

    if (verbose.getValue() == false)
    {
      clog.rdbuf(savedBufferCLOG);
      mylog.close();
    }
    return(0);
  }
  catch (TCLAP::ArgException &e) 
  {
    std::cout << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
}


std::string unit_test(std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, COError >& dCOerrors, IOErrors& ioerrs)
{
  std::stringstream ss;
  ss << std::endl;
  std::set<int> theerrors;
  if (ioerrs.has_errors() == true)
  {
    for (auto& each : ioerrs.get_unique_error_codes())
      theerrors.insert(each);
  }

  for (auto& co : dPrimitives)
  {
    if (dCOerrors.find(co.first) != dCOerrors.end())
      for (auto& each : dCOerrors[co.first].get_unique_error_codes())
        theerrors.insert(each);
    for (auto& p : co.second)
      for (auto& each : p->get_unique_error_codes())
        theerrors.insert(each);
  }
  if (theerrors.size() > 0)
  {
    ss << "@INVALID ";
    for (auto each : theerrors)
      ss << each << " ";
  }
  else {
    ss << "@VALID";
  }
  ss << std::endl;
  return ss.str();
}


std::string print_summary_validation(std::map<std::string,std::vector<Primitive*>>& dPrimitives, std::map<std::string, COError>& dCOerrors, IOErrors& ioerrs)
{
  std::stringstream ss;
  ss << std::endl;
  int noprim = 0;
  for (auto& co : dPrimitives)
    for (auto& p : co.second)
      noprim++;
    
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  //-- if a CityGML/CityJSON report also CityObjects
  if (!( (dPrimitives.size() == 1) && (dPrimitives.find("Primitives") != dPrimitives.end()) ))
  {
    int coInvalid = 0;
    for (auto& co : dPrimitives)
    {
      if (dCOerrors.find(co.first) != dCOerrors.end())
      {
        coInvalid++;
        continue;
      }
      for (auto& p : co.second)
      {
        if (p->is_valid() == false)
        {
          coInvalid++;
          break;
        }
      }
    }
    ss << "Total # of CityObjects: " << setw(7) << dPrimitives.size() << std::endl;
    float percentage;
    if (dPrimitives.size()  == 0)
      percentage = 0;
    else
      percentage = 100 * (coInvalid / float(dPrimitives.size()));
    ss << "# valid: " << setw(22) << dPrimitives.size() - coInvalid;
    if (dPrimitives.size() == 0)
      ss << " (" << 0 << "%)" << std::endl;
    else
      ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
    ss << "# invalid: " << setw(20) << coInvalid;
    ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
    ss << "+++++" << std::endl;
  }
  ss << "Total # of primitives: " << setw(8) << noprim << std::endl;
  int bValid = 0;
  for (auto& co : dPrimitives)
    for (auto& p : co.second)
      if (p->is_valid() == true)
        bValid++;
  float percentage;
  if (noprim  == 0)
    percentage = 0;
  else
    percentage = 100 * ((noprim - bValid) / float(noprim));
  ss << "# valid: " << setw(22) << bValid;
  if (noprim == 0)
    ss << " (" << 0 << "%)" << std::endl;
  else
    ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(20) << (noprim - bValid);
  ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
  //-- overview of errors
  std::map<int,int> errors;
  for (auto& co : dPrimitives) {
    if (dCOerrors.find(co.first) != dCOerrors.end())
      for (auto& code : dCOerrors[co.first].get_unique_error_codes())
        errors[code] = 0;
    for (auto& p : co.second)
      for (auto& code : p->get_unique_error_codes())
        errors[code] = 0;
  }
  for (auto& co : dPrimitives) {
    if (dCOerrors.find(co.first) != dCOerrors.end())
      for (auto& code : dCOerrors[co.first].get_unique_error_codes())
        errors[code] += 1;
    for (auto& p : co.second)
      for (auto& code : p->get_unique_error_codes())
        errors[code] += 1;
  }

  if ( (errors.size() > 0) || (ioerrs.has_errors() == true) )
  {
    ss << "+++++" << std::endl;
    ss << "Errors present:" << std::endl;
    for (auto e : errors)
    {
      ss << "  " << e.first << " -- " << errorcode2description(e.first) << std::endl;
      ss << setw(11) << "(" << e.second << " primitives)" << std::endl;
    }
    for (auto& e : ioerrs.get_unique_error_codes())
    {
      ss << "  " << e << " -- " << errorcode2description(e) << std::endl;
    }
  }

  ss << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  return ss.str();
}


void print_license() {
  std::string thelicense =
    "\nval3dity\n\n"
    "Copyright (C) 2011-2017  3D geoinformation research group, TU Delft\n\n"
    "val3dity is free software: you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation, either version 3 of the License, or\n"
    "(at your option) any later version.\n\n"
    "val3dity is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU General Public License for more details.\n\n"
    "A copy of the GNU General Public License is available at\n"
    "<http://www.gnu.org/licenses/> or\n"
    "<https://github.com/tudelft3d/val3dity/blob/master/LICENSE\n\n"
    "For any information or further details about the use of val3dity, contact:\n"
    "Hugo Ledoux \n"
    "<h.ledoux@tudelft.nl>\n"
    "Faculty of Architecture & the Built Environment\n"
    "Delft University of Technology\n"
    "Julianalaan 134, Delft 2628BL, the Netherlands\n";
  std::cout << thelicense << std::endl;
}

void write_report_json(json& jr,
                       std::string ifile, 
                       std::map<std::string, std::vector<Primitive*> >& dPrimitives,
                       std::map<std::string, COError >& dCOerrors,
                       double snap_tol,
                       double overlap_tol,
                       double planarity_d2p_tol,
                       double planarity_n_tol,
                       IOErrors ioerrs,
                       bool onlyinvalid)
{
  jr["type"] = "val3dity report";
  jr["val3dity_version"] = VAL3DITY_VERSION; 
  jr["input_file"] = ifile;
  //-- time
  std::time_t rawtime;
  struct tm * timeinfo;
  std::time (&rawtime);
  timeinfo = std::localtime ( &rawtime );
  char buffer[80];
  std::strftime(buffer, 80, "%c %Z", timeinfo);
  jr["time"] = buffer;
  //-- user-defined param
  jr["snap_tol"] = snap_tol;
  jr["overlap_tol"] = overlap_tol;
  jr["planarity_d2p_tol"] = planarity_d2p_tol;
  jr["planarity_n_tol"] = planarity_n_tol;
  int noprim = 0;
  for (auto& co : dPrimitives)
    for (auto& p : co.second)
      noprim++;
  jr["total_primitives"] = noprim;
  int bValid = 0;
  for (auto& co : dPrimitives)
    for (auto& p : co.second)
      if (p->is_valid() == true)
        bValid++;
  jr["valid_primitives"] = bValid;
  jr["invalid_primitives"] = noprim - bValid;
  //-- overview of errors
  // "overview-errors": [101, 203],
  // "overview-errors-primitives": [5, 1],
  std::map<int,int> errors;
  for (auto& co : dPrimitives) {
    if (dCOerrors.find(co.first) != dCOerrors.end())
      for (auto& code : dCOerrors[co.first].get_unique_error_codes())
        errors[code] = 0;
    for (auto& p : co.second)
      for (auto& code : p->get_unique_error_codes())
        errors[code] = 0;
  }
  for (auto& co : dPrimitives) {
    if (dCOerrors.find(co.first) != dCOerrors.end())
      for (auto& code : dCOerrors[co.first].get_unique_error_codes())
        errors[code] += 1;
    for (auto& p : co.second)
      for (auto& code : p->get_unique_error_codes())
        errors[code] += 1;
  }
  jr["overview_errors"];    
  jr["overview_errors_no_primitives"];    
  for (auto e : errors)
  {
    jr["overview_errors"].push_back(e.first);
    jr["overview_errors_no_primitives"].push_back(e.second);
  }
  for (auto& e : ioerrs.get_unique_error_codes())
  {
    jr["overview_errors"].push_back(e);
    jr["overview_errors_no_primitives"].push_back(-1);
  }
  
  //-- if a CityGML/CityJSON report also CityObjects
  if (!( (dPrimitives.size() == 1) && (dPrimitives.find("Primitives") != dPrimitives.end()) ))
  {
    int coInvalid = 0;
    for (auto& co : dPrimitives)
    {
      if (dCOerrors.find(co.first) != dCOerrors.end())
      {
        coInvalid++;
        continue;
      }
      for (auto& p : co.second)
      {
        if (p->is_valid() == false)
        {
          coInvalid++;
          break;
        }
      }
    }
    jr["total_cityobjects"] = dPrimitives.size();
    jr["valid_cityobjects"] = dPrimitives.size() - coInvalid;
    jr["invalid_cityobjects"] = coInvalid;
  }
  else
  {
    jr["total_cityobjects"] = 0;
    jr["valid_cityobjects"] = 0;
    jr["invalid_cityobjects"] = 0;
  }
  jr["InputErrors"];
  jr["CityObjects"];
  jr["Primitives"];
  if (ioerrs.has_errors() == true)
  {
    jr["InputErrors"] = ioerrs.get_report_json();
  }
  else
  {
    //-- only primitives (no CityObjects)
    if ( (dPrimitives.size() == 1) && (dPrimitives.find("Primitives") != dPrimitives.end()) )
    {
      for (auto& p : dPrimitives["Primitives"])
        if ( !((onlyinvalid == true) && (p->is_valid() == true)) ) 
          jr["Primitives"].push_back(p->get_report_json());
    }
    else //-- with CityObjects (CityJSON + CityGML)
    {
      for (auto& co : dPrimitives)
      {
        json j;
        std::string cotype = co.first.substr(0, co.first.find_first_of("|"));
        std::string coid = co.first.substr(co.first.find_first_of("|") + 1);
        bool isValid = true;
        j["type"] = cotype;
        j["errors"];
        if (dCOerrors.find(co.first) != dCOerrors.end())
        {
          for (auto& each: dCOerrors[co.first].get_report_json())
          {
            j["errors"].push_back(each);
            isValid = false;
          }

        }
        for (auto& p : co.second)
        {
          if ( !((onlyinvalid == true) && (p->is_valid() == true)) )
          {
            j["primitives"].push_back(p->get_report_json());
            if (p->is_valid() == false)
              isValid = false;
          }
        }
        j["validity"] = isValid;
        j["id"] = coid;
        jr["CityObjects"].push_back(j);
      }
    }
  }
}



