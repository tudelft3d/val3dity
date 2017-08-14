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
#include "Building.h"
#include "Surface.h"
#include "Solid.h"
#include <tclap/CmdLine.h>
#include <time.h>  

using namespace std;
using namespace val3dity;


std::string print_summary_validation(std::vector<Building*>& lsBuildings);
std::string print_summary_validation(std::vector<Primitive*>& lsPrimitives, Primitive3D prim3d);

std::string print_unit_tests(vector<Primitive*>& lsPrimitives);
std::string print_unit_tests(vector<Building*>& lsBuilding);

void write_report_xml (std::ofstream& ss, std::string ifile, vector<Primitive*>& lsPrimitives, Primitive3D prim3d, 
                      double snap_tolerance, double overlap_tolerance, double planarity_d2p, double planarity_n, 
                      IOErrors ioerrs, bool onlyinvalid = false);
void write_report_xml (std::ofstream& ss, std::string ifile, vector<Building*>& lsBuildings,
                      double snap_tolerance, double overlap_tolerance, double planarity_d2p, double planarity_n,
                      IOErrors ioerrs, bool onlyinvalid);


class MyOutput : public TCLAP::StdOutput
{
public:
  
  virtual void usage(TCLAP::CmdLineInterface& c)
  {
    std::cout << "===== val3dity =====" << std::endl;
    std::cout << "OPTIONS" << std::endl;
    std::list<TCLAP::Arg*> args = c.getArgList();
    for (TCLAP::ArgListIterator it = args.begin(); it != args.end(); it++) {
      if ((*it)->getFlag() == "")
        std::cout << "\t--" << (*it)->getName() << std::endl;
      else
        std::cout << "\t-" << (*it)->getFlag() << ", --" << (*it)->getName() << std::endl;
      std::cout << "\t\t" << (*it)->getDescription() << std::endl;
    }
    std::cout << "==SOME EXAMPLES==" << std::endl;
    std::cout << "\tval3dity input.gml -p Solid" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml and outputs a summary" << std::endl;
    std::cout << "\tval3dity input.gml -p Solid -r report.xml" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml and outputs a detailed report in XML" << std::endl;
    std::cout << "\tval3dity input.gml -p CompositeSolid --overlap_tolerance 0.05" << std::endl;
    std::cout << "\t\tValidates each gml:CompositeSolid in input.gml and outputs a summary. A tolerance of 0.05 unit is used." << std::endl;
    std::cout << "\tval3dity input.gml -B" << std::endl;
    std::cout << "\t\tValidates each CityGML Buildings in input.gml and outputs a summary" << std::endl;
    std::cout << "\tval3dity input.gml -p MultiSolid --verbose" << std::endl;
    std::cout << "\t\tAll details of the validation of the solids is printed out" << std::endl;
    std::cout << "\tval3dity data/poly/cube.poly --ishell data/poly/a.poly -p Solid" << std::endl;
    std::cout << "\t\tValidates the solid formed by the outer shell cube.poly with the inner shell a.poly" << std::endl;
    std::cout << "\tval3dity input.gml -p Solid --snap_tolerance 0.1" << std::endl;
    std::cout << "\t\tThe vertices in gml:Solid closer than 0.1unit are snapped together" << std::endl;
    std::cout << "\tval3dity input.gml --info" << std::endl;
    std::cout << "\t\tOutputs information about the GML file (no validation performed)." << std::endl;
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
  primitivestovalidate.push_back("MultiSolid");  
  primitivestovalidate.push_back("CompositeSolid");  
  primitivestovalidate.push_back("MultiSurface");   
  primitivestovalidate.push_back("CompositeSurface");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);

