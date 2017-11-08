 /*
  val3dity 

  Copyright (c) 2011-2017, Hugo Ledoux  

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
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
  for (int i = 0; i < lsNefs.size(); i++)
  {
    Nef_polyhedron* a = lsNefs[i];
    for (int j = i + 1; j < lsNefs.size(); j++) 
    {
      Nef_polyhedron* b = lsNefs[j];
      if (a->interior() * b->interior() != emptynef)
      {
        std::stringstream msg;
        msg << lsPrimitives[i]->get_id() << " and " << lsPrimitives[j]->get_id();
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
