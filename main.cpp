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

// ============================================================================
// TODO: redirect std::clog to a file (XML + plain text)
// TODO: check Nef unit, crashed with 015.gml 
// TODO: validation of MultiSurfaces and CompositeSurfaces?  
// TODO: OBJ input? or OFF?  
// TODO: Shell2 --> Shell *everywhere*  
// ============================================================================



#include "input.h"
#include "Shell.h"
#include "Solid.h"
#include <tclap/CmdLine.h>
#include <ctime>


std::string print_summary_validation(vector<Solid>& lsSolids);


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
    // TODO: update tclap help 
    std::cout << "EXAMPLES" << std::endl;
    std::cout << "\tval3dity input.gml > report.txt" << std::endl;
    std::cout << "\t\tValidate all the gml:Solid in input.gml and output report.txt" << std::endl;
    std::cout << "\tval3dity input.gml --xml > report.xml" << std::endl;
    std::cout << "\t\tValidate all the gml:Solid in input.gml and output an XML report" << std::endl;
    std::cout << "\tval3dity data/poly/cube.poly --ishell data/poly/py.poly" << std::endl;
    std::cout << "\t\tValidate the solid formed by the outer shell cube.poly with the inner shell py.poly" << std::endl;
    std::cout << "\tval3dity input.gml --planarity_d2p 0.1" << std::endl;
    std::cout << "\t\tValidates all the solids in input.gml" << std::endl;
    std::cout << "\t\tand uses a tolerance of 0.1unit (distance point to fitted plane)." << std::endl;
  }
};



