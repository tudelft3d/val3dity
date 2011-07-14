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

// STL library
#include <fstream>

void readShell(ifstream& infile, polyhedraShell &allShells);

void readAllPolyhedraShells(int numShells, char* const filenames[], vector<polyhedraShell*> &polyhedraShells)
{
   cout << "Processing " << numShells << " file(s)." << endl << endl;

   cout << "Reading outer shell: " << filenames[1] << endl;
   ifstream infile(filenames[1], ifstream::in);
   if (!infile)
   {
      cout << "Error. File not there." << endl;
      exit(1);
   }

   // Now let's read in the outer shell from the file.
   polyhedraShell* fshell = new polyhedraShell;
   readShell(infile, *fshell);

   polyhedraShells.push_back(fshell);
   fshell = NULL; // don't own this anymore
   for (int is=1; is<numShells; is++)
   {
      cout << "Reading inner shell #" << (is-1) << filenames[(is+1)] << endl;
      ifstream infile2(filenames[(is+1)], ifstream::in);
      if (!infile2)
      {
         cout << "Error. File not there." << endl;
         exit(1);
      }

      // Now let's read in the inner shell from the file.
      fshell = new polyhedraShell;
      bool isValid = true;
      readShell(infile2, *fshell);

      polyhedraShells.push_back(fshell);
      fshell = NULL; // don't own this anymore
   }
}


void readShell(ifstream& infile, polyhedraShell &allShells)
{
  //-- read the points
  int num, tmpint;
  float tmpfloat;
  infile >> num >> tmpint >> tmpint >> tmpint;
  vector< Point3 >::iterator iPoint3;
  for (int i = 0; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
    allShells.lsPts.push_back(p);
  }

  //-- read the facets
  infile >> num >> tmpint;
  int numf, numpt;
  for (int i = 0; i < num; i++)
  {
//    cout << "---- face ---- " << i << endl;
    infile >> numf >> tmpint;
    //-- read oring (there's always one and only one)
    infile >> numpt;
    vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];

    vector< vector<int> > pgnids;
    pgnids.push_back(ids);

    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];

      pgnids.push_back(ids);
    }
    //-- skip the line about point defining the hole (mandatory in a POLY file)
    if (numf > 1)
      infile >> tmpint >> tmpfloat >> tmpfloat >> tmpfloat;

    allShells.shells.push_back(pgnids);
  }
}
