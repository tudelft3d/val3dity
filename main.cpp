/*
 val3dity - Copyright (c) 2011-2016, Hugo Ledoux.  All rights reserved.
 
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
#include "Shell.h"
#include "Solid.h"
#include <tclap/CmdLine.h>
#include <time.h>  


std::string print_summary_validation(vector<Solid*>& lsSolids, Primitive3D prim3d, bool buildings, int& nobuildings);
std::string print_unit_tests(vector<Solid*>& lsSolids, Primitive3D prim3d, bool usebuildings);

void write_report_xml (std::ofstream& ss, std::string ifile, Primitive3D prim3d, 
                      double snap_tolerance, double planarity_d2p, double planarity_n, 
                      vector<Solid*>& lsSolids, IOErrors ioerrs, bool onlyinvalid = false);



class MyOutput : public TCLAP::StdOutput
{
public:
  
  virtual void usage(TCLAP::CmdLineInterface& c)
  {
    STDOUT("===== val3dity =====" << std::endl);
    STDOUT("OPTIONS" << std::endl);
    std::list<TCLAP::Arg*> args = c.getArgList();
    for (TCLAP::ArgListIterator it = args.begin(); it != args.end(); it++) {
      if ((*it)->getFlag() == "")
        STDOUT("\t--" << (*it)->getName() << std::endl);
      else
        STDOUT("\t-" << (*it)->getFlag() << ", --" << (*it)->getName() << std::endl);
      STDOUT("\t\t" << (*it)->getDescription() << std::endl);
    }
    STDOUT("==SOME EXAMPLES==" << std::endl);
    STDOUT("\tval3dity input.gml" << std::endl);
    STDOUT("\t\tValidates each gml:Solid in input.gml and outputs a summary" << std::endl);
    STDOUT("\tval3dity input.gml -B" << std::endl);
    STDOUT("\t\tsame as previous, but reporting considers Buildings for reporting" << std::endl);
    STDOUT("\tval3dity input.obj" << std::endl);
    STDOUT("\t\tValidates each object in the OBJ file and outputs a summary" << std::endl);
    STDOUT("\tval3dity input.gml -B -p MS" << std::endl);
    STDOUT("\t\tValidates each building represented with gml:MultiSurface and outputs a summary" << std::endl);
    STDOUT("\tval3dity input.gml -r report.xml" << std::endl);
    STDOUT("\t\tValidates each gml:Solid in input.gml and outputs a detailed report in XML" << std::endl);
    STDOUT("\tval3dity data/poly/cube.poly --ishell data/poly/a.poly" << std::endl);
    STDOUT("\t\tValidates the solid formed by the outer shell cube.poly with the inner shell a.poly" << std::endl);
    STDOUT("\tval3dity input.gml --verbose" << std::endl);
    STDOUT("\t\tAll details of the validation of the solids is printed out" << std::endl);
    STDOUT("\tval3dity input.gml --snap_tolerance 0.1" << std::endl);
    STDOUT("\t\tThe vertices in gml:Solid closer than 0.1unit are snapped together" << std::endl);
    STDOUT("\tval3dity input.gml --planarity_d2p 0.1" << std::endl);
    STDOUT("\t\tValidates each gml:Solid in input.gml" << std::endl);
    STDOUT("\t\tand uses a tolerance of 0.1unit (distance point-to-fitted-plane)" << std::endl);
  }
};


int main(int argc, char* const argv[])
{
  IOErrors ioerrs;
  std::streambuf* savedBufferCLOG;
  std::ofstream mylog;

  //-- tclap options
  std::vector<std::string> primitivestovalidate;
  primitivestovalidate.push_back("S");  
  primitivestovalidate.push_back("CS");   
  primitivestovalidate.push_back("MS");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);

  TCLAP::CmdLine cmd("Allowed options", ' ', "1.3.1");
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::UnlabeledValueArg<std::string>  inputfile("inputfile", "input file in either GML (containing several solids/objects), OBJ or POLY (one exterior shell only)", true, "", "string");
    TCLAP::MultiArg<std::string>           ishellfiles("", "ishell", "one interior shell (in POLY format only; more than one possible)", false, "string");
    TCLAP::ValueArg<std::string>           report("r", "report", "output report in XML format", false, "", "string");
    TCLAP::ValueArg<std::string>           primitives("p", "primitive", "what primitive to validate <S|CS|MS> (Solid|CompositeSurface|MultiSurface) (default=S),", false, "S", &primVals);
    TCLAP::SwitchArg                       buildings("B", "Buildings", "report considers the CityGML Buildings", false);
    TCLAP::SwitchArg                       verbose("", "verbose", "verbose output", false);
    TCLAP::SwitchArg                       unittests("", "unittests", "unit tests output", false);
    TCLAP::SwitchArg                       onlyinvalid("", "onlyinvalid", "only invalid primitives are reported", false);
    TCLAP::SwitchArg                       qie("", "qie", "use the OGC QIE error codes", false);
    TCLAP::ValueArg<double>                snap_tolerance("", "snap_tolerance", "tolerance for snapping vertices in GML (default=0.001)", false, 0.001, "double");
    TCLAP::ValueArg<double>                planarity_d2p("", "planarity_d2p", "tolerance for planarity distance_to_plane (default=0.01)", false, 0.01, "double");
    TCLAP::ValueArg<double>                planarity_n("", "planarity_n", "tolerance for planarity based on normals deviation (default=1.0degree)", false, 1.0, "double");

    cmd.add(qie);
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(snap_tolerance);
    cmd.add(primitives);
    cmd.add(buildings);
    cmd.add(verbose);
    cmd.add(unittests);
    cmd.add(onlyinvalid);
    cmd.add(inputfile);
    cmd.add(ishellfiles);
    cmd.add(report);
    cmd.parse( argc, argv );
  
    Primitive3D prim3d = SOLID;
    if (primitives.getValue() == "CS")
      prim3d = COMPOSITESURFACE;
    if (primitives.getValue() == "MS")
      prim3d = MULTISURFACE;

    InputTypes inputtype = OTHER;
    std::string extension = inputfile.getValue().substr(inputfile.getValue().find_last_of(".") + 1);
    if ( (extension == "gml") || (extension == "GML") || (extension == "xml") || (extension == "XML") ) 
      inputtype = GML;
    else if ( (extension == "poly") || (extension == "POLY") ) 
      inputtype = POLY;
    else if ( (extension == "obj") || (extension == "OBJ") ) 
      inputtype = OBJ;
    if (inputtype == OTHER)
    {
      STDOUT("File type not supported. Abort." << std::endl);
      ioerrs.add_error(901, "File type not supported");
    }

    bool usebuildings = buildings.getValue();    
    if ( (inputtype != GML) && (buildings.getValue() == true) )
    {
      STDOUT("Ignoring flag '-B/--Buildings' for OBJ and POLY files" << std::endl);
      usebuildings = false;
    }

    //-- if verbose == false then log to a file
    if (verbose.getValue() == false)
    {
      savedBufferCLOG = clog.rdbuf();
      mylog.open("val3dity.log");
      std::clog.rdbuf(mylog.rdbuf());
    }

    vector<Solid*> lsSolids;
    int nobuildings;

    if (inputtype == GML)
    {
      try
      {
        readGMLfile(lsSolids,
                    inputfile.getValue(), 
                    prim3d, 
                    usebuildings, 
                    ioerrs, 
                    snap_tolerance.getValue(),
                    nobuildings
                   );
        if (ioerrs.has_errors() == true) {
          STDOUT("Errors while reading the input file, aborting." << std::endl);
          STDOUT(ioerrs.get_report_text() << std::endl);
        }
        if (ishellfiles.getValue().size() > 0)
        {
          STDOUT("No inner shells allowed when GML file used as input." << std::endl);
          ioerrs.add_error(901, "No inner shells allowed when GML file used as input.");
        }
      }
      catch (int e)
      {
        if (e == 901)
          ioerrs.add_error(901, "Invalid GML structure, or that particular (twisted and obscure) construction of GML is not supported. Please report at https://github.com/tudelft3d/val3dity/issues");
      }
    }
    else if (inputtype == POLY)
    {
      Solid* s = new Solid;
      Shell* sh = readPolyfile(inputfile.getValue(), 0, ioerrs);
      if (ioerrs.has_errors() == true)
        STDOUT("Input file not found." << std::endl);
      else
      {
        s->set_oshell(sh);
        int sid = 1;
        for (auto ifile : ishellfiles.getValue())
        {
          Shell* sh = readPolyfile(ifile, sid, ioerrs);
          if (ioerrs.has_errors() == true)
            STDOUT("Input file inner shell not found." << std::endl);
          else
          {
            s->add_ishell(sh);
            sid++;
          }
        }
        if (ioerrs.has_errors() == false)
          lsSolids.push_back(s);
      }
    }
    else if (inputtype == OBJ)
    {
      readOBJfile(lsSolids,
                  inputfile.getValue(), 
                  ioerrs, 
                  snap_tolerance.getValue()
                 );
      if (ioerrs.has_errors() == true) {
        STDOUT("Errors while reading the input file, aborting." << std::endl);
        STDOUT(ioerrs.get_report_text() << std::endl);
      }
      if (ishellfiles.getValue().size() > 0)
      {
        STDOUT("No inner shells allowed when GML file used as input." << std::endl);
        ioerrs.add_error(901, "No inner shells allowed when GML file used as input.");
      }
    }

    //-- translate all vertices to avoid potential problems
    for (auto& s : lsSolids)
      s->translate_vertices();
    
    //-- now the validation starts
    if ( (lsSolids.empty() == false) && (ioerrs.has_errors() == false) )
    {
      STDOUT("Validating " << lsSolids.size());
      if (prim3d == SOLID)
        STDOUT(" Solid");
      else if (prim3d == COMPOSITESURFACE)
        STDOUT(" CompositeSurface");
      else 
        STDOUT(" MultiSurface");
      STDOUT(std::endl);
      int i = 1;
      for (auto& s : lsSolids)
      {
        if ( (i % 10 == 0) && (verbose.getValue() == false) )
          printProgressBar(100 * (i / double(lsSolids.size())));
        i++;
        STDLOG(std::endl << "===== Validating Primitive #" << s->get_id() << " =====" << std::endl);
        STDLOG("Number shells: " << (s->num_ishells() + 1) << std::endl);
        STDLOG("Number faces: " << s->num_faces() << std::endl);
        STDLOG("Number vertices: " << s->num_vertices() << std::endl);
        if (inputtype == OBJ) 
        {
          Shell* sh = s->get_oshell();
          if (sh->were_vertices_merged_during_parsing() == true)
          {
            STDLOG("-->" << (sh->get_number_parsed_vertices() - sh->number_vertices()) << " duplicate vertices were merged" << std::endl);
            STDLOG("-->" << "tolerance applied was " << snap_tolerance.getValue() << std::endl);
          }
        }
        if (s->get_id_building().empty() == false)
          STDLOG("Building: " << s->get_id_building() << std::endl);
        if (s->get_id_buildingpart().empty() == false)
          STDLOG("BuildingPart: " << s->get_id_buildingpart() << std::endl);

        if (s->validate(prim3d, planarity_d2p.getValue(), planarity_n.getValue()) == false)
          STDLOG("===== INVALID =====" << std::endl);
        else
          STDLOG("===== VALID =====" << std::endl);
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }

    //-- print summary of errors
    STDOUT("\n" << print_summary_validation(lsSolids, prim3d, usebuildings, nobuildings) << std::endl);
   
    if (report.getValue() != "")
    {
      std::ofstream thereport;
      thereport.open(report.getValue());
      write_report_xml(thereport, 
                       inputfile.getValue(),
                       prim3d, 
                       snap_tolerance.getValue(),
                       planarity_d2p.getValue(),
                       planarity_n.getValue(),
                       lsSolids,
                       ioerrs,
                       onlyinvalid.getValue());
      thereport.close();
      STDOUT("Full validation report saved to " << report.getValue() << std::endl);
    }
    if (report.getValue() == "")
      STDOUT("-->The validation report wasn't saved, use option '--report'." << std::endl);

    if (verbose.getValue() == false)
    {
      clog.rdbuf(savedBufferCLOG);
      mylog.close();
    }
    if (unittests.getValue() == true)
    {
      STDOUT("\n" << print_unit_tests(lsSolids, prim3d, usebuildings) << std::endl);
    }
    return(1);
  }
  catch (TCLAP::ArgException &e) {
    STDOUT("ERROR: " << e.error() << " for arg " << e.argId() << std::endl);
    return(0);
  }
}


std::string print_unit_tests(vector<Solid*>& lsSolids, Primitive3D prim3d, bool usebuildings)
{
  int bValid = 0;
  std::stringstream ss;
  std::map<int,int> errors;
  for (auto& s : lsSolids)
  {
    if (s->is_valid() == true)
      bValid++;
    for (auto& code : s->get_unique_error_codes())
      errors[code] = 0;
  }
  //-- Building overview
  std::map<std::string, vector<Solid*> > dBuildings;
  int buildingInvalid = 0;
  if (usebuildings == true)
  {
    for (auto& s : lsSolids)
      dBuildings[s->get_id_building()].push_back(s);
    // ss << "Total # of Buildings: " << setw(9) << dBuildings.size() << std::endl;
    for (auto b : dBuildings)
    {
      for (auto& sol : b.second)
      {
        if (sol->is_valid() == false)
        {
          buildingInvalid++;
          break;
        }
      }
    }
  }
  if (errors.size() > 0)
  {
    ss << "@INVALID " << lsSolids.size() << " " << (lsSolids.size() - bValid) << " ";
    ss << dBuildings.size() << " " << buildingInvalid << " ";
    for (auto e : errors)
      ss << e.first << " ";
  }
  else {
    ss << "@VALID " << lsSolids.size() << " " << (lsSolids.size() - bValid) << " ";
    ss << dBuildings.size() << " " << buildingInvalid;
  }
  ss << std::endl;
  return ss.str();
}


std::string print_summary_validation(vector<Solid*>& lsSolids, Primitive3D prim3d, bool buildings, int& nobuildings)
{
  std::stringstream ss;
  ss << std::endl;
  std::string primitives;
  if (prim3d == SOLID)
    primitives = "Solid";
  else if (prim3d == COMPOSITESURFACE)
    primitives = "CompositeSurface";
  else 
    primitives = "MultiSurface";
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  ss << "Primitives validated: " << primitives << std::endl;
  ss << "Total # of primitives: " << setw(8) << lsSolids.size() << std::endl;
  int bValid = 0;
  for (auto& s : lsSolids)
    if (s->is_valid() == true)
      bValid++;
  float percentage;
  if (lsSolids.size() == 0)
    percentage = 0;
  else
    percentage = 100 * ((lsSolids.size() - bValid) / float(lsSolids.size()));
  ss << "# valid: " << setw(22) << bValid;
  if (lsSolids.size() == 0)
    ss << " (" << 0 << "%)" << std::endl;
  else
    ss << std::fixed << setprecision(1) << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(20) << (lsSolids.size() - bValid);
  ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
  //-- Building overview
  if (buildings == true)
  {
    std::map<std::string, vector<Solid*> > dBuildings;
    for (auto& s : lsSolids)
      dBuildings[s->get_id_building()].push_back(s);
    ss << "+++++" << std::endl;
    ss << "Total # of Buildings: " << setw(9) << dBuildings.size() << std::endl;
    if (dBuildings.size() == 0)
    {
      ss << "# valid: "   << setw(22) << 0 << " (0.0%)" << std::endl;
      ss << "# invalid: " << setw(20) << 0 << " (0.0%)" << std::endl;
    }  
    else
    {
      int bInvalid = 0;
      for (auto b : dBuildings)
      {
        for (auto& sol : b.second)
        {
          if (sol->is_valid() == false)
          {
            bInvalid++;
            break;
          }
        }
      }
      percentage = 100 * ((dBuildings.size() - bInvalid) / float(dBuildings.size()));
      ss << "# valid: "   << setw(22) << (dBuildings.size() - bInvalid);
      ss << std::fixed << setprecision(1) << " (" << percentage << "%)" << std::endl;
      ss << "# invalid: " << setw(20) << bInvalid;
      ss << std::fixed << setprecision(1) << " (" << (100 - percentage) << "%)" << std::endl;
    }
    if (dBuildings.size() != nobuildings)
    {
      ss << "(file contains " << nobuildings << " Buildings in total)" << std::endl;
      ss << "(but " << dBuildings.size() << " are stored with ";
      if (prim3d == SOLID)
        ss << "gml:Solid";
      else if (prim3d == COMPOSITESURFACE)
        ss << "gml:CompositeSurface";
      else 
        ss << "gml:MultiSurface";
      ss << ")" << std::endl;
    }
  }
  //-- overview of errors
  std::map<int,int> errors;
  for (auto& s : lsSolids)
  {
    for (auto& code : s->get_unique_error_codes())
      errors[code] = 0;
  }
  for (auto& s : lsSolids)
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


void write_report_xml(std::ofstream& ss,
                      std::string ifile, 
                      Primitive3D prim3d, 
                      double snap_tolerance,
                      double planarity_d2p,
                      double planarity_n,
                      vector<Solid*>& lsSolids,
                      IOErrors ioerrs,
                      bool onlyinvalid)
{
  ss << "<val3dity>" << std::endl;
  ss << "\t<inputFile>" << ifile << "</inputFile>" << std::endl;
  ss << "\t<primitives>";
  if (prim3d == SOLID)
    ss << "gml:Solid";
  else if (prim3d == COMPOSITESURFACE)
    ss << "gml:CompositeSurface";
  else
    ss << "gml:MultiSurface";
  ss << "</primitives>" << std::endl;
  ss << "\t<snap_tolerance>" << snap_tolerance << "</snap_tolerance>" << std::endl;
  ss << "\t<planarity_d2p>" << planarity_d2p << "</planarity_d2p>" << std::endl;
  ss << "\t<planarity_n>" << planarity_n << "</planarity_n>" << std::endl;
  ss << "\t<totalprimitives>" << lsSolids.size() << "</totalprimitives>" << std::endl;
  int bValid = 0;
  for (auto& s : lsSolids)
    if (s->is_valid() == true)
      bValid++;
  ss << "\t<validprimitives>" << bValid << "</validprimitives>" << std::endl;
  ss << "\t<invalidprimitives>" << (lsSolids.size() - bValid) << "</invalidprimitives>" << std::endl;
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
    for (auto& s : lsSolids) 
    {
      if ( !((onlyinvalid == true) && (s->is_valid() == true)) )
        ss << s->get_report_xml();
    }
  }
  ss << "</val3dity>" << std::endl;
}