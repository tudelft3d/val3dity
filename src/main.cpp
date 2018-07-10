/*
  val3dity 

  Copyright (c) 2011-2018, 3D geoinformation research group, TU Delft  

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
#include "Surface.h"
#include "MultiSurface.h"
#include "CompositeSurface.h"
#include "Solid.h"
#include "Feature.h"
#include "CityObject.h"
#include "GenericObject.h"


#include "validate_prim_toporel.h"

#include <tclap/CmdLine.h>
#include <time.h>  
#include "nlohmann-json/json.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace val3dity;
using json = nlohmann::json;

std::string VAL3DITY_VERSION = "2.1.1";


std::string print_summary_validation(std::vector<Feature*>& lsFeatures, IOErrors& ioerrs);
std::string unit_test(std::vector<Feature*>& lsFeatures, IOErrors& ioerrs);
void        get_report_json(json& jr, std::string ifile, std::vector<Feature*>& lsFeatures, double snap_tol, double overlap_tol, double planarity_d2p_tol, double planarity_n_tol, IOErrors ioerrs, bool onlyinvalid);
void        print_license();
void        write_report_html(json& jr, std::string report);
void        write_report_json(json& jr, std::string report);


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

    //-- vector with Features: CityObject, GenericObject, 
    //-- or IndoorModel (or others in the future)
    std::vector<Feature*> lsFeatures;
    
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
    "---\nval3dity Copyright (c) 2011-2018, 3D geoinformation research group, TU Delft  \n"
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
                        lsFeatures,
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
                           lsFeatures,
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
        GenericObject* o = new GenericObject("none");
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
            o->add_primitive(s);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
        {
          CompositeSurface* cs = new CompositeSurface;
          cs->set_surface(sh);
          if (ioerrs.has_errors() == false)
            o->add_primitive(cs);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == MULTISURFACE) )
        {
          MultiSurface* ms = new MultiSurface;
          ms->set_surface(sh);
          if (ioerrs.has_errors() == false)
            o->add_primitive(ms);
        }
        lsFeatures.push_back(o);      
      }
      else if (inputtype == OFF)
      {
        GenericObject* o = new GenericObject("none");
        Surface* sh = read_file_off(inputfile.getValue(), 0, ioerrs);
        if ( (ioerrs.has_errors() == false) & (prim3d == SOLID) )
        {
          Solid* s = new Solid;
          s->set_oshell(sh);
          if (ioerrs.has_errors() == false)
            o->add_primitive(s);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
        {
          CompositeSurface* cs = new CompositeSurface;
          cs->set_surface(sh);
          if (ioerrs.has_errors() == false)
            o->add_primitive(cs);
        }
        else if ( (ioerrs.has_errors() == false) & (prim3d == MULTISURFACE) )
        {
          MultiSurface* ms = new MultiSurface;
          ms->set_surface(sh);
          if (ioerrs.has_errors() == false)
            o->add_primitive(ms);
        }
        lsFeatures.push_back(o);
      }    
      else if (inputtype == OBJ)
      {
        read_file_obj(lsFeatures,
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

    double planarity_n_tol_updated = planarity_n_tol.getValue();
    if (ioerrs.has_errors() == false) 
    {
      std::cout << "Primitive(s) validated: ";
      if (prim3d == SOLID)        
        std::cout << "Solid" << std::endl;
      else if (prim3d == MULTISURFACE)        
        std::cout << "MultiSurface" << std::endl;
      else if (prim3d == COMPOSITESURFACE)        
        std::cout << "CompositeSurface" << std::endl;
      else {
        std::cout << "All" << std::endl;
        std::cout << "(CityGML/CityJSON/IndoorGML have all their 3D primitives validated)" << std::endl;
      }
      //-- report on parameters used
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
    if ( (lsFeatures.empty() == false) && (ioerrs.has_errors() == false) )
    {
      int i = 1;
      for (auto& f : lsFeatures)
      {
        if ( (i % 10 == 0) && (verbose.getValue() == false) )
          printProgressBar(100 * (i / double(lsFeatures.size())));
        i++;
        f->validate(planarity_d2p_tol.getValue(), planarity_n_tol_updated, overlap_tol.getValue());
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }

    //-- if error 901 then ignore what was read, it can't be validated
    //-- and is confusing for users to see a valid/invalid while nothing was done...
    if (ioerrs.has_specific_error(901) == true) {
      std::cout << "ERROR 901" << std::endl;
      lsFeatures.clear();
    }

    //-- summary of the validation
    std::cout << "\n" << print_summary_validation(lsFeatures, ioerrs) << std::endl;        

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
        for (auto& f : lsFeatures) {
          int noprim = 0;
          for (auto& p : f->get_primitives()) {
            std::string theid = f->get_id() + "." + std::to_string(noprim);
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
      //-- save the json report in memory first
      json jr;
      get_report_json(jr, 
                       inputfile.getValue(),
                       lsFeatures,
                       snap_tol.getValue(),
                       overlap_tol.getValue(),
                       planarity_d2p_tol.getValue(),
                       planarity_n_tol_updated,
                       ioerrs,
                       onlyinvalid.getValue());
      // HTML report
      if (report.getValue() != "") 
        write_report_html(jr, report.getValue());
      // JSON report
      if (report_json.getValue() != "")
        write_report_json(jr, report_json.getValue());
    }
    else
      std::cout << "-->The validation report wasn't saved, use option '--report' (or '--report_json')." << std::endl;

    //-- unittests 
    if (unittests.getValue() == true)
      std::cout << "\n" << unit_test(lsFeatures, ioerrs) << std::endl;

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


void write_report_json(json& jr, std::string report)
{
  boost::filesystem::path outpath(report);
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



void write_report_html(json& jr, std::string report)
{
  boost::filesystem::path outpath(report);
  if (boost::filesystem::exists(outpath.parent_path()) == false)
    std::cout << "Error: file " << outpath << " impossible to create, wrong path." << std::endl;
  else {
    if (boost::filesystem::exists(outpath) == false)
      boost::filesystem::create_directory(outpath);
    boost::filesystem::path outfile = outpath / "report.html";
    std::ofstream o(outfile.string());
    o << report_indexhtml << std::endl;                                
    std::cout << "Full validation report (in HTML format) saved to " << outfile << std::endl;
    o.close();

    outfile = outpath / "report.js";
    o.open(outfile.string());
    o << "var report =" << jr << std::endl;                                
    o.close();

    outfile = outpath / "tree.html";
    o.open(outfile.string());
    o << report_tree << std::endl;                                
    o.close();

    outfile = outpath / "treeview.js";
    o.open(outfile.string());
    o << report_treeviewjs << std::endl;                                
    o.close();

    outfile = outpath / "val3dityconfig.js";
    o.open(outfile.string());
    o << report_val3dityconfigjs << std::endl;                                
    o.close();
    
    outfile = outpath / "index.css";
    o.open(outfile.string());
    o << report_indexcss << std::endl;                                
    o.close();
  }
}


std::string unit_test(std::vector<Feature*>& lsFeatures, IOErrors& ioerrs)
{
  std::stringstream ss;
  ss << std::endl;
  std::set<int> theerrors;
  if (ioerrs.has_errors() == true)
  {
    for (auto& each : ioerrs.get_unique_error_codes())
      theerrors.insert(each);
  }
  for (auto& f : lsFeatures) {
    for (auto& code : f->get_unique_error_codes())
        theerrors.insert(code);
    for (auto& p : f->get_primitives())
      for (auto& code : p->get_unique_error_codes())
        theerrors.insert(code);
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


std::string print_summary_validation(std::vector<Feature*>& lsFeatures, IOErrors& ioerrs)
{
  std::stringstream ss;
  ss << std::endl;
  int noprim = 0;
  for (auto& o : lsFeatures)
    for (auto& p : o->get_primitives())
      noprim++;
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  int fInvalid = 0;
  for (auto& f : lsFeatures)
  {
    if (f->is_valid() == false)
      fInvalid++;
  }
  ss << "Total # of Features: " << setw(10) << lsFeatures.size() << std::endl;
  float percentage;
  if (lsFeatures.size() == 0)
    percentage = 0;
  else
    percentage = 100 * (fInvalid / float(lsFeatures.size()));
  ss << "# valid: " << setw(22) << lsFeatures.size() - fInvalid;
  if (lsFeatures.size() == 0)
    ss << " (" << 0 << "%)" << std::endl;
  else
    ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(20) << fInvalid;
  ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
  std::set<std::string> thetypes;
  for (auto& f : lsFeatures)
    thetypes.insert(f->get_type());
  if (thetypes.empty() == false)
  {
    ss << "Types:" << std::endl;
    for (auto& each : thetypes)
      ss << "  " << each << std::endl;
  }
  ss << "+++++" << std::endl;
  ss << "Total # of primitives: " << setw(8) << noprim << std::endl;
  int bValid = 0;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      if (p->is_valid() == true)
        bValid++;
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
  std::set<int> theprimitives;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      theprimitives.insert(p->get_type());
  if (theprimitives.empty() == false)
  {
    ss << "Types:" << std::endl;
    for (auto& each : theprimitives)
    {
      ss << "  ";
      switch(each)
      {
        case 0: ss << "Solid"             << std::endl; break;
        case 1: ss << "CompositeSolid"    << std::endl; break;
        case 2: ss << "MultiSolid"        << std::endl; break;
        case 3: ss << "CompositeSurface"  << std::endl; break;
        case 4: ss << "MultiSurface"      << std::endl; break;
        case 5: ss << "ALL"               << std::endl; break;
      }
    }
  }
  //-- overview of errors
  std::map<int,int> errors;
  for (auto& f : lsFeatures) 
    for (auto& code : f->get_unique_error_codes())
        errors[code] = 0;
  for (auto& f : lsFeatures) 
    for (auto& code : f->get_unique_error_codes())
        errors[code] += 1;

  if ( (errors.size() > 0) || (ioerrs.has_errors() == true) )
  {
    ss << "+++++" << std::endl;
    ss << "Errors present:" << std::endl;
    for (auto e : errors)
    {
      ss << "  " << e.first << " -- " << errorcode2description(e.first) << std::endl;
      ss << setw(11) << e.second;
      if (e.first < 600)
       ss << " primitive(s)";
      else
       ss << " feature(s)";
      ss << std::endl;
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
    "Copyright (C) 2011-2018  3D geoinformation research group, TU Delft\n\n"
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


void get_report_json(json& jr,
                     std::string ifile, 
                     std::vector<Feature*>& lsFeatures,
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
  
  std::set<int> theprimitives;
  int noprim = 0;
  for (auto& f : lsFeatures)
  {
    for (auto& p : f->get_primitives())
    {
      theprimitives.insert(p->get_type());
      noprim++;
    }
  }
  jr["overview_primitives"];    
  for (auto& each : theprimitives)
  {
    switch(each)
    {
      case 0: jr["overview_primitives"].push_back("Solid"); break;
      case 1: jr["overview_primitives"].push_back("CompositeSolid"); break;
      case 2: jr["overview_primitives"].push_back("MultiSolid"); break;
      case 3: jr["overview_primitives"].push_back("CompositeSurface"); break;
      case 4: jr["overview_primitives"].push_back("MultiSurface"); break;
      case 5: jr["overview_primitives"].push_back("ALL"); break;
    }
  }
  jr["total_primitives"] = noprim;
  int bValid = 0;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      if (p->is_valid() == true)
        bValid++;
  jr["valid_primitives"] = bValid;
  jr["invalid_primitives"] = noprim - bValid;
  //-- features
  std::set<std::string> thefeatures;
  jr["total_features"] = lsFeatures.size();
  bValid = 0;
  for (auto& f : lsFeatures)
  {
    thefeatures.insert(f->get_type());
    if (f->is_valid() == true)
      bValid++;
  }
  jr["overview_features"];    
  for (auto& each : thefeatures)
    jr["overview_features"].push_back(each);
  jr["valid_features"] = bValid;
  jr["invalid_features"] = lsFeatures.size() - bValid;
  //-- overview of errors
  // "overview-errors": [101, 203],
  // "overview-errors-primitives": [5, 1],
  std::map<int,int> errors;
  for (auto& f : lsFeatures) 
    for (auto& code : f->get_unique_error_codes())
        errors[code] = 0;
  for (auto& f : lsFeatures) 
    for (auto& code : f->get_unique_error_codes())
        errors[code] += 1;
  jr["overview_errors"];    
  for (auto e : errors)
    jr["overview_errors"].push_back(e.first);
  for (auto& e : ioerrs.get_unique_error_codes())
    jr["overview_errors"].push_back(e);
  jr["errors_dataset"];
  jr["features"];
  if (ioerrs.has_errors() == true)
    jr["errors_dataset"] = ioerrs.get_report_json();
  for (auto& f : lsFeatures) 
    jr["features"].push_back(f->get_report_json()); 
}



