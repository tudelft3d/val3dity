/*
 val3dity - Copyright (c) 2011-2012, Hugo Ledoux.  All rights reserved.
 
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
bool xmloutput = false;
bool bIsPolyhedron = true; //modified to false to prevent closure check for LoD0

// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
void callback_cout(Val3dity_ErrorCode errorCode,    // 0 means status message, -1 means unknown error
                   int shellNum, // -1 means unused; 0-based
                   int facetNum,     // -1 means unused; 0-based
                   std::string messageStr) // optional
{
  if (0 == errorCode)
  {
    // This is just a status message.
    if ( (shellNum == -1) && (facetNum == -1) )
      cout << messageStr << endl;
    else
      cout << "Status: shell " << shellNum << "; face " << facetNum << ". " << messageStr << endl;
  }
  else
  {
    cout << "Error (#";
    switch(errorCode)
    {
        //-- Ring level
      case REPEATED_POINTS:                        cout << errorCode << ") " << "REPEATED_POINTS"; break;
      case RING_NOT_CLOSED:                        cout << errorCode << ") " << "RING_NOT_CLOSED"; break;
      case RING_SELF_INTERSECT:                    cout << errorCode << ") " << "RING_SELF_INTERSECT"; break;
        //-- Surface level
      case SELF_INTERSECTION:                      cout << errorCode << ") " << "SELF_INTERSECTION"; break;
      case NON_PLANAR_SURFACE:                     cout << errorCode << ") " << "NON_PLANAR_SURFACE"; break;
      case INTERIOR_DISCONNECTED:                  cout << errorCode << ") " << "INTERIOR_DISCONNECTED"; break;
      case HOLE_OUTSIDE:                           cout << errorCode << ") " << "HOLE_OUTSIDE"; break;
      case HOLES_ARE_NESTED:                       cout << errorCode << ") " << "HOLES_ARE_NESTED"; break;
      case ORIENTATION_RINGS_SAME:                 cout << errorCode << ") " << "ORIENTATION_RINGS_SAME"; break;
        //-- Shell level
      case NOT_VALID_2_MANIFOLD:                   cout << errorCode << ") " << "NOT_VALID_2_MANIFOLD"; break;
      case SURFACE_NOT_CLOSED:                     cout << errorCode << ") " << "SURFACE_NOT_CLOSED"; break;
      case DANGLING_FACES:                         cout << errorCode << ") " << "DANGLING_FACES"; break;
      case FACE_ORIENTATION_INCORRECT_EDGE_USAGE:  cout << errorCode << ") " << "FACE_ORIENTATION_INCORRECT_EDGE_USAGE"; break;
      case FREE_FACES:                             cout << errorCode << ") " << "FREE_FACES"; break;
      case SURFACE_SELF_INTERSECTS:                cout << errorCode << ") " << "SURFACE_SELF_INTERSECTS"; break;
      case VERTICES_NOT_USED:                      cout << errorCode << ") " << "VERTICES_NOT_USED"; break;
      case SURFACE_NORMALS_WRONG_ORIENTATION:      cout << errorCode << ") " << "SURFACE_NORMALS_WRONG_ORIENTATION"; break;
        //-- Solid level
      case SHELLS_FACE_ADJACENT:                   cout << errorCode << ") " << "SHELLS_FACE_ADJACENT"; break;
      case SHELL_INTERIOR_INTERSECT:               cout << errorCode << ") " << "SHELL_INTERIOR_INTERSECT"; break;
      case INNER_SHELL_OUTSIDE_OUTER:              cout << errorCode << ") " << "INNER_SHELL_OUTSIDE_OUTER"; break;
      case INTERIOR_OF_SHELL_NOT_CONNECTED:        cout << errorCode << ") " << "INTERIOR_OF_SHELL_NOT_CONNECTED"; break;
        //-- Input problem
      case INVALID_INPUT_FILE:                     cout << errorCode << ") " << "INVALID_INPUT_FILE"; break;
        //-- Other reasons
      default:                                     cout << errorCode << ") " << "UNKNOWN"; break;
    }
    cout << endl;
    if (bUsingIDs == false)
    {
      if (shellNum != -1) shellNum = shellNum + 1;
      if (facetNum != -1) facetNum = facetNum + 1;
      cout << "\t" << "[shell: #" << shellNum << "; face: #" << facetNum << "]" << endl;
    }
    else
  	{
  		//add by John to prevent warning
  		//-1 means unused
  		string shelloutput = "-1";
  		string faceoutput = "-1";
  		if (shellNum >= 0) 
      {
  			shelloutput = idShells[shellNum];
      }
  		if (facetNum >= 0&&shellNum >= 0)
      {  
  			faceoutput = idFaces[shellNum][facetNum];
      }
  		cout << "\t" << "[shell: #" << shelloutput << "; face: #" << faceoutput << "]" << endl;    
  	}
    if (messageStr.size() > 0)
      cout << "\t" << messageStr << endl;
    callbackWasCalledWithError = true;
  }
}


void callback_xml(Val3dity_ErrorCode errorCode,    // 0 means status message, -1 means unknown error
                  int shellNum,      // -1 means unused; 0-based
                  int facetNum,      // -1 means unused; 0-based
                  std::string messageStr) // optional
{
  if (0 != errorCode)
  {
    callbackWasCalledWithError = true;
    cout << "\t\t<ValidatorMessage>" << endl;
    cout << "\t\t\t<type>ERROR</type>" << endl;
    cout << "\t\t\t<errorCode>" << errorCode << "</errorCode>" << endl;
    cout << "\t\t\t<errorType>";
    switch(errorCode)
    {
//-- Ring level
      case REPEATED_POINTS:                        cout << "REPEATED_POINTS"; break;
      case RING_NOT_CLOSED:                        cout << "RING_NOT_CLOSED"; break;
      case RING_SELF_INTERSECT:                    cout << "RING_SELF_INTERSECT"; break;
//-- Surface level
      case SELF_INTERSECTION:                      cout << "SELF_INTERSECTION"; break;
      case NON_PLANAR_SURFACE:                     cout << "NON_PLANAR_SURFACE"; break;
      case INTERIOR_DISCONNECTED:                  cout << "INTERIOR_DISCONNECTED"; break;
      case HOLE_OUTSIDE:                           cout << "HOLE_OUTSIDE"; break;
      case HOLES_ARE_NESTED:                       cout << "HOLES_ARE_NESTED"; break;
      case ORIENTATION_RINGS_SAME:                 cout << "ORIENTATION_RINGS_SAME"; break;
//-- Shell level
      case NOT_VALID_2_MANIFOLD:                   cout << "NOT_VALID_2_MANIFOLD"; break;
      case SURFACE_NOT_CLOSED:                     cout << "SURFACE_NOT_CLOSED"; break;
      case DANGLING_FACES:                         cout << "DANGLING_FACES"; break;
      case FACE_ORIENTATION_INCORRECT_EDGE_USAGE:  cout << "FACE_ORIENTATION_INCORRECT_EDGE_USAGE"; break;
      case FREE_FACES:                             cout << "FREE_FACES"; break;
      case SURFACE_SELF_INTERSECTS:                cout << "SURFACE_SELF_INTERSECTS"; break;
      case VERTICES_NOT_USED:                      cout << "VERTICES_NOT_USED"; break;
      case SURFACE_NORMALS_WRONG_ORIENTATION:      cout << "SURFACE_NORMALS_WRONG_ORIENTATION"; break;
//-- Solid level
      case SHELLS_FACE_ADJACENT:                   cout << "SHELLS_FACE_ADJACENT"; break;
      case SHELL_INTERIOR_INTERSECT:               cout << "SHELL_INTERIOR_INTERSECT"; break;
      case INNER_SHELL_OUTSIDE_OUTER:              cout << "INNER_SHELL_OUTSIDE_OUTER"; break;
      case INTERIOR_OF_SHELL_NOT_CONNECTED:        cout << "INTERIOR_OF_SHELL_NOT_CONNECTED"; break;
        // Input problem
      case INVALID_INPUT_FILE:                     cout << "INVALID_INPUT_FILE"; break;
        // Other reasons
      default:                                     cout << "UNKNOWN"; break;
    }
    cout << "</errorType>" << endl;
    

    if (bUsingIDs == true) 
    {
  		//add by John to prevent warning
  		//-1 means unused
  		string shelloutput = "-1";
  		string faceoutput = "-1";

  		if (shellNum >= 0)
  			shelloutput = idShells[shellNum];

  		if (facetNum >= 0&&shellNum >= 0)
  			faceoutput = idFaces[shellNum][facetNum];

  		cout << "\t\t\t<shell>" << shelloutput << "</shell>" << endl;
  		cout << "\t\t\t<face>" << faceoutput << "</face>" << endl;
  		//cout << "\t\t\t<shell>" << idShells[shellNum] << "</shell>" << endl;
  		//cout << "\t\t\t<face>" << idFaces[shellNum][facetNum] << "</face>" << endl;
    }
    else {
      //-- returns -1 if unknown, otherwise 1-based is better for users, and less geeky...
      if (shellNum != -1) shellNum = shellNum + 1;
      if (facetNum != -1) facetNum = facetNum + 1;
      cout << "\t\t\t<shell>" << shellNum << "</shell>" << endl;
      cout << "\t\t\t<face>" << facetNum << "</face>" << endl;
    }
	if (messageStr.empty() == false)
		cout << "\t\t\t<message>" << messageStr << "</message>" << endl;  
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

  bool TRANSLATE               = true;
  double TOL_PLANARITY_d2p     = 0.01;  //-- default: 1cm 
  double TOL_PLANARITY_normals = 1.0;   //-- default: 1.0 degree
  
  bool bRepair                 = false;
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

  vector<string> arguments;
  for (int argNum = 1; argNum < argc; ++argNum) {
    if (strcmp(argv[argNum], "-xml") == 0)
      xmloutput = true;
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
  // std::cout << "TOL d2p: "      << TOL_PLANARITY_d2p     << std::endl;
  // std::cout << "TOL: normals: " << TOL_PLANARITY_normals << std::endl;

  vector<Shell*> shells;
  if (xmloutput == false) {
    if (bUsingIDs == true) {
      readAllInputShells_withIDs(arguments, shells, idShells, idFaces, callback_cout);
    }
    else {
      readAllInputShells(arguments, shells, callback_cout, TRANSLATE);           //<---
    }
    
    if (bRepair == false)
      validate(shells, callback_cout, TOL_PLANARITY_d2p, TOL_PLANARITY_normals); //<---
    else
      repair(shells, repairs, callback_cout);
  }
  else {
    if (bUsingIDs == true) {
      readAllInputShells_withIDs(arguments, shells, idShells, idFaces, callback_xml);
    }
    else {
      readAllInputShells(arguments, shells, callback_xml, TRANSLATE);
    }
    if (bRepair == false)
		  validate(shells, callback_xml, TOL_PLANARITY_d2p, TOL_PLANARITY_normals);
	  else
		  repair(shells, repairs, callback_xml);
  }

  if (xmloutput == false) {
    if (callbackWasCalledWithError)
    {
       cout << "\nInvalid solid :(" << endl << endl;
       return(0);
    }
    else
    {
       cout << "\nValid solid. Hourrraaa!" << endl;
       return(1);
    }
  }
}

