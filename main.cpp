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

static bool callbackWasCalledWithError = false;

//-- global lists to keep track of IDs for shells and faces
vector<string> idShells;
vector< vector<string> > idFaces;
bool bUsingIDs = false;
bool XMLOUTPUT = false;
bool bIsPolyhedron = true; //modified to false to prevent closure check for LoD0


// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
void callback(Val3dity_ErrorCode errorCode,    // 0 means status message, -1 means unknown error
              int shellNum, // -1 means unused; 0-based
              int facetNum,     // -1 means unused; 0-based
              std::string messageStr) // optional
{
  if ( (0 == errorCode) && (XMLOUTPUT == false) )
  {
    // This is just a status message.
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
    switch(errorCode)
    {
        //-- Ring level
      case TOO_FEW_POINTS:                         cout << "TOO_FEW_POINTS"; break;
      case CONSECUTIVE_POINTS_SAME:                cout << "CONSECUTIVE_POINTS_SAME"; break;
      case RING_NOT_CLOSED:                        cout << "RING_NOT_CLOSED"; break;
      case RING_SELF_INTERSECT:                    cout << "RING_SELF_INTERSECT"; break;
        //-- Polygon level
      case INTERSECTION_RINGS:                     cout << "INTERSECTION_RINGS"; break;
      case NON_PLANAR_SURFACE:                     cout << "NON_PLANAR_SURFACE"; break;
      case INTERIOR_DISCONNECTED:                  cout << "INTERIOR_DISCONNECTED"; break;
      case HOLE_OUTSIDE:                           cout << "HOLE_OUTSIDE"; break;
      case HOLES_ARE_NESTED:                       cout << "HOLES_ARE_NESTED"; break;
      case ORIENTATION_RINGS_SAME:                 cout << "ORIENTATION_RINGS_SAME"; break;
        //-- Shell level
      case NOT_VALID_2_MANIFOLD:                   cout << "NOT_VALID_2_MANIFOLD"; break;
      case SURFACE_HAS_HOLE:                       cout << "SURFACE_HAS_HOLE"; break;
      case NON_MANIFOLD:                           cout << "NON_MANIFOLD"; break;
      case FACE_WRONG_ORIENTATION:                 cout << "FACE_WRONG_ORIENTATION"; break;
      case FREE_FACE:                              cout << "FREE_FACE"; break;
      case SURFACE_SELF_INTERSECTS:                cout << "SURFACE_SELF_INTERSECTS"; break;
      case VERTICES_NOT_USED:                      cout << "VERTICES_NOT_USED"; break;
      case ALL_FACES_WRONG_ORIENTATION:            cout << "ALL_FACES_WRONG_ORIENTATION"; break;
        //-- Solid level
      case SHELLS_FACE_ADJACENT:                   cout << "SHELLS_FACE_ADJACENT"; break;
      case SHELL_INTERIOR_INTERSECT:               cout << "SHELL_INTERIOR_INTERSECT"; break;
      case INNER_SHELL_OUTSIDE_OUTER:              cout << "INNER_SHELL_OUTSIDE_OUTER"; break;
      case INTERIOR_OF_SHELL_NOT_CONNECTED:        cout << "INTERIOR_OF_SHELL_NOT_CONNECTED"; break;
        //-- Input problem
      case INVALID_INPUT_FILE:                     cout << "INVALID_INPUT_FILE"; break;
        //-- Other reasons
      default:                                     cout << "UNKNOWN"; break;
    }
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
  std::cout << "USING EXACT-EXACT" << std::endl;
#endif

  bool   TRANSLATE             = true;
  double TOL_PLANARITY_d2p     = 0.01;  //-- default: 1cm 
  double TOL_PLANARITY_normals = 1.0;   //-- default: 1.0 degree
  
  bool ONLYSURFACES            = false;
  
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

  
  if (argc < 2)
  {
    cout << "You have to give at least one input POLY file (a shell)." << endl;
    cout << endl << "Usage: val3dity ./src/data/cube.poly ./src/data/py1.poly" << endl;
    cout << "This example would validate a solid with the outer shell from cube.poly and one inner shell from py1.poly" << endl;
    return(1);
  }

  cbf cbfunction = callback;
  vector<string> arguments;
  for (int argNum = 1; argNum < argc; ++argNum) {
    if (strcmp(argv[argNum], "-xml") == 0) {
      XMLOUTPUT = true;
    }
    else if (strcmp(argv[argNum], "-onlysurfaces") == 0)
      ONLYSURFACES = true;
    else if (strcmp(argv[argNum], "-withids") == 0)
      bUsingIDs = true;
    else if (strcmp(argv[argNum], "-repair") == 0)
      bRepair = true;
    else if (strcmp(argv[argNum], "-planarity_d2p") == 0)
    {
      ++argNum;
      TOL_PLANARITY_d2p = atof(argv[argNum]);
    }
    else if (strcmp(argv[argNum], "-planarity_normals") == 0)
    {
      ++argNum;
      TOL_PLANARITY_normals = atof(argv[argNum]);
    }
    else {
      arguments.push_back(string(argv[argNum]));
    }
  }

  vector<Shell*> shells;
  if (bRepair == false) {
    readAllInputShells(arguments, shells, cbfunction, TRANSLATE);
    if (!callbackWasCalledWithError)
      validate(shells, cbfunction, TOL_PLANARITY_d2p, TOL_PLANARITY_normals, ONLYSURFACES);
  }
  else {
    repair(shells, repairs, cbfunction);
  }

  if (XMLOUTPUT == false) {
    if (ONLYSURFACES == true)
      cout << endl << "Only polygons are individually validated, no solid validation." << endl;
    if (callbackWasCalledWithError)
    {
      if (ONLYSURFACES == false)
        cout << "\nInvalid solid :(" << endl << endl;
      else
        cout << "\nSome polygons are invalid :(" << endl << endl;
      return(0);
    }
    else
    {
      if (ONLYSURFACES == false)
        cout << "\nValid solid :)" << endl;
      else
        cout << "\nAll polygons are valid :)" << endl;
      return(1);
    }
  }
}

