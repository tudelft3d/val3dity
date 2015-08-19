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

static bool callbackWasCalledWithError = false;

//-- global lists to keep track of IDs for shells and faces
vector<string> idShells;
vector< vector<string> > idFaces;
bool bUsingIDs = false;
bool XMLOUTPUT = false;
//-- error codes from the OGC CityGML QIE (https://portal.opengeospatial.org/wiki/CityGMLqIE/WebHome)
bool USEQIECODES = false;


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
    std::cout << "\tval3dity -i data/poly/cube.poly" << std::endl;
    std::cout << "\t\tTakes the outer shell cube.poly and validates it (as a solid)." << std::endl;
    std::cout << "\tval3dity -i data/poly/cube.poly -p MS" << std::endl;
    std::cout << "\t\tTakes the outer shell cube.poly and validates it (as a multisurface)." << std::endl;
    std::cout << "\tval3dity -i data/poly/cube.poly --ishell data/poly/py.poly" << std::endl;
    std::cout << "\t\tTakes the outer shell cube.poly with the inner shell py.poly" << std::endl;
    std::cout << "\t\tand validates the solid." << std::endl;
    std::cout << "\tval3dity -i data/poly/cube.poly --ishell data/poly/py.poly --ishell data/poly/py2.poly" << std::endl;
    std::cout << "\t\tTakes the outer shell cube.poly with the inner shells py.poly" << std::endl;
    std::cout << "\t\tand py2.poly and validates the solid." << std::endl;
    std::cout << "\tval3dity -i data/poly/cube.poly --planarity_d2p 0.1" << std::endl;
    std::cout << "\t\tTakes the outer shell cube.poly and validates it (as a solid)" << std::endl;
    std::cout << "\t\twith tolerance 0.1unit (distance point to fitted plane)." << std::endl;
  }
};






// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
// void callback(int errorCode,    // 0 means status message, -1 means unknown error
//               int shellNum, // -1 means unused; 0-based
//               int facetNum,     // -1 means unused; 0-based
//               std::string messageStr) // optional
// {
//   if ( (0 == errorCode) && (XMLOUTPUT == false) )
//   {
//     if ( (shellNum == -1) && (facetNum == -1) )
//       cout << messageStr << endl;
//     else
//       cout << "Status: shell " << shellNum << "; face " << facetNum << ". " << messageStr << endl;
//   }
  
//   if (errorCode != 0)
//   {
//     callbackWasCalledWithError = true;
//     if (XMLOUTPUT == false)
//       cout << "Error #" << errorCode << " ";
//     else
//     {
//       cout << "\t\t<ValidatorMessage>" << endl;
//       cout << "\t\t\t<type>ERROR</type>" << endl;
//       cout << "\t\t\t<errorCode>" << errorCode << "</errorCode>" << endl;
//       cout << "\t\t\t<errorType>";
//     }
//     std::cout << errorcode2description(errorCode, USEQIECODES);
//     if (XMLOUTPUT == false)
//       cout << endl;
//     else
//       cout << "</errorType>" << endl;
    
//     if (bUsingIDs == false)
//     {
//       if (shellNum != -1)
//         shellNum = shellNum + 1;
//       if (facetNum != -1)
//         facetNum = facetNum + 1;
//       if (XMLOUTPUT == false)
//         cout << "\t" << "[shell: #" << shellNum << "; face: #" << facetNum << "]" << endl;
//       else {
//         cout << "\t\t\t<shell>" << shellNum << "</shell>" << endl;
//         cout << "\t\t\t<face>" << facetNum << "</face>" << endl;
//       }
//     }
    
