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
#include <fstream>
#include <string>

void readShell(ifstream& infile, Shell &allShells);
void readShell_withIDs(ifstream& infile, Shell &allShells, vector<string> &idShells, vector< vector<string> > &idFaces);


void readAllInputShells_withIDs(vector<string> &arguments, vector<Shell*> &shells, vector<string> &idShells, vector< vector<string> > &idFaces, cbf cb)
{
  std::stringstream st;
  st << "Reading " << arguments.size() << " file(s).";
  (*cb)(STATUS_OK, -1, -1, st.str());
  
  st.str(""); //-- clear what's in st
  st << "Reading outer shell:\t" << arguments[0];
  (*cb)(STATUS_OK, -1, -1, st.str());
  ifstream infile(arguments[0].c_str(), ifstream::in);
  if (!infile)
  {
    (*cb)(INVALID_INPUT_FILE, -1, -1, "Input file doesn't exist.");
    exit(1);
  }
  
  // Now let's read in the outer shell (the first input file)
  Shell* oneshell = new Shell;
  readShell_withIDs(infile, *oneshell, idShells, idFaces);
  
  shells.push_back(oneshell);
  oneshell = NULL; // don't own this anymore
  
  vector<string>::const_iterator it = arguments.begin();
  it++;
  int i = 0;
  for ( ; it < arguments.end(); it++)
  {
    st.str("");
    st << "Reading inner shell #" << i << ":\t" << *it;
    i++;
    (*cb)(STATUS_OK, -1, -1, st.str());
    ifstream infile2(it->c_str(), ifstream::in);
    if (!infile2)
    {
      (*cb)(INVALID_INPUT_FILE, -1, -1, "Input file doesn't exist.");
      exit(1);
    }
    
    // Now let's read in the inner shell from the file.
    oneshell = new Shell;
    //bool isValid = true;
    readShell_withIDs(infile2, *oneshell, idShells, idFaces);
    
    shells.push_back(oneshell);
    oneshell = NULL; // don't own this anymore
  }
  (*cb)(STATUS_OK, -1, -1, "");
}

void readAllInputShells(vector<string> &arguments, vector<Shell*> &shells, cbf cb)
{
  std::stringstream st;
  st << "Reading " << arguments.size() << " file(s).";
  (*cb)(STATUS_OK, -1, -1, st.str());
  
  st.str(""); //-- clear what's in st
  st << "Reading outer shell:\t" << arguments[0];
  (*cb)(STATUS_OK, -1, -1, st.str());
  ifstream infile(arguments[0].c_str(), ifstream::in);
  if (!infile)
  {
    (*cb)(INVALID_INPUT_FILE, -1, -1, "Input file doesn't exist.");
    exit(1);
  }
  
  // Now let's read in the outer shell (the first input file)
  Shell* oneshell = new Shell;
  readShell(infile, *oneshell);
  
  shells.push_back(oneshell);
  oneshell = NULL; // don't own this anymore
  
  vector<string>::const_iterator it = arguments.begin();
  it++;
  int i = 0;
  for ( ; it < arguments.end(); it++)
  {
    st.str("");
    st << "Reading inner shell #" << i << ":\t" << *it;
    i++;
    (*cb)(STATUS_OK, -1, -1, st.str());
    ifstream infile2(it->c_str(), ifstream::in);
    if (!infile2)
    {
      (*cb)(INVALID_INPUT_FILE, -1, -1, "Input file doesn't exist.");
      exit(1);
    }
    
    // Now let's read in the inner shell from the file.
    oneshell = new Shell;
    //bool isValid = true;
    readShell(infile2, *oneshell);
    
    shells.push_back(oneshell);
    oneshell = NULL; // don't own this anymore
  }
  (*cb)(STATUS_OK, -1, -1, "");
}
  
 

