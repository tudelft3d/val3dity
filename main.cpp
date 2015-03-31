/*
 val3dity - Copyright (c) 2011-2014, Hugo Ledoux.  All rights reserved.
 
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
    std::cout << "\tpprepair -i file1.shp -i file2.geojson --outerrors out.shp -v" << std::endl;
    std::cout << "\t\tTakes 2 input files, validates them," << std::endl;
    std::cout << "\t\tand output the problematic regions to out.shp" << std::endl << std::endl;
    std::cout << "\tpprepair -i file1.shp -i file2.geojson -o /home/elvis/temp/ -r fix" << std::endl;
    std::cout << "\t\tTakes 2 input files, repairs them with the default method (RandomNeighbour)" << std::endl;
    std::cout << "\t\tand outputs 2 repaired shapefiles to /home/elvis/temp/ folder" << std::endl;
    std::cout << "\t\t(file1.r.shp and file2.r.shp)" << std::endl << std::endl;
    std::cout << "\tpprepair -i file1.shp -o /home/elvis/temp/ -r PL --priority prio.txt" << std::endl;
    std::cout << "\t\tTakes 1 input file, repairs it with PriorityList rule" << std::endl;
    std::cout << "\t\tand outputs the repaired shapefile to /home/elvis/temp/ folder" << std::endl << std::endl;
    std::cout << "\tpprepair -i file1.shp -e extent.geojson -o . -r LB" << std::endl;
    std::cout << "\t\tTakes 1 input file and a spatial extent file," << std::endl; 
    std::cout << "\t\trepairs file1.shp for holes and overlaps + 'aligns' it to extent.geojson" << std::endl; 
    std::cout << "\t\tRepaired shapefile file1.r.shp saved to current folder" << std::endl << std::endl;
  }
};

static bool callbackWasCalledWithError = false;

//-- global lists to keep track of IDs for shells and faces
vector<string> idShells;
vector< vector<string> > idFaces;
bool bUsingIDs = false;
bool XMLOUTPUT = false;
//-- error codes from the OGC CityGML QIE (https://portal.opengeospatial.org/wiki/CityGMLqIE/WebHome)
bool USEQIECODES = false;


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

  // double TOL_PLANARITY_d2p = 0.01;  //-- default: 1cm 
  // double TOL_PLANARITY_n   = 1.0;   //-- default: 1.0 degree

  bool   TRANSLATE             = true;  //-- to handle very large coordinates 
                                        //   the object is translated to its min xyz

  bool MULTISURFACE            = false;
  bool COMPOSITESURFACE        = false;
  
  bool bRepair = false;
  bool repairF = true; //-- flipping orientation of faces
  bool repairD = true; //-- dangling pieces will be removed
  bool repairH = true; //-- holes will be filled
  bool repairI = true; //-- interactions between shells fixed with Boolean ops
  bool repairV = true; //-- unused vertices will be removed (eg for the Stanford Bunny)
  bool repairP = true; //-- non-planar faces are triangulated

  vector<bool> repairs;
  repairs.push_back(repairF);
  repairs.push_back(repairD);
  repairs.push_back(repairH);
  repairs.push_back(repairI);
  repairs.push_back(repairV);
  repairs.push_back(repairP);

  //-- tclap options

  std::vector<std::string> primitivestovalidate;
  primitivestovalidate.push_back("S");  
  primitivestovalidate.push_back("CS");   
  primitivestovalidate.push_back("MS");   
  TCLAP::ValuesConstraint<std::string> primVals(primitivestovalidate);
  TCLAP::CmdLine cmd("Allowed options", ' ', "");
  MyOutput my;
  cmd.setOutput(&my);
  try {
    TCLAP::ValueArg<std::string> oshell     ("i", "oshell", "exterior shell (one and only one given)", true, "", "string");
    TCLAP::MultiArg<std::string> ishells    ("", "ishell", "interior shell (more than one possible)", false, "string");
    TCLAP::ValueArg<std::string> primitives ("p", "primitive", "what primitive to validate <S|CS|MS>", false, "S", &primVals);
    TCLAP::SwitchArg             repair     ("", "repair", "attempt repair", false);
    TCLAP::SwitchArg             xml        ("", "xml", "XML output", false);
    TCLAP::SwitchArg             qie        ("", "qie", "use the OGC QIE codes", false);
    TCLAP::SwitchArg             withids    ("", "withids", "POLY files contain IDs", false);
    TCLAP::ValueArg<double> planarity_d2p    ("", "planarity_d2p", "tolerance for planarity distance_to_plane", false, 0.1, "double");
    TCLAP::ValueArg<double> planarity_n      ("", "planarity_n", "tolerance for planarity based on normals deviation", false, 1.0, "double");
    
    cmd.add(xml);
    cmd.add(qie);
    cmd.add(withids);
    cmd.add(planarity_d2p);
    cmd.add(planarity_n);
    cmd.add(repair);
    cmd.add(primitives);
    cmd.add(ishells);
    cmd.add(oshell);
    cmd.parse( argc, argv );
  

    cbf cbfunction = callback;


  // for (int argNum = 1; argNum < argc; ++argNum) {
  //   if (strcmp(argv[argNum], "-xml") == 0) {
  //     XMLOUTPUT = true;
  //   }
  //   else if (strcmp(argv[argNum], "-qie") == 0)
  //     USEQIECODES = true;
  //   else if (strcmp(argv[argNum], "-multisurface") == 0)
  //     MULTISURFACE = true;
  //   else if (strcmp(argv[argNum], "-withids") == 0)
  //     bUsingIDs = true;
  //   else if (strcmp(argv[argNum], "-repair") == 0)
  //     bRepair = true;
  //   else if (strcmp(argv[argNum], "-planarity_d2p") == 0)
  //   {
  //     ++argNum;
  //     TOL_PLANARITY_d2p = atof(argv[argNum]);
  //   }
  //   else if (strcmp(argv[argNum], "-planarity_normals") == 0)
  //   {
  //     ++argNum;
  //     TOL_PLANARITY_normals = atof(argv[argNum]);
  //   }
  //   else {
  //     arguments.push_back(string(argv[argNum]));
  //   }
  // }

    // std::cout << (ishells.getValue()).size() << std::endl;
    std::vector<std::string> fishells = ishells.getValue();
    vector<Shell*> shells;
    if (repair.getValue() == false) {
      readAllInputShells(oshell.getValue(), fishells, shells, cbfunction, TRANSLATE);
      if (!callbackWasCalledWithError)
        validate(shells, cbfunction, planarity_d2p.getValue(), planarity_n.getValue(), false);
    }
    // else {
      // repair(shells, repairs, cbfunction);
    // }
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
  // std::cout << "\nSuccessfully terminated." << std::endl;
  return 1;

}