//     if (bUsingIDs == true)
//     {
//       string shelloutput = "-1";
//       string faceoutput = "-1";
//       if (shellNum >= 0)
//         shelloutput = idShells[shellNum];
//       if (facetNum >= 0&&shellNum >= 0)
//         faceoutput = idFaces[shellNum][facetNum];
//       if (XMLOUTPUT == false)
//         cout << "\t" << "[shell: #" << shelloutput << "; face: #" << faceoutput << "]" << endl;
//       else {
//         cout << "\t\t\t<shell>" << shelloutput << "</shell>" << endl;
//         cout << "\t\t\t<face>" << faceoutput << "</face>" << endl;
//       }
//     }
//     if (messageStr.empty() == false) {
//       if (XMLOUTPUT == false)
//         cout << "\t" << messageStr << endl;
//       else
//         cout << "\t\t\t<message>" << messageStr << "</message>" << endl;
//     }
//     if (XMLOUTPUT == true)
//       cout << "\t\t</ValidatorMessage>" << endl;
//   }
// }




// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main(int argc, char* const argv[])
{
#ifdef VAL3DITY_USE_EPECSQRT
  std::clog << "***** USING EXACT-EXACT *****" << std::endl;
#endif

  bool   TRANSLATE             = true;  //-- to handle very large coordinates 
  IOErrors errs;

  //-- tclap options
  std::vector<std::string> primitivestovalidate;
  primitivestovalidate.push_back("S");  
  primitivestovalidate.push_back("CS");   
  primitivestovalidate.push_back("MS");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);

  TCLAP::CmdLine cmd("Allowed options", ' ', "0.9");
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::UnlabeledValueArg<std::string>  inputfile("inputfile", "input file in either GML (several gml:Solids possible) or POLY (one shell)", true, "", "string");
    TCLAP::MultiArg<std::string>           ishellfiles("", "ishell", "one interior shell (in POLY format only) (more than one possible)", false, "string");
    TCLAP::ValueArg<std::string>           primitives("p", "primitive", "what primitive to validate <S|CS|MS> (default=solid), ie (solid|compositesurface|multisurface)", false, "S", &primVals);
    TCLAP::SwitchArg                       outputxml("", "outputxml", "XML output", false);
    TCLAP::SwitchArg                       qie("", "qie", "use the OGC QIE codes", false);
    TCLAP::ValueArg<double>                snap_tolerance("", "snap_tolerance", "tolerance for snapping vertices in GML (default=0.001)", false, 0.001, "double");
    TCLAP::ValueArg<double>                planarity_d2p("", "planarity_d2p", "tolerance for planarity distance_to_plane (default=0.01)", false, 0.01, "double");
    TCLAP::ValueArg<double>                planarity_n("", "planarity_n", "tolerance for planarity based on normals deviation (default=1.0degree)", false, 1.0, "double");

    cmd.add(outputxml);
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

    XMLOUTPUT = outputxml.getValue();
    USEQIECODES = qie.getValue();

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
      lsSolids = readGMLfile(inputfile.getValue(), errs, snap_tolerance.getValue(), TRANSLATE);
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
      Shell2* sh = readPolyfile(inputfile.getValue(), 0, errs, TRANSLATE);
      if (errs.has_errors())
        throw "901: INVALID_INPUT_FILE";
      s.set_oshell(sh);
      lsSolids.push_back(s);
      int sid = 1;
      for (auto ifile : ishellfiles.getValue())
      {
        Shell2* sh = readPolyfile(ifile, sid, errs, TRANSLATE);
        if (errs.has_errors())
          throw "901: INVALID_INPUT_FILE";
        s.set_oshell(sh);
        sid++;
      }
    }
    else
      throw "unknown file type";

    //-- now the validation starts
    std::clog << "# of <gml:Solids>: " << lsSolids.size() << std::endl;
    for (auto& s : lsSolids)
    {
      std::clog << "===== Validating Solid #" << s.get_id() << " =====" << std::endl;
      if (s.validate(planarity_d2p.getValue(), planarity_n.getValue()) == false)
        std::clog << "-->invalid" << std::endl;
      else
        std::clog << "-->valid" << std::endl;
    }

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
  std::cout << "\nSuccessfully terminated." << std::endl;
  return(1);
}



