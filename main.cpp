/*
Copyright (c) 2011, Hugo Ledoux
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgment:
   This product includes software developed by the <organization>.
4. Neither the name of the <organization> nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "input.h"
#include "validate.h"

// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
int main(int argc, char* const argv[])
{

  if (argc < 2)
  {
    cout << "You have to give at least one input POLY file." << endl;
    cout << endl << "Usage: <program> ./src/data/cube.poly ./src/data/py1.poly" << endl;
    cout << "This example would validate a solid with the outer polyhedra from cube.poly and one inner void from py1.poly" << endl;
    return(1);
  }

  vector<polyhedraShell*> polyhedraShells;
  readAllPolyhedraShells((argc-1), argv, polyhedraShells);

  vector<invalidItem> invalidItems;
  validatePolyHedra(polyhedraShells, invalidItems);
  if (invalidItems.size() > 0)
  {
     cout << "Invalid solid :(" << endl << endl;
     for(unsigned int i(0); i<invalidItems.size(); i++)
     {
        cout << "Error #" << i << ":  errorCode=" << invalidItems[i].errorCode
             << "     Polyhedra #" << invalidItems[i].polyhedraNum << "       ";
        switch(invalidItems[i].errorCode)
        {
           // Ring level
        case 100   : cout << "2+ consecutive points"; break;
        case 110   : cout << "ring is not closed (first-last point are not the same)"; break;
           // Surface level
        case 200   : cout << "oring and irings have same orientation"; break;
        case 210   : cout << "surface is not planar"; break;
        case 220   : cout << "surface is not valid in 2D (it's projection)"; break;
        case   221 : cout << "iring intersect oring"; break;
        case   222 : cout << "iring outside oring"; break;
        case   223 : cout << "oring and iring(s) intersect"; break;
        case   224 : cout << "interior not connected"; break;
           // Shell level
        case 300   : cout << "is not a 2-manifold"; break;
        case   301 : cout << "surface is not closed"; break;
        case   302 : cout << "dangling faces (more than 2 surface incident to an edge)"; break;
        case   303 : cout << "faces not connected to the 2-manifold (eg 'floating' in the air)"; break;
        case   304 : cout << "orientation of faces not correct (edge not used 2 times: one in each direction)"; break;
        case   305 : cout << "surface self-intersect"; break;
        case 310   : cout << "normales not pointing in correct direction (oshell=outwards; ishell=inwards)"; break;
           // Solid level
        case 400   : cout << "shells are face adjacent"; break;
        case 410   : cout << "interior of shells intersect"; break;
        case 420   : cout << "ishell outside the oshell"; break;
        case 430   : cout << "interior not connected"; break;
        default    : cout << "unknown reason"; break;
        }
        cout << endl;
     }
     return(1);
  }
  else
  {
     cout << "Valid solid. Hourrraaa!" << endl;
     return(0);
  }
}