int main(int argc, char* const argv[])
{
#ifdef VAL3DITY_USE_EPECSQRT
  std::clog << "***** USING EXACT-EXACT *****" << std::endl;
#endif

  IOErrors errs;

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
    TCLAP::UnlabeledValueArg<std::string>  inputfile("inputfile", "input file in either GML (several gml:Solids possible) or POLY (one shell)", true, "", "string");
    TCLAP::MultiArg<std::string>           ishellfiles("", "ishell", "one interior shell (in POLY format only) (more than one possible)", false, "string");
    TCLAP::ValueArg<std::string>           primitives("p", "primitive", "what primitive to validate <S|CS|MS> (default=solid), ie (solid|compositesurface|multisurface)", false, "S", &primVals);
    TCLAP::SwitchArg                       xmloutput("", "xml", "XML output", false);
    TCLAP::SwitchArg                       qie("", "qie", "use the OGC QIE codes", false);
    TCLAP::ValueArg<double>                snap_tolerance("", "snap_tolerance", "tolerance for snapping vertices in GML (default=0.001)", false, 0.001, "double");
    TCLAP::ValueArg<double>                planarity_d2p("", "planarity_d2p", "tolerance for planarity distance_to_plane (default=0.01)", false, 0.01, "double");
    TCLAP::ValueArg<double>                planarity_n("", "planarity_n", "tolerance for planarity based on normals deviation (default=1.0degree)", false, 1.0, "double");

    cmd.add(xmloutput);
    cmd.add(qie);
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(snap_tolerance);
    cmd.add(primitives);
    cmd.add(inputfile);
    cmd.add(ishellfiles);
    cmd.parse( argc, argv );
  
    Primitives3D prim3d = SOLID;
    if (primitives.getValue() == "CS")
      prim3d = COMPOSITESURFACE;
    if (primitives.getValue() == "MS")
      prim3d = MULTISURFACE;

    
    // TODO : redirect clog to a file?
    //    std::streambuf* savedBufferCLOG;
    //    savedBufferCLOG = clog.rdbuf();
    //    std::ofstream mylog;
    //    mylog.open("/Users/hugo/temp/0.log");
    //    std::clog.rdbuf(mylog.rdbuf());

    vector<Solid> lsSolids;

    std::string extension = inputfile.getValue().substr(inputfile.getValue().find_last_of(".") + 1);
    if ( (extension == "gml") ||  
         (extension == "GML") ||  
         (extension == "xml") ||  
         (extension == "XML") ) 
    {
      lsSolids = readGMLfile(inputfile.getValue(), errs, snap_tolerance.getValue());
      if (errs.has_errors())
        throw "901: INVALID_INPUT_FILE";
      if (ishellfiles.getValue().size() > 0)
      {
        std::cout << "No inner shells allowed when GML file used as input." << std::endl;
        throw "No inner shells allowed when GML file used as input.";
      }
    }
    else if ( (extension == "poly") ||
              (extension == "POLY") )
    {
      Solid s;
      Shell2* sh = readPolyfile(inputfile.getValue(), 0, errs);
      if (errs.has_errors())
        throw "901: INVALID_INPUT_FILE";
      s.set_oshell(sh);
      int sid = 1;
      for (auto ifile : ishellfiles.getValue())
      {
        Shell2* sh = readPolyfile(ifile, sid, errs);
        if (errs.has_errors())
          throw "901: INVALID_INPUT_FILE";
        s.add_ishell(sh);
        sid++;
      }
      lsSolids.push_back(s);
    }
    else
      throw "unknown file type (only GML/XML and POLY accepted)";


    //-- now the validation starts
    for (auto& s : lsSolids)
    {
      std::clog << std::endl << "===== Validating Solid #" << s.get_id() << " =====" << std::endl;
      if (s.validate(planarity_d2p.getValue(), planarity_n.getValue()) == false)
        std::clog << "===== INVALID =====" << std::endl;
      else
        std::clog << "===== VALID =====" << std::endl;
    }
        
    //-- outputting report with results
    if (xmloutput.getValue() == true)
    {
      std::stringstream ss;
      ss << "<val3dity>" << std::endl;
      ss << "\t<inputFile>" << inputfile.getValue() << "</inputFile>" << std::endl;
      ss << "\t<primitives>";
      if (prim3d == SOLID)
        ss << "gml:Solid";
      else if (prim3d == COMPOSITESURFACE)
        ss << "gml:CompositeSurface";
      else
        ss << "gml:MultiSurface";
      ss << "</primitives>" << std::endl;
      ss << "\t<snap_tolerance>" << snap_tolerance.getValue() << "</snap_tolerance>" << std::endl;
      ss << "\t<planarity_d2p>" << planarity_d2p.getValue() << "</planarity_d2p>" << std::endl;
      ss << "\t<planarity_n>" << planarity_n.getValue() << "</planarity_n>" << std::endl;
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
      for (auto& s : lsSolids)
        ss << s.get_report_xml();
      ss << "</val3dity>" << std::endl;
      std::cout << ss.str();
    }
    else
    {
      std::stringstream ss;
      ss << "Input File: " << inputfile.getValue() << std::endl;
      ss << "Primitives: ";
      if (prim3d == SOLID)
        ss << "gml:Solid";
      else if (prim3d == COMPOSITESURFACE)
        ss << "gml:CompositeSurface";
      else
        ss << "gml:MultiSurface";
      ss << std::endl;
      ss << "Snap_tolerance: " << snap_tolerance.getValue() << std::endl;
      ss << "Planarity_d2p: " << planarity_d2p.getValue() << std::endl;
      ss << "Planarity_n: " << planarity_n.getValue() << std::endl;
      std::time_t t = std::time(nullptr);
      std::tm tm = *std::localtime(&t);
      ss << "Time: " << std::put_time(&tm, "%c %Z") << std::endl;
      ss << print_summary_validation(lsSolids) << std::endl;
      for (auto& s : lsSolids)
        ss << s.get_report_text();
      std::cout << ss.str();
    }
      
    //-- print summary of errors
    if (lsSolids.size() > 0)
      std::clog << print_summary_validation(lsSolids) << std::endl;

    // TODO : redirect clog to a file?
    //    clog.rdbuf(savedBufferCLOG);
    //    mylog.close();

  }
  catch (TCLAP::ArgException &e) {
    std::cout << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
  catch (std::string problem) {
    std::cout << std::endl << "ERROR: " << problem << std::endl;
    std::cout << "Aborted." << std::endl;
    return(0);
  }
  catch (const char* problem) {
    std::cout << std::endl << "ERROR: " << problem << std::endl;
    std::cout << "Aborted." << std::endl;
    return(0);
  }
  catch (bool b) {
    std::cout << "Aborted." << std::endl;
    return(0);
  }
  std::clog << "\nSuccessfully terminated." << std::endl;
  return(1);
}




std::string print_summary_validation(vector<Solid>& lsSolids)
{
  std::stringstream ss;
  ss << std::endl;
  ss << "+++++++++++++++++++ SUMMARY +++++++++++++++++++" << std::endl;
  ss << "total # of Solids: " << setw(12) << lsSolids.size() << std::endl;
  int bValid = 0;
  for (auto& s : lsSolids)
    if (s.is_valid() == true)
      bValid++;
  ss << "# valid: " << setw(22) << bValid << std::endl;
  ss << "# invalid: " << setw(20) << (lsSolids.size() - bValid) << std::endl;
  std::set<int> allerrs;
  for (auto& s : lsSolids)
  {
    if (s.get_unique_error_codes().size() > 0)
    {
      std::set<int> tmp = s.get_unique_error_codes();
      allerrs.insert(tmp.begin(), tmp.end());
    }
  }
  if (allerrs.size() > 0)
  {
    ss << "Errors present:" << std::endl;
    for (auto e : allerrs)
      ss << "  " << e << " --- " << errorcode2description(e) << std::endl;
  }
  ss << "+++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  return ss.str();
}

