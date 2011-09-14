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
#include <fstream>

void readShell(ifstream& infile, Shell &allShells);



void readAllInputShells(int numShells, char* const filenames[], vector<Shell*> &shells, cbf cb)
{
   std::stringstream st;
   st << "Reading " << numShells << " file(s).";
   (*cb)(0, -1, -1, st.str());

   st.str(""); //-- clear what's in st
   st << "Reading outer shell:\t" << filenames[1];
   (*cb)(0, -1, -1, st.str());
   ifstream infile(filenames[1], ifstream::in);
   if (!infile)
   {
      (*cb)(999, -1, -1, "Input file doesn't exist.");
      exit(1);
   }

   // Now let's read in the outer shell (the first input file)
   Shell* oneshell = new Shell;
   readShell(infile, *oneshell);

   shells.push_back(oneshell);
   oneshell = NULL; // don't own this anymore
   for (int is=1; is<numShells; is++)
   {
      st.str("");
      st << "Reading inner shell #" << (is-1) << ":\t" << filenames[(is+1)];
      (*cb)(0, -1, -1, st.str());
      ifstream infile2(filenames[(is+1)], ifstream::in);
      if (!infile2)
      {
         (*cb)(999, -1, -1, "Input file doesn't exist.");
         exit(1);
      }

      // Now let's read in the inner shell from the file.
      oneshell = new Shell;
      bool isValid = true;
      readShell(infile2, *oneshell);

      shells.push_back(oneshell);
      oneshell = NULL; // don't own this anymore
   }
   (*cb)(0, -1, -1, "");
}


void readShell(ifstream& infile, Shell &oneshell)
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
    oneshell.lsPts.push_back(p);
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

    oneshell.faces.push_back(pgnids);
  }
}