  TCLAP::CmdLine cmd("Allowed options", ' ', "2.0 beta 1");
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::UnlabeledValueArg<std::string>   inputfile(
                                              "inputfile", 
                                              "input file in either GML (containing several solids/objects), CityJSON, OBJ, OFF, or POLY (one exterior shell only)", 
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
                                              "output report in XML format",
                                              false,
                                              "",
                                              "string");
    TCLAP::ValueArg<std::string>            primitives("p",
                                              "primitive",
                                              "what geometric primitive to validate <Solid|CompositeSurface|MultiSurface) (default=S)",
                                              false,
                                              "S",
                                              &primVals);
    TCLAP::SwitchArg                        buildings("b",
                                              "buildings",
                                              "validate all 3D primitives of CityGML Buildings (including BuidingParts),"
                                              "skips the rest,"
                                              "and report per building",
                                              false);
    TCLAP::SwitchArg                        info("i",
                                              "info",
                                              "prints information about the file",
                                              false);
    TCLAP::SwitchArg                        verbose("",
                                              "verbose",
                                              "verbose output",
                                              false);
    TCLAP::SwitchArg                        unittests("",
                                              "unittests",
                                              "unit tests output",
                                              false);
    TCLAP::SwitchArg                        notranslate("",
                                              "notranslate",
                                              "do not translate to (minx,"
                                              "miny)",
                                              false);
    TCLAP::SwitchArg                        onlyinvalid("",
                                              "onlyinvalid",
                                              "only invalid primitives are reported",
                                              false);
    TCLAP::ValueArg<double>                 snap_tolerance("",
                                              "snap_tolerance",
                                              "tolerance for snapping vertices in GML (default=0.001; no-snapping=-1)",
                                              false,
                                              0.001,
                                              "double");
    TCLAP::ValueArg<double>                 overlap_tolerance("",
                                              "overlap_tolerance",
                                              "tolerance for testing overlap CompositeSolids and BuildingParts (default=0.0)",
                                              false,
                                              -1,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_d2p("",
                                              "planarity_d2p",
                                              "tolerance for planarity distance_to_plane (default=0.01)",
                                              false,
                                              0.01,
                                              "double");
    TCLAP::ValueArg<double>                 planarity_n("",
                                              "planarity_n",
                                              "tolerance for planarity based on normals deviation (default=1.0degree)",
                                              false,
                                              1.0,
                                              "double");

    vector<TCLAP::Arg*> xorlist;
    xorlist.push_back(&primitives);
    xorlist.push_back(&buildings);
    xorlist.push_back(&info);
    cmd.xorAdd( xorlist );
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(snap_tolerance);
    cmd.add(notranslate);
    cmd.add(overlap_tolerance);
    cmd.add(verbose);
    cmd.add(unittests);
    cmd.add(onlyinvalid);
    cmd.add(inputfile);
    cmd.add(ishellfiles);
    cmd.add(report);
    cmd.parse( argc, argv );

    if (info.getValue() == true)
    {
      print_information(inputfile.getValue());
      return (1);
    }
  
    Primitive3D prim3d = SOLID;
    if (primitives.getValue()      == "CompositeSolid")
      prim3d = COMPOSITESOLID;
    else if (primitives.getValue() == "MultiSolid")
      prim3d = MULTISOLID;
    else if (primitives.getValue() == "MultiSurface")
      prim3d = MULTISURFACE;
    else if (primitives.getValue() == "CompositeSurface")
      prim3d = COMPOSITESURFACE;
    

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
    if (inputtype == OTHER)
      ioerrs.add_error(901, "File type not supported");

    if ((prim3d == COMPOSITESURFACE) && (ishellfiles.getValue().size() > 0))
      ioerrs.add_error(999, "POLY files having inner shells can be validated as CompositeSurface (only Solids)");
    
    bool usebuildings = buildings.getValue();    
    if ( (inputtype != GML) && (buildings.getValue() == true) )
    {
      std::cout << "Ignoring flag '-b/--buildings' for non-CityGML files" << std::endl;
      usebuildings = false;
    }

    //-- if verbose == false then log to a file
    if (verbose.getValue() == false)
    {
      savedBufferCLOG = clog.rdbuf();
      mylog.open("val3dity.log");
      std::clog.rdbuf(mylog.rdbuf());
    }

    std::vector<Primitive*> lsPrimitives;
    std::vector<Building*> lsBuildings;
    std::map<std::string, std::vector<Primitive*> > dPrimitives;

    if (inputtype == GML)
    {
      try
      {
        readGMLfile(inputfile.getValue(), 
                    dPrimitives,
                    ioerrs, 
                    snap_tolerance.getValue());

        for (auto& each: dPrimitives)
          std::cout << each.first << " : " << (each.second).size() << std::endl;
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
      if (usebuildings == true)
        readCityJSONfile_primitives(inputfile.getValue(), 
                                    lsPrimitives,
                                    prim3d, 
                                    ioerrs, 
                                    snap_tolerance.getValue());
      else
        readCityJSONfile_buildings(inputfile.getValue(), 
                                   lsBuildings,
                                   ioerrs, 
                                   snap_tolerance.getValue());
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
      Surface* sh = readPolyfile(inputfile.getValue(), 0, ioerrs);
      if ( (ioerrs.has_errors() == false) & (prim3d == SOLID) )
      {
        Solid* s = new Solid;
        s->set_oshell(sh);
        int sid = 1;
        for (auto ifile : ishellfiles.getValue())
        {
          Surface* sh = readPolyfile(ifile, sid, ioerrs);
          if (ioerrs.has_errors() == false)
          {
            s->add_ishell(sh);
            sid++;
          }
        }
        if (ioerrs.has_errors() == false)
          lsPrimitives.push_back(s);
      }
      if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
      {
        CompositeSurface* cs = new CompositeSurface;
        cs->set_surface(sh);
        if (ioerrs.has_errors() == false)
          lsPrimitives.push_back(cs);
      }
    }
    else if (inputtype == OFF)
    {
      Surface* sh = readOFFfile(inputfile.getValue(), 0, ioerrs);
      if ( (ioerrs.has_errors() == false) & (prim3d == SOLID) )
      {
        Solid* s = new Solid;
        s->set_oshell(sh);
        if (ioerrs.has_errors() == false)
          lsPrimitives.push_back(s);
      }
      if ( (ioerrs.has_errors() == false) & (prim3d == COMPOSITESURFACE) )
      {
        CompositeSurface* cs = new CompositeSurface;
        cs->set_surface(sh);
        if (ioerrs.has_errors() == false)
          lsPrimitives.push_back(cs);
      }
    }    
    else if (inputtype == OBJ)
    {
      readOBJfile(lsPrimitives,
                  inputfile.getValue(), 
                  ioerrs, 
                  snap_tolerance.getValue());
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

    if ( (ioerrs.has_errors() == false) && (notranslate.getValue() == false) )
    {
      //-- translate all vertices to avoid potential problems
      double tmpx, tmpy;
      double minx = 9e10;
      double miny = 9e10;
      if (buildings.getValue() == true)
      {
        for (auto& b : lsBuildings)
        {
          b->get_min_bbox(tmpx, tmpy);
          if (tmpx < minx)
            minx = tmpx;
          if (tmpy < miny)
            miny = tmpy;
        }
        for (auto& b : lsBuildings)
          b->translate_vertices(minx, miny);
      }
      else 
      {
        for (auto& p : lsPrimitives)
        {
          p->get_min_bbox(tmpx, tmpy);
          if (tmpx < minx)
            minx = tmpx;
          if (tmpy < miny)
            miny = tmpy;
        }
        for (auto& p : lsPrimitives)
          p->translate_vertices(minx, miny);
      }
      std::cout << "Translating all coordinates by (-" << minx << ", -" << miny << ")" << std::endl;
    }
    
    //-- report on parameters used
    if (ioerrs.has_errors() == false)
    {
      std::cout << "Parameters used for validation:" << std::endl;
      if (snap_tolerance.getValue() < 1e-8)
        std::cout << "   snap_tolerance"    << setw(12)  << "none" << std::endl;
      else
        std::cout << "   snap_tolerance"    << setw(12)  << snap_tolerance.getValue() << std::endl;
      std::cout << "   planarity_d2p"     << setw(13)  << planarity_d2p.getValue() << std::endl;
      std::cout << "   planarity_n"       << setw(15) << planarity_n.getValue() << std::endl;
      if (overlap_tolerance.getValue() < 1e-8)
        std::cout << "   overlap_tolerance" << setw(9)  << "none" << std::endl;
      else
        std::cout << "   overlap_tolerance" << setw(9)  << overlap_tolerance.getValue() << std::endl;
    }

    //-- now the validation starts
    if ( (ioerrs.has_errors() == false) && (usebuildings == true) )
    {
      std::cout << "Validating " << lsBuildings.size() << " Buildings." << std::endl;
      int i = 1;
      for (auto& b : lsBuildings)
      {
        if ( (i % 10 == 0) && (verbose.getValue() == false) )
          printProgressBar(100 * (i / double(lsBuildings.size())));
        i++;
        std::clog << std::endl << "======== Validating Building (#" << b->get_id() << ") ========" << std::endl;
        if (b->validate(planarity_d2p.getValue(), planarity_n.getValue(), overlap_tolerance.getValue()) == false)
          std::clog << "======== INVALID ========" << std::endl;
        else
          std::clog << "======== VALID ========" << std::endl;
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }
    else 
    {
      if ( (lsPrimitives.empty() == false) && (ioerrs.has_errors() == false) )
      {
        std::cout << "Validating " << lsPrimitives.size();
        if (prim3d == SOLID)
          std::cout << " Solid";
        else if (prim3d == MULTISOLID)
          std::cout << " MultiSolid";
        else if (prim3d == COMPOSITESURFACE)
          std::cout << " CompositeSurface";
        else if (prim3d == MULTISURFACE)
          std::cout << " MultiSurface";
        std::cout << std::endl;
        int i = 1;
        for (auto& s : lsPrimitives)
        {
          if ( (i % 10 == 0) && (verbose.getValue() == false) )
            printProgressBar(100 * (i / double(lsPrimitives.size())));
          i++;
          std::clog << std::endl << "======== Validating Primitive ========" << std::endl;
          std::clog << "type: ";
          Primitive3D prim3d = s->get_type();
          if (prim3d == SOLID)
            std::clog << "Solid" << std::endl;
          else if (prim3d == COMPOSITESOLID)
            std::clog << "CompositeSolid" << std::endl;
          else if (prim3d == MULTISOLID)
            std::clog << "MultiSolid" << std::endl;
          else if (prim3d == MULTISURFACE)
            std::clog << "MultiSurface" << std::endl;
          else if (prim3d == COMPOSITESURFACE)
            std::clog << "CompositeSurface" << std::endl;
          if (s->get_id() != "")
            std::clog << "id: " << s->get_id() << std::endl;
          if (s->validate(planarity_d2p.getValue(), planarity_n.getValue(), overlap_tolerance.getValue()) == false)
            std::clog << "======== INVALID ========" << std::endl;
          else
            std::clog << "========= VALID =========" << std::endl;
        }
        if (verbose.getValue() == false)
          printProgressBar(100);
      }
    }
    //-- print summary of errors
    if (usebuildings == true)
      std::cout << "\n" << print_summary_validation(lsBuildings) << std::endl;        
    else
      std::cout << "\n" << print_summary_validation(lsPrimitives, prim3d) << std::endl;        
    if (report.getValue() != "")
    {
      std::ofstream thereport;
      thereport.open(report.getValue());
      if (usebuildings == false)
      {
        write_report_xml(thereport, 
                         inputfile.getValue(),
                         lsPrimitives,
                         prim3d, 
                         snap_tolerance.getValue(),
                         overlap_tolerance.getValue(),
                         planarity_d2p.getValue(),
                         planarity_n.getValue(),
                         ioerrs,
                         onlyinvalid.getValue());
      }
      else
      {
        write_report_xml(thereport, 
                         inputfile.getValue(),
                         lsBuildings,
                         snap_tolerance.getValue(),
                         overlap_tolerance.getValue(),
                         planarity_d2p.getValue(),
                         planarity_n.getValue(),
                         ioerrs,
                         onlyinvalid.getValue());
      }
      thereport.close();
      std::cout << "Full validation report saved to " << report.getValue() << std::endl;
    }
    else
      std::cout << "-->The validation report wasn't saved, use option '--report'." << std::endl;

    if (verbose.getValue() == false)
    {
      clog.rdbuf(savedBufferCLOG);
      mylog.close();
    }
    if (unittests.getValue() == true)
    {
      if (buildings.getValue() == true)
        std::cout << "\n" << print_unit_tests(lsBuildings) << std::endl;
      else
        std::cout << "\n" << print_unit_tests(lsPrimitives) << std::endl;
    }
    return(1);
  }
  catch (TCLAP::ArgException &e) 
  {
    std::cout << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
}

std::string print_unit_tests(vector<Primitive*>& lsPrimitives)
{
  int bValid = 0;
  std::stringstream ss;
  std::map<int,int> errors;
  for (auto& s : lsPrimitives)
  {
    if (s->is_valid() == true)
      bValid++;
    for (auto& code : s->get_unique_error_codes())
      errors[code] = 0;
  }
  if (errors.size() > 0)
  {
    ss << "@INVALID " << lsPrimitives.size() << " " << (lsPrimitives.size() - bValid) << " ";
    for (auto e : errors)
      ss << e.first << " ";
  }
  else {
    ss << "@VALID " << lsPrimitives.size() << " " << (lsPrimitives.size() - bValid) << " ";
  }
  ss << std::endl;
  return ss.str();
}

std::string print_unit_tests(vector<Building*>& lsBuilding)
{
  int bValid = 0;
  std::stringstream ss;
  std::map<int,int> errors;
  for (auto& s : lsBuilding)
  {
    if (s->is_valid() == true)
      bValid++;
    for (auto& code : s->get_unique_error_codes())
      errors[code] = 0;
  }
  if (errors.size() > 0)
  {
    ss << "@INVALID " << lsBuilding.size() << " " << (lsBuilding.size() - bValid) << " ";
    for (auto e : errors)
      ss << e.first << " ";
  }
  else {
    ss << "@VALID " << lsBuilding.size() << " " << (lsBuilding.size() - bValid) << " ";
  }
  ss << std::endl;
  return ss.str();
}


std::string print_summary_validation(std::vector<Primitive*>& lsPrimitives, Primitive3D prim3d)
{
  std::stringstream ss;
  ss << std::endl;
  std::string primitives;
  if (prim3d == SOLID)
    primitives = "Solid";
  else if (prim3d == COMPOSITESOLID)
    primitives = "CompositeSolid";
  else if (prim3d == MULTISOLID)
    primitives = "MultiSolid";
  else if (prim3d == MULTISURFACE)
    primitives = "MultiSurface";
  else if (prim3d == COMPOSITESURFACE)
    primitives = "CompositeSurface";

  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  ss << "Primitives validated: " << primitives << std::endl;
  ss << "Total # of primitives: " << setw(8) << lsPrimitives.size() << std::endl;
  int bValid = 0;
  for (auto& s : lsPrimitives)
    if (s->is_valid() == true)
      bValid++;
  float percentage;
  if (lsPrimitives.size() == 0)
    percentage = 0;
  else
    percentage = 100 * ((lsPrimitives.size() - bValid) / float(lsPrimitives.size()));
  ss << "# valid: " << setw(22) << bValid;
  if (lsPrimitives.size() == 0)
    ss << " (" << 0 << "%)" << std::endl;
  else
    ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(20) << (lsPrimitives.size() - bValid);
  ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
  //-- overview of errors
  std::map<int,int> errors;
  for (auto& s : lsPrimitives)
  {
    for (auto& code : s->get_unique_error_codes())
      errors[code] = 0;
  }
  for (auto& s : lsPrimitives)
  {
    for (auto& code : s->get_unique_error_codes())
      errors[code] += 1;
  }
  if (errors.size() > 0)
  {
    ss << "+++++" << std::endl;
    ss << "Errors present:" << std::endl;
    for (auto e : errors)
    {
      ss << "  " << e.first << " --- " << errorcode2description(e.first) << std::endl;
      ss << setw(11) << "(" << e.second << " primitives)" << std::endl;
    }
  }
  ss << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  return ss.str();
}


std::string print_summary_validation(std::vector<Building*>& lsBuildings)
{
  std::stringstream ss;
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  ss << "Total # of Buildings: " << setw(8) << lsBuildings.size() << std::endl;
  int bValid = 0;
  int countPrim = 0;
  int countSolids = 0;
  int countCSolids = 0;
  int countMSurfaces = 0;
  for (auto& b : lsBuildings)
  {
    if (b->is_valid() == true)
      bValid++;
    countPrim += b->get_number_primitives();
    countSolids += b->get_number_solids();
    countCSolids += b->get_number_compositesolids();
    countMSurfaces += b->get_number_multisurfaces();
  }
  float percentage;
  if (lsBuildings.size() == 0)
    percentage = 0;
  else
    percentage = 100 * ((lsBuildings.size() - bValid) / float(lsBuildings.size()));
  ss << "# valid: " << setw(21) << bValid;
  if (lsBuildings.size() == 0)
    ss << " (" << 0 << "%)" << std::endl;
  else
    ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(19) << (lsBuildings.size() - bValid);
  ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
  ss << "+++++" << std::endl;
  ss << "Total # Primitives: " << setw(10) << countPrim << std::endl;
  ss << "\tCompositeSolids: " << setw(5) << countCSolids << std::endl;
  ss << "\tSolids: " << setw(14) << countSolids << std::endl;
  ss << "\tMultiSurfaces: " << setw(7) << countMSurfaces << std::endl;
  //-- overview of errors
  std::map<int,int> errors;
  for (auto& b : lsBuildings)
  {
    for (auto& code : b->get_unique_error_codes())
      errors[code] = 0;
  }
  for (auto& b : lsBuildings)
  {
    for (auto& code : b->get_unique_error_codes())
      errors[code] += 1;
  }
  if (errors.size() > 0)
  {
    ss << "+++++" << std::endl;
    ss << "Errors present:" << std::endl;
    for (auto e : errors)
    {
      ss << "  " << e.first << " --- " << errorcode2description(e.first) << std::endl;
      ss << setw(11) << "(" << e.second << " Buildings)" << std::endl;
    }
  }
  ss << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  return ss.str();
}


void write_report_xml(std::ofstream& ss,
                      std::string ifile, 
                      vector<Primitive*>& lsPrimitives,
                      Primitive3D prim3d, 
                      double snap_tolerance,
                      double overlap_tolerance,
                      double planarity_d2p,
                      double planarity_n,
                      IOErrors ioerrs,
                      bool onlyinvalid)
{
  ss << "<val3dity>" << std::endl;
  ss << "\t<inputFile>" << ifile << "</inputFile>" << std::endl;
  ss << "\t<primitives>";
  if (prim3d == SOLID)
    ss << "gml:Solid";
  else if (prim3d == COMPOSITESOLID)
    ss << "gml:CompositeSolid";
  else if (prim3d == MULTISOLID)
    ss << "gml:MultiSolid";
  else if (prim3d == MULTISURFACE)
    ss << "gml:MultiSurface";
  else if (prim3d == COMPOSITESURFACE)
    ss << "gml:CompositeSurface";
  ss << "</primitives>" << std::endl;
  ss << "\t<snap_tolerance>" << snap_tolerance << "</snap_tolerance>" << std::endl;
  ss << "\t<overlap_tolerance>" << overlap_tolerance << "</overlap_tolerance>" << std::endl;
  ss << "\t<planarity_d2p>" << planarity_d2p << "</planarity_d2p>" << std::endl;
  ss << "\t<planarity_n>" << planarity_n << "</planarity_n>" << std::endl;
  ss << "\t<totalprimitives>" << lsPrimitives.size() << "</totalprimitives>" << std::endl;
  int bValid = 0;
  for (auto& s : lsPrimitives)
    if (s->is_valid() == true)
      bValid++;
  ss << "\t<validprimitives>" << bValid << "</validprimitives>" << std::endl;
  ss << "\t<invalidprimitives>" << (lsPrimitives.size() - bValid) << "</invalidprimitives>" << std::endl;
  std::time_t rawtime;
  struct tm * timeinfo;
  std::time (&rawtime);
  timeinfo = std::localtime ( &rawtime );
  char buffer[80];
  std::strftime(buffer, 80, "%c %Z", timeinfo);
  ss << "\t<time>" << buffer << "</time>" << std::endl;
  if (ioerrs.has_errors() == true)
  {
    ss << ioerrs.get_report_xml();
  }
  else
  {
    for (auto& s : lsPrimitives) 
    {
      if ( !((onlyinvalid == true) && (s->is_valid() == true)) )
        ss << s->get_report_xml();
    }
  }
  ss << "</val3dity>" << std::endl;
}


void write_report_xml(std::ofstream& ss,
                      std::string ifile, 
                      vector<Building*>& lsBuildings,
                      double snap_tolerance,
                      double overlap_tolerance,
                      double planarity_d2p,
                      double planarity_n,
                      IOErrors ioerrs,
                      bool onlyinvalid)
{
  ss << "<val3dity>" << std::endl;
  ss << "\t<inputFile>" << ifile << "</inputFile>" << std::endl;
  ss << "\t<snap_tolerance>" << snap_tolerance << "</snap_tolerance>" << std::endl;
  ss << "\t<overlap_tolerance>" << overlap_tolerance << "</overlap_tolerance>" << std::endl;
  ss << "\t<planarity_d2p>" << planarity_d2p << "</planarity_d2p>" << std::endl;
  ss << "\t<planarity_n>" << planarity_n << "</planarity_n>" << std::endl;
  ss << "\t<numberbuildings>" << lsBuildings.size() << "</numberbuildings>" << std::endl;
  int bValid = 0;
  for (auto& s : lsBuildings)
    if (s->is_valid() == true)
      bValid++;
  ss << "\t<validbuildings>" << bValid << "</validbuildings>" << std::endl;
  ss << "\t<invalidbuildings>" << (lsBuildings.size() - bValid) << "</invalidbuildings>" << std::endl;
  std::time_t rawtime;
  struct tm * timeinfo;
  std::time (&rawtime);
  timeinfo = std::localtime ( &rawtime );
  char buffer[80];
  std::strftime(buffer, 80, "%c %Z", timeinfo);
  ss << "\t<time>" << buffer << "</time>" << std::endl;
  if (ioerrs.has_errors() == true)
  {
    ss << ioerrs.get_report_xml();
  }
  else
  {
    for (auto& s : lsBuildings) 
    {
      if ( !((onlyinvalid == true) && (s->is_valid() == true)) )
        ss << s->get_report_xml();
    }
  }
  ss << "</val3dity>" << std::endl;
}

