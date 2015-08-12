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
#include "validate.h"
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



std::string errorcode2description(int code, bool qie) {
  if (qie == false) {
    switch(code)
    {
      case 0:   return string("STATUS_OK"); break;
      //-- RING
      case 101: return string("TOO_FEW_POINTS"); break;
      case 102: return string("CONSECUTIVE_POINTS_SAME"); break;
      case 103: return string("RING_NOT_CLOSED"); break;
      case 104: return string("RING_SELF_INTERSECTION"); break;
      case 105: return string("RING_COLLAPSED"); break;
      //-- POLYGON
      case 201: return string("INTERSECTION_RINGS"); break;
      case 202: return string("DUPLICATED_RINGS"); break;
      case 203: return string("NON_PLANAR_POLYGON_DISTANCE_PLANE"); break;
      case 204: return string("NON_PLANAR_POLYGON_NORMALS_DEVIATION"); break;
      case 205: return string("POLYGON_INTERIOR_DISCONNECTED"); break;
      case 206: return string("HOLE_OUTSIDE"); break;
      case 207: return string("INNER_RINGS_NESTED"); break;
      case 208: return string("ORIENTATION_RINGS_SAME"); break;
      //-- SHELL
      case 300: return string("NOT_VALID_2_MANIFOLD"); break;
      case 301: return string("TOO_FEW_POLYGONS"); break;
      case 302: return string("SHELL_NOT_CLOSED"); break;
      case 303: return string("NON_MANIFOLD_VERTEX"); break;
      case 304: return string("NON_MANIFOLD_EDGE"); break;
      case 305: return string("MULTIPLE_CONNECTED_COMPONENTS"); break;
      case 306: return string("SHELL_SELF_INTERSECTION"); break;
      case 307: return string("POLYGON_WRONG_ORIENTATION"); break;
      case 308: return string("ALL_POLYGONS_WRONG_ORIENTATION"); break;
      case 309: return string("VERTICES_NOT_USED"); break;
      //--SOLID
      case 401: return string("SHELLS_FACE_ADJACENT"); break;
      case 402: return string("INTERSECTION_SHELLS"); break;
      case 403: return string("INNER_SHELL_OUTSIDE_OUTER"); break;
      case 404: return string("SOLID_INTERIOR_DISCONNECTED"); break;
      case 901: return string("INVALID_INPUT_FILE"); break;
      case 999: return string("UNKNOWN_ERROR"); break;
      default:  return string("UNKNOWN_ERROR"); break;
    }
  }
  else { //-- return QIE error codes
    switch(code)
    {
      case 0:   return string("STATUS_OK"); break;
      //-- RING
      case 101: return string("GE_R_TOO_FEW_POINTS"); break;
      case 102: return string("GE_R_CONSECUTIVE_POINTS_SAME"); break;
      case 103: return string("GE_R_NOT_CLOSED"); break;
      case 104: return string("GE_R_SELF_INTERSECTION"); break;
      case 105: return string("GE_R_COLLAPSED"); break;
      //-- POLYGON
      case 201: return string("GE_P_INTERSECTION_RINGS"); break;
      case 202: return string("GE_P_DUPLICATED_RINGS"); break;
      case 203: return string("GE_P_NON_PLANAR_POLYGON_DISTANCE_PLANE"); break;
      case 204: return string("GE_P_NON_PLANAR_POLYGON_NORMALS_DEVIATION"); break;
      case 205: return string("GE_P_INTERIOR_DISCONNECTED"); break;
      case 206: return string("GE_P_HOLE_OUTSIDE"); break;
      case 207: return string("GE_P_INNER_RINGS_NESTED"); break;
      case 208: return string("GE_P_ORIENTATION_RINGS_SAME"); break;
      //-- SHELL
      case 301: return string("GE_S_TOO_FEW_POLYGONS"); break;
      case 302: return string("GE_S_NOT_CLOSED"); break;
      case 303: return string("GE_S_NON_MANIFOLD_VERTEX"); break;
      case 304: return string("GE_S_NON_MANIFOLD_EDGE"); break;
      case 305: return string("GE_S_MULTIPLE_CONNECTED_COMPONENTS"); break;
      case 306: return string("GE_S_SELF_INTERSECTION"); break;
      case 307: return string("GE_S_POLYGON_WRONG_ORIENTATION"); break;
      case 308: return string("GE_S_ALL_POLYGONS_WRONG_ORIENTATION"); break;
      //--SOLID
      case 401: return string("GE_SO_SHELLS_FACE_ADJACENT"); break;
      case 402: return string("GE_SO_INTERSECTION_SHELLS"); break;
      case 403: return string("GE_SO_INNER_SHELL_OUTSIDE_OUTER"); break;
      case 404: return string("GE_SO_INTERIOR_DISCONNECTED"); break;
      case 901: return string("INVALID_INPUT_FILE"); break;
      case 999: return string("UNKNOWN_ERROR"); break;
      default:  return string("UNKNOWN_ERROR"); break;
    }
  }
}


// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
void callback(int errorCode,    // 0 means status message, -1 means unknown error
              int shellNum, // -1 means unused; 0-based
              int facetNum,     // -1 means unused; 0-based
              std::string messageStr) // optional
{
  if ( (0 == errorCode) && (XMLOUTPUT == false) )
  {
    if ( (shellNum == -1) && (facetNum == -1) )
      cout << messageStr << endl;
    else
      cout << "Status: shell " << shellNum << "; face " << facetNum << ". " << messageStr << endl;
  }
  
  if (errorCode != 0)
  {
    callbackWasCalledWithError = true;
    if (XMLOUTPUT == false)
      cout << "Error #" << errorCode << " ";
    else
    {
      cout << "\t\t<ValidatorMessage>" << endl;
      cout << "\t\t\t<type>ERROR</type>" << endl;
      cout << "\t\t\t<errorCode>" << errorCode << "</errorCode>" << endl;
      cout << "\t\t\t<errorType>";
    }
    std::cout << errorcode2description(errorCode, USEQIECODES);
    if (XMLOUTPUT == false)
      cout << endl;
    else
      cout << "</errorType>" << endl;
    
    if (bUsingIDs == false)
    {
      if (shellNum != -1)
        shellNum = shellNum + 1;
      if (facetNum != -1)
        facetNum = facetNum + 1;
      if (XMLOUTPUT == false)
        cout << "\t" << "[shell: #" << shellNum << "; face: #" << facetNum << "]" << endl;
      else {
        cout << "\t\t\t<shell>" << shellNum << "</shell>" << endl;
        cout << "\t\t\t<face>" << facetNum << "</face>" << endl;
      }
    }
    
    if (bUsingIDs == true)
    {
      string shelloutput = "-1";
      string faceoutput = "-1";
      if (shellNum >= 0)
        shelloutput = idShells[shellNum];
      if (facetNum >= 0&&shellNum >= 0)
        faceoutput = idFaces[shellNum][facetNum];
      if (XMLOUTPUT == false)
        cout << "\t" << "[shell: #" << shelloutput << "; face: #" << faceoutput << "]" << endl;
      else {
        cout << "\t\t\t<shell>" << shelloutput << "</shell>" << endl;
        cout << "\t\t\t<face>" << faceoutput << "</face>" << endl;
      }
    }
    if (messageStr.empty() == false) {
      if (XMLOUTPUT == false)
        cout << "\t" << messageStr << endl;
      else
        cout << "\t\t\t<message>" << messageStr << "</message>" << endl;
    }
    if (XMLOUTPUT == true)
      cout << "\t\t</ValidatorMessage>" << endl;
  }
}




// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main(int argc, char* const argv[])
{
#ifdef VAL3DITY_USE_EPECSQRT
  std::cout << "***** USING EXACT-EXACT *****" << std::endl;
#endif

  bool   TRANSLATE             = true;  //-- to handle very large coordinates 

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
    TCLAP::ValueArg<std::string> inputxml   ("i", "", "xml file input", true, "", "string");
    TCLAP::ValueArg<std::string> primitives ("p", "primitive", "what primitive to validate <S|CS|MS> (default=solid), ie (solid|compositesurface|multisurface)", false, "S", &primVals);
    TCLAP::SwitchArg             outputxml  ("", "outputxml", "XML output", false);
    TCLAP::SwitchArg             qie        ("", "qie", "use the OGC QIE codes", false);
    TCLAP::SwitchArg             withids    ("", "withids", "POLY files contain IDs", false);
    TCLAP::ValueArg<double> planarity_d2p   ("", "planarity_d2p", "tolerance for planarity distance_to_plane (default=0.01)", false, 0.01, "double");
    TCLAP::ValueArg<double> planarity_n     ("", "planarity_n", "tolerance for planarity based on normals deviation (default=1.0)", false, 1.0, "double");
    
    cmd.add(outputxml);
    cmd.add(qie);
    cmd.add(withids);
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(primitives);
    cmd.add(inputxml);
    cmd.parse( argc, argv );
  
    cbf cbfunction = callback;

    Primitives3D prim3d = SOLID;
    if (primitives.getValue() == "CS")
      prim3d = COMPOSITESURFACE;
    if (primitives.getValue() == "MS")
      prim3d = MULTISURFACE;

    XMLOUTPUT = outputxml.getValue();
    USEQIECODES = qie.getValue();
    bUsingIDs = withids.getValue();

    Point3 p(0.1, 0.1, 0.0);
    Point3 p2(0.1, 0.1, 0.0);
    std::cout << (p == p2) << std::endl;

    vector<Shell*> shells;
    //-- read the input GML
    readGMLfile(inputxml.getValue(), shells, cbfunction, TRANSLATE);
    std::cout << "done." << std::endl;
    return 1;
    // if (dorepair.getValue() == false) {
    //   readAllInputShells(oshell.getValue(), fishells, shells, cbfunction, TRANSLATE);
    //   if (!callbackWasCalledWithError)
    //     validate(shells, cbfunction, planarity_d2p.getValue(), planarity_n.getValue(), prim3d);
    // }
    // else {
    //   repair(shells, repairmeths, cbfunction);
    // }

    //-- feedback to user
    if (outputxml.getValue() == false) {
      if (callbackWasCalledWithError)
      {
        cout << "--> Invalid :(" << endl << endl;
        return(0);
      }
      else
      {
        cout << "--> Valid :)" << endl << endl;
        return(1);
      }
    }
  }
  catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
  catch (std::string problem) {
    std::cerr << std::endl << "ERROR: " << problem << " (our other project 'prepair' can perform automatic repair of single polygons)" << std::endl;
    std::cerr << "Aborted." << std::endl;
    return(0);
  }
  catch (bool b) {
    std::cerr << "Aborted." << std::endl;
    return(0);
  }
}


// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main_2(int argc, char* const argv[])
{
#ifdef VAL3DITY_USE_EPECSQRT
  std::cout << "***** USING EXACT-EXACT *****" << std::endl;
#endif

  bool   TRANSLATE             = true;  //-- to handle very large coordinates 

  bool bRepair = false;
  bool repairF = true; //-- flipping orientation of faces
  bool repairD = true; //-- dangling pieces will be removed
  bool repairH = true; //-- holes will be filled
  bool repairI = true; //-- interactions between shells fixed with Boolean ops
  bool repairV = true; //-- unused vertices will be removed (eg for the Stanford Bunny)
  bool repairP = true; //-- non-planar faces are triangulated

  vector<bool> repairmeths;
  repairmeths.push_back(repairF);
  repairmeths.push_back(repairD);
  repairmeths.push_back(repairH);
  repairmeths.push_back(repairI);
  repairmeths.push_back(repairV);
  repairmeths.push_back(repairP);

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
    TCLAP::ValueArg<std::string> oshell     ("i", "oshell", "exterior shell (one and only one)", true, "", "string");
    TCLAP::ValueArg<std::string> inputxml   ("x", "", "xml file input", true, "", "string");
    TCLAP::MultiArg<std::string> ishells    ("", "ishell", "interior shell (more than one possible)", false, "string");
    TCLAP::ValueArg<std::string> primitives ("p", "primitive", "what primitive to validate <S|CS|MS> (default=solid), ie (solid|compositesurface|multisurface)", false, "S", &primVals);
    TCLAP::SwitchArg             dorepair   ("", "repair", "attempt repair", false);
    TCLAP::SwitchArg             xml        ("", "xml", "XML output", false);
    TCLAP::SwitchArg             qie        ("", "qie", "use the OGC QIE codes", false);
    TCLAP::SwitchArg             withids    ("", "withids", "POLY files contain IDs", false);
    TCLAP::ValueArg<double> planarity_d2p   ("", "planarity_d2p", "tolerance for planarity distance_to_plane (default=0.01)", false, 0.01, "double");
    TCLAP::ValueArg<double> planarity_n     ("", "planarity_n", "tolerance for planarity based on normals deviation (default=1.0)", false, 1.0, "double");
    
    cmd.add(xml);
    cmd.add(qie);
    cmd.add(withids);
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(dorepair);
    cmd.add(primitives);
    cmd.add(ishells);
    cmd.add(oshell);
    cmd.add(inputxml);
    cmd.parse( argc, argv );
  
    cbf cbfunction = callback;

    Primitives3D prim3d = SOLID;
    if (primitives.getValue() == "CS")
      prim3d = COMPOSITESURFACE;
    if (primitives.getValue() == "MS")
      prim3d = MULTISURFACE;

    XMLOUTPUT = xml.getValue();
    USEQIECODES = qie.getValue();
    bUsingIDs = withids.getValue();

    std::vector<std::string> fishells = ishells.getValue();
    vector<Shell*> shells;
    if (dorepair.getValue() == false) {
      readAllInputShells(oshell.getValue(), fishells, shells, cbfunction, TRANSLATE);
      if (!callbackWasCalledWithError)
        validate(shells, cbfunction, planarity_d2p.getValue(), planarity_n.getValue(), prim3d);
    }
    else {
      repair(shells, repairmeths, cbfunction);
    }

    //-- feedback to user
    if (xml.getValue() == false) {
      if (callbackWasCalledWithError)
      {
        cout << "--> Invalid :(" << endl << endl;
        return(0);
      }
      else
      {
        cout << "--> Valid :)" << endl << endl;
        return(1);
      }
    }
  }
  catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return(0);
  }
  catch (std::string problem) {
    std::cerr << std::endl << "ERROR: " << problem << " (our other project 'prepair' can perform automatic repair of single polygons)" << std::endl;
    std::cerr << "Aborted." << std::endl;
    return(0);
  }
  catch (bool b) {
    std::cerr << "Aborted." << std::endl;
    return(0);
  }
}

