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

#include "validate_2d.h"
#include "validate.h"
#include "CGAL/squared_distance_3.h"
#include <CGAL/linear_least_squares_fitting_3.h>


bool has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface)
{
  bool bDuplicates = false;
  vector< vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    size_t numv = itr->size();
    //-- first-last not the same (they are not in GML format anymore)
    if ((*itr)[0] == (*itr)[numv - 1]) {
      bDuplicates = true;
      break;
    }
    for (int i = 0; i < (static_cast<int>(numv) - 1); i++) {
      if ((*itr)[i] == (*itr)[i+1]) {
        bDuplicates = true;
        break;
      }
    }
  }
  return bDuplicates;
}

bool has_face_rings_toofewpoints(const vector< vector<int> >& theface)
{
  bool bErrors = false;
  vector< vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    if (itr->size() < 3) {
      bErrors = true;
      break;
    }
  }
  return bErrors;
}



bool is_face_planar_distance2plane(const vector<Point3> &pts, double& value, float tolerance)
{
  if (pts.size() == 3) {
    return true;
  }
  //-- find a fitted plane with least-square adjustment
  CgalPolyhedron::Plane_3 plane;
  linear_least_squares_fitting_3(pts.begin(), pts.end(), plane, CGAL::Dimension_tag<0>());  

  //-- test distance to that plane for each point
  vector<Point3>::const_iterator it = pts.begin();
  bool isPlanar = true;
  for ( ; it != pts.end(); it++)
  {
    K::FT d2 = CGAL::squared_distance(*it, plane);
    if ( CGAL::to_double(d2) > (tolerance*tolerance) )
    {
      value = sqrt(CGAL::to_double(d2));
      isPlanar = false;
      break;
    }
  }
  return isPlanar;
}


