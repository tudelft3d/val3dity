/*
 val3dity - Copyright (c) 2011-2017, Hugo Ledoux.  All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the authors nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*/

#include "input.h"
#include "Primitive.h"
#include "validate_prim_toporel.h"
#include "Surface.h"
#include "Solid.h"
#include "COError.h"
#include <tclap/CmdLine.h>
#include <time.h>  
#include "nlohmann-json/json.hpp"

using namespace std;
using namespace val3dity;
using json = nlohmann::json;

std::string VAL3DITY_VERSION = "2.0-rc1";


std::string print_summary_validation(std::map<std::string, std::vector<Primitive*>>& dPrimitives, std::map<std::string, COError>& dCOerrors, IOErrors& ioerrs);
std::string unit_test(std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, COError>& dCOerrors, IOErrors& ioerrs);
void write_report_json(json& jr, std::string ifile, std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, COError >& dCOerrors, double snap_tol, double overlap_tol, double planarity_d2p_tol, double planarity_n_tol, IOErrors ioerrs, bool onlyinvalid);


class MyOutput : public TCLAP::StdOutput
{
public:
  
  virtual void usage(TCLAP::CmdLineInterface& c)
  {
    std::cout << "===== val3dity =====" << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::list<TCLAP::Arg*> args = c.getArgList();
    for (TCLAP::ArgListIterator it = args.begin(); it != args.end(); it++) {
      if ((*it)->getName() == "ishell")
        continue;
      if ((*it)->getFlag() == "")
        std::cout << "\t--" << (*it)->getName() << std::endl;
      else
        std::cout << "\t-" << (*it)->getFlag() << ", --" << (*it)->getName() << std::endl;
      std::cout << "\t\t" << (*it)->getDescription() << std::endl;
    }
    std::cout << "==SOME EXAMPLES==" << std::endl;
    std::cout << "\tval3dity input.gml" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in input.gml and outputs a summary" << std::endl;
    std::cout << "\tval3dity citygmlinput.gml" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in citygmlinput.gml" << std::endl;
    std::cout << "\t\tand outputs a summary per city object" << std::endl;
    std::cout << "\tval3dity input.gml -r report.json" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in input.gml" << std::endl;
    std::cout << "\t\tand outputs a detailed report in XML" << std::endl;
    std::cout << "\tval3dity input.gml --overlap_tol 0.05" << std::endl;
    std::cout << "\t\tValidates each 3D primitive in input.gml," << std::endl;
    std::cout << "\t\ta tolerance of 0.05 unit is used for the CompositeSolids and BuildingParts" << std::endl;
    std::cout << "\tval3dity input.gml --verbose" << std::endl;
    std::cout << "\t\tAll details of the validation are printed out" << std::endl;
    std::cout << "\tval3dity input.obj -p Solid" << std::endl;
    std::cout << "\t\tValidates the geometries in input.obj as if they were a Solid" << std::endl;
    std::cout << "\tval3dity input.off -p MultiSurface" << std::endl;
    std::cout << "\t\tValidates the geometries in input.off individually" << std::endl;
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
                                              "Input file in either GML, CityJSON, OBJ, or OFF",
                                              true, 
                                              "", 
                                              "string");
    TCLAP::MultiArg<std::string>            ishellfiles(
                                              "", 
                                              "ishell", 
                                              "One interior shell (in POLY format only; more than one possible)",
                                              false, 
                                              "string");
    TCLAP::ValueArg<std::string>            report("r",
                                              "report",
                                              "Output report in JSON format",
                                              false,
                                              "",
                                              "string");
    TCLAP::ValueArg<std::string>            primitives("p",
                                              "primitive",
                                              "whic geometric primitive to validate <Solid|CompositeSurface|MultiSurface>",
                                              false,
                                              "Solid",
                                              &primVals);
    TCLAP::SwitchArg                        verbose("",
                                              "verbose",
                                              "Verbose output",
                                              false);
    TCLAP::SwitchArg                        unittests("",
                                              "unittests",
                                              "Unit tests output",
                                              false);
    TCLAP::SwitchArg                        notranslate("",
                                              "notranslate",
                                              "Do not translate to (minx, miny)",
                                              false);
    TCLAP::SwitchArg                        onlyinvalid("",
                                              "onlyinvalid",
                                              "Only invalid primitives are reported",
                                              false);
    TCLAP::SwitchArg                        ignore204("",
                                              "ignore204",
                                              "Ignore error 204",
                                              false);    
    TCLAP::ValueArg<double>                 snap_tol("",
                                              "snap_tol",
                                              "Tolerance for snapping vertices in GML (default=0.001; no-snapping=-1)",
                                              false,
                                              0.001,
                                              "double");
    TCLAP::ValueArg<double>                 overlap_tol("",
                                              "overlap_tol",
                                              "Tolerance for testing overlap CompositeSolids and BuildingParts (default=0.0)",
                                              false,
                                              -1,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_d2p_tol("",
                                              "planarity_d2p_tol",
                                              "Tolerance for planarity distance_to_plane (default=0.01)",
                                              false,
                                              0.01,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_n_tol("",
                                              "planarity_n_tol",
                                              "Tolerance for planarity based on normals deviation (default=20.0degree)",
                                              false,
                                              20.0,
                                              "double");

    cmd.add(planarity_d2p_tol);
    cmd.add(planarity_n_tol);
    cmd.add(snap_tol);
    cmd.add(overlap_tol);
    cmd.add(notranslate);
    cmd.add(verbose);
    cmd.add(primitives);
    cmd.add(ignore204);
    cmd.add(unittests);
    cmd.add(onlyinvalid);
    cmd.add(inputfile);
    cmd.add(ishellfiles);
    cmd.add(report);
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
    if (inputtype == OTHER)
      ioerrs.add_error(901, "File type not supported");

    Primitive3D prim3d;
    if ( (inputtype == JSON) || (inputtype == GML) )
    {
      prim3d = ALL;
      if (primitives.getValue() != "")
        std::cout << "[--p " << primitives.getValue() << " overwritten] CityGML/CityJSON have all their 3D primitive validated" << std::endl;
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

    if (ioerrs.has_errors() == false)
    {
      if (inputtype == GML)
      {
        try
        {
          read_file_gml(inputfile.getValue(), 
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
    }

    if ( (ioerrs.has_errors() == false) && (notranslate.getValue() == false) )
    {
      //-- translate all vertices to avoid potential problems
      double tmpx, tmpy;
      double minx = 9e10;
      double miny = 9e10;
      for (auto& co : dPrimitives)
      {
        for (auto& p : co.second)
        {
          p->get_min_bbox(tmpx, tmpy);
          if (tmpx < minx)
            minx = tmpx;
          if (tmpy < miny)
            miny = tmpy;
        }
      }
      Primitive::set_translation_min_values(minx, miny);
      Surface::set_translation_min_values(minx, miny);
      for (auto& co : dPrimitives)
        for (auto& p : co.second)
          p->translate_vertices();
      std::cout << "Translating all coordinates by (-" << minx << ", -" << miny << ")" << std::endl;
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
        bool bValid = true;
        for (auto& p : co.second)
        {
          std::clog << std::endl << "======== Validating Primitive ========" << std::endl;
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
        if ( (bValid == true) && (co.first.find("Building|") != std::string::npos) )
        {
          std::clog << "--extra building validation" << std::endl;
          COError coerrs;
          if (do_primitives_overlap(co.second, coerrs, overlap_tol.getValue()) == true)
          {
            // std::cout << "ERROR OVERLAPPING BUILDING PARTS" << std::endl;
            dCOerrors[co.first] = coerrs;
          }
        }
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }

    if (unittests.getValue() == true)
    {
      std::cout << "\n" << unit_test(dPrimitives, dCOerrors, ioerrs) << std::endl;
    }
    else {
      //-- print summary of errors
      std::cout << "\n" << print_summary_validation(dPrimitives, dCOerrors, ioerrs) << std::endl;        
      if (report.getValue() != "")
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
        std::ofstream o(report.getValue());
        o << jr.dump(2) << std::endl;                                
        std::cout << "Full validation report saved to " << report.getValue() << std::endl;
      }
      else
        std::cout << "-->The validation report wasn't saved, use option '--report'." << std::endl;
    }

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
  jr["overview-errors"];    
  jr["overview-errors-no-primitives"];    
  for (auto e : errors)
  {
    jr["overview-errors"].push_back(e.first);
    jr["overview-errors-no-primitives"].push_back(e.second);
  }
  for (auto& e : ioerrs.get_unique_error_codes())
  {
    jr["overview-errors"].push_back(e);
    jr["overview-errors-no-primitives"].push_back(-1);
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
        jr["CityObjects"][coid] = j;
      }
    }
  }
}



