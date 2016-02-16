/*
 val3dity - Copyright (c) 2011-2015, Hugo Ledoux.  All rights reserved.
 
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
#include <ctime>


std::string print_summary_validation(vector<Solid>& lsSolids, Primitive3D prim3d);
void write_report_xml (std::ofstream& ss, std::string ifile, Primitive3D prim3d, 
                      double snap_tolerance, double planarity_d2p, double planarity_n, 
                      vector<Solid>& lsSolids, IOErrors ioerrs, bool onlyinvalid = false);
void write_report_text(std::ofstream& ss, std::string ifile, Primitive3D prim3d, 
                       double snap_tolerance, double planarity_d2p, double planarity_n, 
                       vector<Solid>& lsSolids, IOErrors ioerrs, bool onlyinvalid = false);



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
    std::cout << "EXAMPLES" << std::endl;
    std::cout << "\tval3dity input.gml" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml and outputs a summary" << std::endl;
    std::cout << "\tval3dity input.gml --otxt report.txt" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml and outputs a detailed report in plain text" << std::endl;
    std::cout << "\tval3dity input.gml --oxml report.xml" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml and outputs a detailed report in XML" << std::endl;
    std::cout << "\tval3dity data/poly/cube.poly --ishell data/poly/py.poly" << std::endl;
    std::cout << "\t\tValidates the solid formed by the outer shell cube.poly with the inner shell py.poly" << std::endl;
    std::cout << "\tval3dity input.gml --verbose" << std::endl;
    std::cout << "\t\tAll details of the validation of the solids is printed out" << std::endl;
    std::cout << "\tval3dity input.gml --snap_tolerance 0.1" << std::endl;
    std::cout << "\t\tThe vertices in gml:Solid closer than 0.1unit are snapped together" << std::endl;
    std::cout << "\tval3dity input.gml --planarity_d2p 0.1" << std::endl;
    std::cout << "\t\tValidates each gml:Solid in input.gml" << std::endl;
    std::cout << "\t\tand uses a tolerance of 0.1unit (distance point-to-fitted-plane)" << std::endl;
  }
};


int main(int argc, char* const argv[])
{
#ifdef VAL3DITY_USE_EPECSQRT
  std::clog << "***** USING EXACT-EXACT *****" << std::endl;
#endif

  IOErrors ioerrs;
  std::streambuf* savedBufferCLOG;
  std::ofstream mylog;

  //-- tclap options
  std::vector<std::string> primitivestovalidate;
  primitivestovalidate.push_back("S");  
  primitivestovalidate.push_back("CS");   
  primitivestovalidate.push_back("MS");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);

  TCLAP::CmdLine cmd("Allowed options", ' ', "0.92");
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::UnlabeledValueArg<std::string>  inputfile("inputfile", "input file in either GML (several gml:Solids possible) or POLY (one exterior shell)", true, "", "string");
    TCLAP::MultiArg<std::string>           ishellfiles("", "ishell", "one interior shell (in POLY format only) (more than one possible)", false, "string");
    TCLAP::ValueArg<std::string>           outputxml("", "oxml", "output report in XML format", false, "", "string");
    TCLAP::ValueArg<std::string>           outputtxt("", "otxt", "output report in text format", false, "", "string");
    TCLAP::ValueArg<std::string>           primitives("p", "primitive", "what primitive to validate <S|CS|MS> (Solid|CompositeSurface|MultiSurface) (default=S),", false, "S", &primVals);
    TCLAP::SwitchArg                       verbose("", "verbose", "verbose output", false);
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
    cmd.add(verbose);
    cmd.add(onlyinvalid);
    cmd.add(inputfile);
    cmd.add(ishellfiles);
    cmd.add(outputxml);
    cmd.add(outputtxt);
    cmd.parse( argc, argv );
  
    Primitive3D prim3d = SOLID;
    if (primitives.getValue() == "CS")
      prim3d = COMPOSITESURFACE;
    if (primitives.getValue() == "MS")
      prim3d = MULTISURFACE;

    //-- if verbose == false then log to a file
    if (verbose.getValue() == false)
    {
      savedBufferCLOG = clog.rdbuf();
      mylog.open("val3dity.log");
      std::clog.rdbuf(mylog.rdbuf());
    }

    vector<Solid> lsSolids;

    std::string extension = inputfile.getValue().substr(inputfile.getValue().find_last_of(".") + 1);
    if ( (extension == "gml") ||  
         (extension == "GML") ||  
         (extension == "xml") ||  
         (extension == "XML") ) 
    {
      lsSolids = readGMLfile(inputfile.getValue(), prim3d, ioerrs, snap_tolerance.getValue());
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
    else if ( (extension == "poly") ||
              (extension == "POLY") )
    {
      Solid s;
      Shell* sh = readPolyfile(inputfile.getValue(), 0, ioerrs);
      if (ioerrs.has_errors() == true)
        std::cout << "Input file not found." << std::endl;
      else
      {
        s.set_oshell(sh);
        int sid = 1;
        for (auto ifile : ishellfiles.getValue())
        {
          Shell* sh = readPolyfile(ifile, sid, ioerrs);
          if (ioerrs.has_errors() == true)
            std::cout << "Input file inner shell not found." << std::endl;
          else
          {
            s.add_ishell(sh);
            sid++;
          }
        }
        if (ioerrs.has_errors() == false)
          lsSolids.push_back(s);
      }
    }
    else
    {
      std::cout << "Unknown file type (only GML/XML and POLY accepted)" << std::endl;
      ioerrs.add_error(901, "Unknown file type (only GML/XML and POLY accepted)");
    }
    // //-- check if all primitives are non-empty 
    // //-- (parsing could have failed with "inventive" GML tags)
    // for (auto& s : lsSolids)
    // {
    //   if (s.is_empty() == true) 
    //     s.add_error(999, -1, -1, "Primitive is empty (error while parsing input?)");
    // }

    //-- now the validation starts
    if ( (lsSolids.empty() == false) && (ioerrs.has_errors() == false) )
    {
      std::cout << "Validating " << lsSolids.size();
      if (prim3d == SOLID)
        std::cout << " <gml:Solid>";
      else if (prim3d == COMPOSITESURFACE)
        std::cout << " <gml:CompositeSurface>";
      else 
        std::cout << " <gml:MultiSurface>";
      std::cout << std::endl;
      int i = 1;
      for (auto& s : lsSolids)
      {
        if ( (i % 10 == 0) && (verbose.getValue() == false) )
          printProgressBar(100 * (i / double(lsSolids.size())));
        i++;
        std::clog << std::endl << "===== Validating Primitive #" << s.get_id() << " =====" << std::endl;
        if (s.validate(prim3d, planarity_d2p.getValue(), planarity_n.getValue()) == false)
          std::clog << "===== INVALID =====" << std::endl;
        else
          std::clog << "===== VALID =====" << std::endl;
      }
      if (verbose.getValue() == false)
        printProgressBar(100);
    }

    //-- print summary of errors
    std::cout << "\n" << print_summary_validation(lsSolids, prim3d) << std::endl;        
   
    if (outputxml.getValue() != "")
    {
      std::ofstream thereport;
      thereport.open(outputxml.getValue());
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
      std::cout << "Full validation report saved to " << outputxml.getValue() << std::endl;
    }
    if (outputtxt.getValue() != "")
    {
      std::ofstream thereport;
      thereport.open(outputtxt.getValue());
      write_report_text(thereport, 
                        inputfile.getValue(),
                        prim3d, 
                        snap_tolerance.getValue(),
                        planarity_d2p.getValue(),
                        planarity_n.getValue(),
                        lsSolids,
                        ioerrs,
                        onlyinvalid.getValue());
      thereport.close();
      std::cout << "Full validation report saved to " << outputtxt.getValue() << std::endl;
    }
    if ( (outputtxt.getValue() == "") && (outputxml.getValue() == "") ) 
      std::cout << "-->The validation report wasn't saved, use option '--oxml' or '--otxt'." << std::endl;

    if (verbose.getValue() == false)
    {
      clog.rdbuf(savedBufferCLOG);
      mylog.close();
    }
    return(1);
  }
  catch (TCLAP::ArgException &e) {
    std::cout << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
}




std::string print_summary_validation(vector<Solid>& lsSolids, Primitive3D prim3d)
{
  std::stringstream ss;
  ss << std::endl;
  std::string primitives;
  if (prim3d == SOLID)
    primitives = "<gml:Solid>";
  else if (prim3d == COMPOSITESURFACE)
    primitives = "<gml:CompositeSurface>";
  else 
    primitives = "<gml:MultiSurface>";
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  ss << "Primitives validated: " << primitives << std::endl;
  ss << "total # of primitives: " << setw(8) << lsSolids.size() << std::endl;
  int bValid = 0;
  for (auto& s : lsSolids)
    if (s.is_valid() == true)
      bValid++;
  int percentage = 100 * ((lsSolids.size() - bValid) / float(lsSolids.size()));
  ss << "# valid: " << setw(22) << bValid;
  ss << " (" << 100 - percentage << "%)" << std::endl;
  ss << "# invalid: " << setw(20) << (lsSolids.size() - bValid);
  ss << " (" << percentage << "%)" << std::endl;
  std::set<int> allerrs;
  std::map<int,int> errors;
  for (auto& s : lsSolids)
  {
    for (auto& code : s.get_unique_error_codes())
      errors[code] = 0;
  }
  for (auto& s : lsSolids)
  {
    for (auto& code : s.get_unique_error_codes())
      errors[code] += 1;
  }
  if (errors.size() > 0)
  {
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


void write_report_text(std::ofstream& ss,
                       std::string ifile, 
                       Primitive3D prim3d, 
                       double snap_tolerance,
                       double planarity_d2p,
                       double planarity_n,
                       vector<Solid>& lsSolids,
                       IOErrors ioerrs,
                       bool onlyinvalid)
{
  ss << "Input File: " << ifile << std::endl;
  ss << "Primitives: ";
  if (prim3d == SOLID)
    ss << "gml:Solid";
  else if (prim3d == COMPOSITESURFACE)
    ss << "gml:CompositeSurface";
  else
    ss << "gml:MultiSurface";
  ss << std::endl;
  ss << "Snap_tolerance: " << snap_tolerance << std::endl;
  ss << "Planarity_d2p: " << planarity_d2p << std::endl;
  ss << "Planarity_n: " << planarity_n << std::endl;
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  ss << "Time: " << std::put_time(&tm, "%c %Z") << std::endl;
  ss << print_summary_validation(lsSolids, prim3d) << std::endl;
  if (ioerrs.has_errors() == true)
  {
    ss << ioerrs.get_report_text();
  }
  else
  {
    for (auto& s : lsSolids) 
    {
      if ( !((onlyinvalid == true) && (s.is_valid() == true)) )
        ss << s.get_report_text();
    }
  }
}


void write_report_xml(std::ofstream& ss,
                      std::string ifile, 
                      Primitive3D prim3d, 
                      double snap_tolerance,
                      double planarity_d2p,
                      double planarity_n,
                      vector<Solid>& lsSolids,
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
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  ss << "\t<totalprimitives>" << lsSolids.size() << "</totalprimitives>" << std::endl;
  int bValid = 0;
  for (auto& s : lsSolids)
    if (s.is_valid() == true)
      bValid++;
  ss << "\t<validprimitives>" << bValid << "</validprimitives>" << std::endl;
  ss << "\t<invalidprimitives>" << (lsSolids.size() - bValid) << "</invalidprimitives>" << std::endl;
  ss << "\t<time>" << std::put_time(&tm, "%c %Z") << "</time>" << std::endl;
  if (ioerrs.has_errors() == true)
  {
    ss << ioerrs.get_report_xml();
  }
  else
  {
    for (auto& s : lsSolids) 
    {
      if ( !((onlyinvalid == true) && (s.is_valid() == true)) )
        ss << s.get_report_xml();
    }
  }
  ss << "</val3dity>" << std::endl;
}