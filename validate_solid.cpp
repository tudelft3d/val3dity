
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


#include "validate_solid.h"
#include <CGAL/IO/Polyhedron_iostream.h>



bool validate_solid_with_nef(vector<CgalPolyhedron*> &polyhedra, bool bRepair, cbf cb)
{
  if (polyhedra.size() <= 1)
    return true;
    
  bool isValid = true;
  std::stringstream st;
  st << "Inspecting interactions between the " << polyhedra.size() << " shells";
  (*cb)(0, -1, -1, st.str());
  vector<Nef_polyhedron> nefs;
  vector<CgalPolyhedron*>::const_iterator polyhedraIt;
  for (polyhedraIt = polyhedra.begin(); polyhedraIt != polyhedra.end(); polyhedraIt++)
  {
     std::stringstream offrep (stringstream::in | stringstream::out);
     offrep << **polyhedraIt;
     PolyhedronExact pe;
     offrep >> pe;
     Nef_polyhedron onef(pe);
     nefs.push_back(onef);
  }
  vector<Nef_polyhedron>::iterator nefsIt = nefs.begin();

  Nef_polyhedron solid;
  solid += (*nefsIt);
  nefsIt++;
  int numvol = 2;
  bool success = true;
  for ( ; nefsIt != nefs.end(); nefsIt++) 
  {
    solid -= *nefsIt;
    numvol++;
    if (solid.number_of_volumes() != numvol)
    {
      cout << "!!!WRONG SOLID!!!" << endl;
      success = false;
      break;
    }
  }
  
  if (success == false) //-- the Nef is not valid, pairwise testing to see what's wrong
  {
    //-- start with oshell<-->ishells
    nefsIt = nefs.begin();
    nefsIt++;
    int no = 1;
    for ( ; nefsIt != nefs.end(); nefsIt++) 
    {
      solid.clear();
      solid += *(nefs.begin());
      solid -= *nefsIt;
      if (solid.number_of_volumes() != 3)
      {
        cout << "%%%ERROR: oshell/ishell #" << no << endl;
        if (solid.number_of_volumes() < 3)
      }
      no++;
    }
    
    
  }
  
  
  cout << "# of volumes: " << solid.number_of_volumes() << endl;
  
  
  if (solid.number_of_volumes() != (polyhedra.size()+1))
  {
     (*cb)(401, -1, -1, "Shells do not interact according to the rules.");
     isValid = false;
     //TODO: add the exact errors here...
  }
  return isValid;
}




