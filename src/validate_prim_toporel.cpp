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

typedef std::vector<Nef_polyhedron*>                                    Nefs;
typedef Nefs::iterator                                                  Iterator;
typedef CGAL::Box_intersection_d::Box_with_handle_d<double,3,Iterator>  AABB;


struct Report {
  Nefs* nefs;
  std::vector<std::string>* lsCellIDs;
  std::vector<int>* ll2;

  Report(Nefs& nefs, std::vector<std::string>& lsCell, std::vector<int>& ll)
    : nefs(&nefs), lsCellIDs(&lsCell), ll2(&ll)
  {
    // lsCellIDs = lsCell;
  }

  // callback functor that reports all truly intersecting triangles
  void operator()(const AABB& a, const AABB& b)  
  {
    std::cout << "Box " << (a.handle() - nefs->begin()) << " and "
              << (b.handle() - nefs->begin()) << " intersect";
    std::cout << "-->CHECK IF REAL INTERSECTION" << std::endl;
    int box1 = (a.handle() - nefs->begin());
    int box2 = (b.handle() - nefs->begin());
    Nef_polyhedron* tmp = nefs->at(box1);
    std::cout << "id: " << lsCellIDs->at(box1) << std::endl;
    std::cout << "id: " << lsCellIDs->at(box2) << std::endl;
    std::cout << ll2->size() << std::endl;
    ll2->push_back(box2);
//    std::cout << a.handle() << std::endl;
    // if ( ! a.handle()->is_degenerate() && ! b.handle()->is_degenerate()
    //      && CGAL::do_intersect( *(a.handle()), *(b.handle()))) {
    // std::cout << ", and the triangles intersect also";
    // }
  }
};


bool test2(std::vector<std::tuple<std::string,Solid*>>& lsCells,
          int errorcode_to_assign, 
          std::vector<Error>& lsErrors, 
          double tol_overlap)
{
  std::vector<Nef_polyhedron*> lsNefs;
  std::vector<std::string>     lsCellIDs;
  for (auto& c : lsCells)
  {
    Solid* ts = std::get<1>(c);
    if (ts->is_valid() != 1)
      continue;
    Nef_polyhedron* tmpnef = ts->get_nef_polyhedron();
    if (tol_overlap > 0)
    {
      lsNefs.push_back(erode_nef_polyhedron(tmpnef, tol_overlap));
      delete tmpnef;
    }
    else
      lsNefs.push_back(tmpnef);
    lsCellIDs.push_back(std::get<0>(c));
  }
  
  std::vector<AABB> aabbs;
  
  int counter = 0;
  for ( Iterator i = lsNefs.begin(); i != lsNefs.end(); ++i)
  {
    Solid* ts = std::get<1>(lsCells[counter]);
    aabbs.push_back( AABB( ts->get_bbox(), i) );
    counter++;
  }

  std::vector<int> ll;
  ll.push_back(99);
  CGAL::box_self_intersection_d( aabbs.begin(), aabbs.end(), Report(lsNefs, lsCellIDs, ll));

  std::cout << "size: " << ll.size() << std::endl;
  return true;
}


bool test(std::vector<Primitive*>& lsPrimitives, 
          int errorcode_to_assign, 
          std::vector<Error>& lsErrors, 
          double tol_overlap)
{
  // std::vector<Solid*> solids;
  // for (auto& p : lsPrimitives)
  //   solids.push_back(dynamic_cast<Solid*>(p));
  // std::vector<AABB> aabbs;
  
  // for ( Iterator i = solids.begin(); i != solids.end(); ++i)
  //   aabbs.push_back( AABB( (*i)->get_bbox(), i) );

  // CGAL::box_self_intersection_d( aabbs.begin(), aabbs.end(), Report(solids, 37));

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
