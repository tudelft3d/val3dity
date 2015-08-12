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
#include <fstream>
#include <string>

void readGMLfile(string &ifile, vector<Shell*> &shells, double tol_snapping, cbf cb, bool translatevertices);

void readShell(ifstream& infile, Shell &allShells, int noshell, cbf cb, bool translatevertices);
void readShell_withIDs(ifstream& infile, Shell &allShells, vector<string> &idShells, vector< vector<string> > &idFaces);
void translate_vertices(vector< Point3 > &lsPts);
std::string localise(std::string s);

/////

//-- ignore XML namespace
std::string localise(std::string s)
{
  return "*[local-name(.) = '" + s + "']";
}

bool cmpPoint3(Point3 &p1, Point3 &p2, double tol)
{
  if ( (p1 == p2) || (CGAL::squared_distance(p1, p2) <= (tol * tol)) )
    return true;
  else
    return false;
}


void readGMLfile(string &ifile, vector<Shell*> &shells, double tol_snapping, cbf cb, bool translatevertices) 
{
  pugi::xml_document doc;
  if (!doc.load_file(ifile.c_str())) {
    std::cout << "FILE DOESN'T EXIST" << std::endl;
    return;
  }
  std::string s = "//" + localise("Solid");
  pugi::xpath_query myquery(s.c_str());
  pugi::xpath_node_set nsolids = myquery.evaluate_node_set(doc);
  std::cout << "# of Solids: " << nsolids.size() << std::endl;

  Point3 p(0.1, 0.1, 0.0);
  Point3 p2(0.1005, 0.1006, 0.001);
  std::cout << "equal: " << cmpPoint3(p, p2, tol_snapping) << std::endl;
}

void readAllInputShells_withIDs(vector<string> &arguments, vector<Shell*> &shells, vector<string> &idShells, vector< vector<string> > &idFaces, cbf cb)
{
  std::stringstream st;
  st << "Reading " << arguments.size() << " file(s).";
  (*cb)(0, -1, -1, st.str());
  
  st.str(""); //-- clear what's in st
  st << "Reading outer shell:\t" << arguments[0];
  (*cb)(0, -1, -1, st.str());
  ifstream infile(arguments[0].c_str(), ifstream::in);
  if (!infile)
  {
    (*cb)(901, -1, -1, "Input file doesn't exist.");
    return;
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
    (*cb)(0, -1, -1, st.str());
    ifstream infile2(it->c_str(), ifstream::in);
    if (!infile2)
    {
      (*cb)(901, -1, -1, "Input file doesn't exist.");
      return;
    }
    
    // Now let's read in the inner shell from the file.
    oneshell = new Shell;
    //bool isValid = true;
    readShell_withIDs(infile2, *oneshell, idShells, idFaces);
    
    shells.push_back(oneshell);
    oneshell = NULL; // don't own this anymore
  }
  (*cb)(0, -1, -1, "");
}

void readAllInputShells(string &foshell, vector<string> &fishells, vector<Shell*> &shells, cbf cb, bool translatevertices)
{
  std::stringstream st;
  st << "Reading " << (fishells.size() + 1) << " file(s).";
  (*cb)(0, -1, -1, st.str());
  
  st.str(""); //-- clear what's in st
  st << "Reading outer shell:\t" << foshell;
  (*cb)(0, -1, -1, st.str());
  ifstream infile(foshell.c_str(), ifstream::in);
  if (!infile)
  {
    (*cb)(901, -1, -1, "Input file doesn't exist.");
    return;
  }
  
  int is = 0; //-- shell index for reporting errors
  // Now let's read in the outer shell (the first input file)
  Shell* oneshell = new Shell;
  readShell(infile, *oneshell, is, cb, translatevertices);
  is++;
  
  shells.push_back(oneshell);
  oneshell = NULL; // don't own this anymore
  
  vector<string>::const_iterator it = fishells.begin();
  int i = 1;
  for ( ; it < fishells.end(); it++)
  {
    st.str("");
    st << "Reading inner shell #" << i << ":\t" << *it;
    i++;
    (*cb)(0, -1, -1, st.str());
    ifstream infile2(it->c_str(), ifstream::in);
    if (!infile2)
    {
      (*cb)(901, -1, -1, "Input file doesn't exist.");
      return;
    }
    
    // Now let's read in the inner shell from the file.
    oneshell = new Shell;
    //bool isValid = true;
    readShell(infile2, *oneshell, is, cb, translatevertices);
    is++;
    
    shells.push_back(oneshell);
    oneshell = NULL; // don't own this anymore
  }
  (*cb)(0, -1, -1, "");
}
  
 

void readShell(ifstream& infile, Shell &oneshell, int noshell, cbf cb, bool translatevertices)
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
  }
  //-- process other vertices
  for (int i = 1; i < num; i++)
  {
    Point3 p;
    infile >> tmpint >> p;
    oneshell.lsPts.push_back(p);
  }
  //-- translate all vertices to (minx, miny)
  if (translatevertices == true)
  {
    translate_vertices(oneshell.lsPts);
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
    if (numpt == -1) {
      (*cb)(103, noshell, i, "");
      continue;
    }
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
      if (numpt == -1) {
        (*cb)(103, noshell, i, "");
        continue;
      }
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


void translate_vertices(vector< Point3 > &lsPts)
{
  vector<Point3>::iterator it = lsPts.begin();
  K::FT minx = 9e10;
  K::FT miny = 9e10;
  for ( ; it != lsPts.end(); it++)
  {
    if (it->x() < minx)
      minx = it->x();
    if (it->y() < miny)
      miny = it->y();
  }
  for (it = lsPts.begin(); it != lsPts.end(); it++)
  {
    Point3 tp(CGAL::to_double(it->x() - minx), CGAL::to_double(it->y() - miny), CGAL::to_double(it->z()));
    *it = tp;
  }
}


