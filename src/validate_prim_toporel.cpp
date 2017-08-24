/*
 val3dity - Copyright (c) 2011-2017, Hugo Ledoux.  All rights reserved.
 
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

#include "validate_prim_toporel.h"
#include "geomtools.h"
#include "Solid.h"
#include "CompositeSolid.h"
#include <iostream>
#include <sstream>

namespace val3dity
{

bool do_primitives_overlap(std::vector<Primitive*>& lsPrimitives, COError& coerrs, double tol_overlap)
{
  bool isValid = true;
  //-- 1. create Nef for all primitives and erode if necessary
  std::vector<Nef_polyhedron*> lsNefs;
  for (auto& p : lsPrimitives)
  {
    Nef_polyhedron* tmpnef;
    if (p->get_type() == SOLID)
      tmpnef = dynamic_cast<Solid*>(p)->get_nef_polyhedron();
    else if (p->get_type() == COMPOSITESOLID)
      tmpnef = dynamic_cast<CompositeSolid*>(p)->get_nef_polyhedron();
    else
      continue;
    if (tol_overlap > 0)
    {
      lsNefs.push_back(erode_nef_polyhedron(tmpnef, tol_overlap));
      delete tmpnef;
    }
    else
    {
      lsNefs.push_back(tmpnef);
    }
  }
  //-- 2. check whether pairwise intersection of interiors is empty
  Nef_polyhedron emptynef(Nef_polyhedron::EMPTY);
  for (int i = 0; i < (lsNefs.size() - 1); i++)
  {
    Nef_polyhedron* a = lsNefs[i];
    for (int j = i + 1; j < lsNefs.size(); j++) 
    {
      Nef_polyhedron* b = lsNefs[j];
      if (a->interior() * b->interior() != emptynef)
      {
        std::stringstream msg;
        msg << lsPrimitives[i]->get_id() << " & " << lsPrimitives[j]->get_id();
        coerrs.add_error(601, msg.str(), "");
        isValid = false;
      }
    }
  }
  if (tol_overlap > 0.0)
  {
    for (auto each : lsNefs)
      delete each;
  }
  return !isValid;
}  


} // namespace val3dity
