/*
 val3dity - Copyright (c) 2011, Hugo Ledoux.  All rights reserved.
 
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

// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
void callback_cout(int errorCode,    // 0 means status message, -1 means unknown error
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
      case 100   : cout << "Error 100: " << "2+ consecutive points"; break;
      case 110   : cout << "Error 110: " << "ring is not closed (first-last point are not the same)"; break;
        // Surface level
      case 200   : cout << "Error 200: " << "oring and irings have same orientation"; break;
      case 210   : cout << "Error 210: " << "surface is not planar"; break;
      case 220   : cout << "Error 220: " << "surface is not valid in 2D (it's projection)"; break;
      case   221 : cout << "Error 221: " << "iring intersect oring"; break;
      case   222 : cout << "Error 222: " << "iring outside oring"; break;
      case   223 : cout << "Error 223: " << "oring and iring(s) intersect"; break;
      case   224 : cout << "Error 224: " << "interior not connected"; break;
        // Shell level
      case 300   : cout << "Error 300: " << "is not a 2-manifold"; break;
      case   301 : cout << "Error 301: " << "surface is not closed"; break;
      case   302 : cout << "Error 302: " << "dangling faces (more than 2 surfaces incident to an edge)"; break;
      case   303 : cout << "Error 303: " << "orientation of faces not correct (edge not used 2 times: one in each direction)"; break;
      case   304 : cout << "Error 304: " << "faces not connected to the 2-manifold (eg 'floating' in the air)"; break;
      case   305 : cout << "Error 305: " << "surface self-intersect"; break;
      case 310   : cout << "Error 310: " << "normales pointing in wrong direction (oshell=outwards; ishell=inwards)"; break;
        // Solid level
      case 400   : cout << "Error 400: " << "shells are face adjacent"; break;
      case 410   : cout << "Error 410: " << "interior of shells intersect"; break;
      case 420   : cout << "Error 420: " << "ishell outside the oshell"; break;
      case 430   : cout << "Error 430: " << "interior not connected"; break;
        // Input problem
      case 999   : cout << "Error 999: " << "input file is not valid"; break;
         // Other reasons
      default    : cout << "Error: invalid for unknown reasons (but for sure invalid!)"; break;
      }
      cout << endl;
      cout << "\t" << "[shell: #" << shellNum << "; face: #" << facetNum << "]" << endl;
      if (messageStr.size() > 0)
        cout << "\t" << messageStr << endl;
      callbackWasCalledWithError = true;
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

  vector<Shell*> shells;
  readAllInputShells((argc-1), argv, shells, callback_cout);
  validate(shells, bRepair, callback_cout);

  if (callbackWasCalledWithError)
  {
     cout << "\nInvalid solid :(" << endl << endl;
     return(1);
  }
  else
  {
     cout << "\nValid solid. Hourrraaa!" << endl;
     return(0);
  }
}

