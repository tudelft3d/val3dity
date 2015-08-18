
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


#include "validate_solid.h"
#include <CGAL/IO/Polyhedron_iostream.h>

// bool validate_solid_with_nef(vector<CgalPolyhedron*> &polyhedra, cbf cb)
bool validate_solid_with_nef(Solid& sol)
{
  if (sol.num_ishells() == 0)
    return true;
  vector<CgalPolyhedron*> polyhedra;
  polyhedra.push_back(sol.get_oshell()->get_cgal_polyhedron())
  for (auto& ishell : sol.get_ishells())
    polyhedra.push_back(ishell->get_cgal_polyhedron())
    
  bool isValid = true;
  std::stringstream st;
  std::clog << "Inspecting interactions between the " << polyhedra.size() << " shells";
  vector<Nef_polyhedron> nefs;
  vector<CgalPolyhedron*>::const_iterator polyhedraIt;
  for (polyhedraIt = polyhedra.begin(); polyhedraIt != polyhedra.end(); polyhedraIt++)
  {
#ifdef VAL3DITY_USE_EPECSQRT
     Nef_polyhedron onef(**polyhedraIt);
#else
     std::stringstream offrep (stringstream::in | stringstream::out);
     offrep << **polyhedraIt;
     PolyhedronExact pe;
     offrep >> pe;
     Nef_polyhedron onef(pe);
//    std::cout << "convertion to exact polyhedron done." << std::endl;
#endif

     nefs.push_back(onef);
  }
  vector<Nef_polyhedron>::iterator nefsIt = nefs.begin();
  Nef_polyhedron nef;
  nef += (*nefsIt);
  nefsIt++;
  int numvol = 2;
  bool success = true;
  for ( ; nefsIt != nefs.end(); nefsIt++) 
  {
    nef -= (*nefsIt);
  	nef.regularization();
    numvol++;
    if (nef.number_of_volumes() != numvol)
    {
      success = false;
      break;
    }
  }
  if (success == false) //-- the Nef is not valid, pairwise testing to see what's wrong
  {
    isValid = false;
//-- start with oshell<-->ishells
    nefsIt = nefs.begin();
    nefsIt++;
    int no = 1;
    for ( ; nefsIt != nefs.end(); nefsIt++) 
    {
      nef.clear();
      nef += *(nefs.begin());
      nef -= *nefsIt;
      nef.regularization();	
      if (nef.number_of_volumes() != 3)
      {
        if (nef.number_of_volumes() > 3)
        {
          //-- check if ishell is a subset of oshell
          if ((*nefsIt <= nefs[0]) == true)
            sol.add_error(404, 0, no, "");
          else
          {
            sol.add_error(402, 0, no, "");
            sol.add_error(404, 0, no, "");
          }
        }
        else //-- nef.number_of_volumes() < 3
        {
          //-- perform union
          nef.clear();
          nef += *(nefs.begin());
          nef += *nefsIt;
          nef.regularization();
          if (nef.number_of_volumes() == 3)
            sol.add_error(403, -1, -1, "");
          else
          {
            if ((*nefsIt <= nefs[0]) == true)
              sol.add_error(401, 0, no, "");
            else
            {
              nef.clear();
              nef = nefs[0].intersection(nefsIt->interior());
              nef.regularization();
              if (nef.is_empty() == true)
              {
                sol.add_error(401, 0, no, "");
                sol.add_error(403, 0, no, "");
              }
              else
                sol.add_error(402, 0, no, "");
            }
          }
        }
      }
    no++;
    }

//-- then check ishell<-->ishell interactions
    nefsIt = nefs.begin();
    nefsIt++;
    vector<Nef_polyhedron>::iterator nefsIt2;
    no = 1;
    int no2;
    for ( ; nefsIt != nefs.end(); nefsIt++)
    {
      nefsIt2 = nefsIt;
      nefsIt2++;
      no2 = no + 1;
      for ( ; nefsIt2 != nefs.end(); nefsIt2++)
      {
        nef.clear();
        nef += *nefsIt;
        nef += *nefsIt2;
		    nef.regularization();
        if (nef.number_of_volumes() > 3)
          sol.add_error(402, no, no2, "Both shells completely overlap");
        else if (nef.number_of_volumes() < 3)
        {
          //-- either they are face adjacent or overlap
          nef.clear();
          nef = nefsIt->interior();
          nef = nef.intersection(nefsIt2->interior());
		      nef.regularization();
          if (nef.is_empty() == true)
            sol.add_error(401, no, no2, "");
          else
            sol.add_error(402, no, no2, "");
        }
        no2++;
      }
      no++;
    }
  }
  return isValid;
}




