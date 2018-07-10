 /*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

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
#include "Primitive.h"
#include "geomtools.h"
#include "Solid.h"
#include "CompositeSolid.h"
#include <iostream>
#include <sstream>

#include <CGAL/box_intersection_d.h>

namespace val3dity
{

typedef std::vector<Solid*>                                             Solids;
typedef Solids::iterator                                                Iterator;
typedef CGAL::Box_intersection_d::Box_with_handle_d<double,3,Iterator>  AABB;
// typedef CGAL::Box_intersection_d::Box_d<double,3> AABB;


// void callback( const AABB& a, const AABB& b ) {
//     std::cout << "box " << a.id() << " intersects box " << b.id() << std::endl;
// }


struct Report {
  Solids* solids;

  Report(Solids& solids)
    : solids(&solids)
  {}

  // callback functor that reports all truly intersecting triangles
  void operator()(const AABB& a, const AABB& b) const 
  {
    std::cout << "Box " << (a.handle() - solids->begin()) << " and "
              << (b.handle() - solids->begin()) << " intersect";
    std::cout << "-->CHECK IF REAL INTERSECTION" << std::endl;
    int box1 = (a.handle() - solids->begin());
    int box2 = (b.handle() - solids->begin());
    Solid* tmp = solids->at(box1);
    std::cout << tmp->num_faces() << std::endl;
//    std::cout << a.handle() << std::endl;
    // if ( ! a.handle()->is_degenerate() && ! b.handle()->is_degenerate()
    //      && CGAL::do_intersect( *(a.handle()), *(b.handle()))) {
    // std::cout << ", and the triangles intersect also";
    // }
  }
};



bool test(std::vector<Primitive*>& lsPrimitives, 
          int errorcode_to_assign, 
          std::vector<Error>& lsErrors, 
          double tol_overlap)
{
  std::vector<Solid*> solids;
  for (auto& p : lsPrimitives)
    solids.push_back(dynamic_cast<Solid*>(p));
  std::vector<AABB> aabbs;
  
  for ( Iterator i = solids.begin(); i != solids.end(); ++i)
    aabbs.push_back( AABB( (*i)->get_bbox(), i));

  CGAL::box_self_intersection_d( aabbs.begin(), aabbs.end(), Report(solids));

  return true;
}




bool do_primitives_interior_overlap(std::vector<Primitive*>& lsPrimitives, 
                           int errorcode_to_assign, 
                           std::vector<Error>& lsErrors, 
                           double tol_overlap)
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
        Error e;
        std::stringstream msg;
        msg << lsPrimitives[i]->get_id() << " and " << lsPrimitives[j]->get_id();
        e.errorcode = errorcode_to_assign;
        e.info1 = msg.str();
        e.info2 = "";
        lsErrors.push_back(e);
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