void readShell(ifstream& infile, Shell &oneshell)
{
  //-- read the points
  int num, tmpint;
  float tmpfloat;
  infile >> num >> tmpint >> tmpint >> tmpint;
  vector< Point3 >::iterator iPoint3;
  //-- read first line to decide if 0- or 1-based indexing
  bool zerobased = true;
  Point3 p;
  infile >> tmpint >> p;
  oneshell.lsPts.push_back(p);
  if (tmpint == 1)
  {
    zerobased = false;
    cout << "1-based indexing file!" << endl;
  }
  //-- process other vertices
  for (int i = 1; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
    oneshell.lsPts.push_back(p);
  }

  //-- read the facets
  infile >> num >> tmpint;
  int numf, numpt, numholes;
  string s;
  for (int i = 0; i < num; i++)
  {
    numholes = 0;
    infile >> numf;
    while(true) {
      if (infile.peek() == '\n')
        break;
      else if (infile.peek() == ' ')
        infile.ignore();
      else
        infile >> numholes;
    }

    //-- read oring (there's always one and only one)
    infile >> numpt;
    vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];
    if (zerobased == false)
    {
      for (int k = 0; k < numpt; k++)
        ids[k] = (ids[k] - 1);      
    }

    vector< vector<int> > pgnids;
    pgnids.push_back(ids);

    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];
      if (zerobased == false)
      {
        for (int k = 0; k < numpt; k++)
          ids[k] = (ids[k] - 1);      
      }
      pgnids.push_back(ids);
    }
    //-- skip the line about points defining holes (if present)
    for (int j = 0; j < numholes; j++)
      infile >> tmpint >> tmpfloat >> tmpfloat >> tmpfloat;

    oneshell.faces.push_back(pgnids);
  }
}


void readShell_withIDs(ifstream& infile, Shell &oneshell, vector<string> &idShells, vector< vector<string> > &idFaces)
{
  //-- read the id of the shell
  char dash;
  string sID;
  int num, tmpint;
  infile >> dash >> sID;
  idShells.push_back(sID);
  infile >> dash >> tmpint;
  vector<string> tempIDs;
  //-- read the points
  float tmpfloat;
  infile >> num >> tmpint >> tmpint >> tmpint;
  vector< Point3 >::iterator iPoint3;
  //-- read first line to decide if 0- or 1-based indexing
  bool zerobased = true;
  Point3 p;
  infile >> tmpint >> p;
  oneshell.lsPts.push_back(p);
  if (tmpint == 1)
  {
    zerobased = false;
    cout << "1-based indexing file!" << endl;
  }
  //-- process other vertices
  for (int i = 1; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
    oneshell.lsPts.push_back(p);
  }
  
  //-- read the facets
  infile >> num >> tmpint;
  int numf, numpt;
  string s;
  for (int i = 0; i < num; i++)
  {
    //    cout << "---- face ---- " << i << endl;
    infile >> numf >> tmpint >> dash >> sID;
    tempIDs.push_back(sID);
//    cout << sID << endl;
    //-- read oring (there's always one and only one)
    infile >> numpt;
    vector<int> ids(numpt);
    for (int k = 0; k < numpt; k++)
      infile >> ids[k];
    if (zerobased == false)
    {
      for (int k = 0; k < numpt; k++)
        ids[k] = (ids[k] - 1);      
    }
    
    vector< vector<int> > pgnids;
    pgnids.push_back(ids);
    
    //-- check for irings
    for (int j = 1; j < numf; j++)
    {
      infile >> numpt;
      vector<int> ids(numpt);
      for (int l = 0; l < numpt; l++)
        infile >> ids[l];
      if (zerobased == false)
      {
        for (int k = 0; k < numpt; k++)
          ids[k] = (ids[k] - 1);      
      }
      
      pgnids.push_back(ids);
    }
    //-- skip the lines about point defining the hole (mandatory in a POLY file)
    for (int j = 1; j < numf; j++)
      infile >> tmpint >> tmpfloat >> tmpfloat >> tmpfloat;
    
    oneshell.faces.push_back(pgnids);
  }
  idFaces.push_back(tempIDs);
}
