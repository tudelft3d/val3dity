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
    // cout << ":  errorCode=" << errorCode << "     Polyhedra #" << polyhedraNum << "       ";
    
    switch(errorCode)
    {
        // Ring level
      case DUPLICATE_POINTS:                       cout << "Error 100: " << "2+ consecutive points"; break;
      case RING_NOT_CLOSED:                        cout << "Error 110: " << "ring is not closed (first-last point are not the same)"; break;
        // Surface level
      case INNER_RING_WRONG_ORIENTATION:           cout << "Error 200: " << "oring and irings have same orientation"; break;
      case NON_PLANAR_SURFACE:                     cout << "Error 210: " << "surface is not planar"; break;
      case SURFACE_PROJECTION_INVALID:             cout << "Error 220: " << "surface is not valid in 2D (its projection)"; break;
      case INNER_RING_INTERSECTS_OUTER:            cout << "Error 221: " << "iring intersect oring"; break;
      case INNER_RING_OUTSIDE_OUTER:               cout << "Error 222: " << "iring outside oring"; break;
        //case INNER_OUTER_RINGS_INTERSECT:          cout << "Error 223: " << "oring and iring(s) intersect"; break;
      case INTERIOR_OF_RING_NOT_CONNECTED:         cout << "Error 224: " << "interior not connected"; break;
        // Shell level
      case NOT_VALID_2_MANIFOLD:                   cout << "Error 300: " << "is not a 2-manifold"; break;
      case SURFACE_NOT_CLOSED:                     cout << "Error 301: " << "surface is not closed"; break;
      case DANGLING_FACES:                         cout << "Error 302: " << "dangling faces (more than 2 surfaces incident to an edge)"; break;
      case FACE_ORIENTATION_INCORRECT_EDGE_USAGE:  cout << "Error 303: " << "orientation of faces not correct (edge not used 2 times: one in each direction)"; break;
      case FREE_FACES:                             cout << "Error 304: " << "faces not connected to the 2-manifold (eg 'floating' in the air)"; break;
      case SURFACE_SELF_INTERSECTS:                cout << "Error 305: " << "surface self-intersect"; break;
      case SURFACE_NORMALS_BAD_ORIENTATION:        cout << "Error 310: " << "normals pointing in wrong direction (oshell=outwards; ishell=inwards)"; break;
        // Solid level
      case SHELLS_FACE_ADJACENT:                   cout << "Error 400: " << "shells are face adjacent"; break;
      case SHELL_INTERIOR_INTERSECT:               cout << "Error 410: " << "interior of shells intersect"; break;
      case INNER_SHELL_OUTSIDE_OUTER:              cout << "Error 420: " << "ishell outside the oshell"; break;
      case INTERIOR_OF_SHELL_NOT_CONNECTED:        cout << "Error 430: " << "interior not connected"; break;
        // Input problem
      case INVALID_INPUT_FILE:                     cout << "Error 999: " << "input file is not valid"; break;
        // Other reasons
      default    : cout << "Error: invalid for unknown reasons (but for sure invalid!)"; break;
    }
    cout << endl;
    
    if (bUsingIDs == false)
      cout << "\t" << "[shell: #" << shellNum << "; face: #" << facetNum << "]" << endl;
    else
      cout << "\t" << "[shell: #" << idShells[shellNum] << "; face: #" << idFaces[shellNum][facetNum] << "]" << endl;    

    if (messageStr.size() > 0)
      cout << "\t" << messageStr << endl;
    callbackWasCalledWithError = true;
  }
}


void callback_xml(Val3dity_ErrorCode errorCode,    // 0 means status message, -1 means unknown error
                  int shellNum, // -1 means unused; 0-based
                  int facetNum,     // -1 means unused; 0-based
                  std::string messageStr) // optional
{
  if (0 != errorCode)
  {
    callbackWasCalledWithError = true;
    cout << "\t<ValidatorMessage>" << endl;
    cout << "\t\t<type>ERROR</type>" << endl;
    cout << "\t\t<errorCode>" << errorCode << "</errorCode>" << endl;
    if (bUsingIDs == true) {
      cout << "\t\t<shell>" << idShells[shellNum] << "</shell>" << endl;
      cout << "\t\t<face>" << idFaces[shellNum][facetNum] << "</face>" << endl;
    }
    else {
      cout << "\t\t<shell>" << shellNum << "</shell>" << endl;
      cout << "\t\t<face>" << facetNum << "</face>" << endl;
    }
    if (messageStr.empty() == false)
      cout << "\t\t<message>" << messageStr << "</errorCode>" << endl;  
    cout << "\t</ValidatorMessage>" << endl;
  }
  
}



// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main(int argc, char* const argv[])
{
  bool bRepair = false;

  
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
    else {
      arguments.push_back(string(argv[argNum]));
    }
  }

  vector<Shell*> shells;
  if (xmloutput == false) {
    if (bUsingIDs == true) {
      readAllInputShells_withIDs(arguments, shells, idShells, idFaces, callback_cout);
    }
    else {
      readAllInputShells(arguments, shells, callback_cout);
    }
    validate(shells, bRepair, callback_cout);
  }
  else {

    if (bUsingIDs == true) {
      readAllInputShells_withIDs(arguments, shells, idShells, idFaces, callback_xml);
    }
    else {
      readAllInputShells(arguments, shells, callback_xml);
    }
    validate(shells, bRepair, callback_xml);
  }
    

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

