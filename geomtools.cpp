/*
 val3dity - Copyright (c) 2011-2016, Hugo Ledoux.  All rights reserved.
 
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

#include "geomtools.h"
#include "CGAL/squared_distance_3.h"
#include <CGAL/linear_least_squares_fitting_3.h>


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


int projection_plane(const vector< Point3 > &lsPts, const vector<int> &ids)
{
  Vector n;
  polygon_normal(lsPts, ids, n);
  double maxcomp = abs(n.x());
  int proj = 0;
  if (abs(n.y()) > maxcomp)
  {
    maxcomp = abs(n.y());
    proj = 1;
  }
  if (abs(n.z()) > maxcomp)
  {
    maxcomp = abs(n.z());
    proj = 2;
  }
  return proj;
}


bool cmpPoint3(Point3 &p1, Point3 &p2, double tol)
{
  if ( (p1 == p2) || (CGAL::squared_distance(p1, p2) <= (tol * tol)) )
    return true;
  else
    return false;
}


bool polygon_normal(const vector< Point3 > &lsPts, const vector<int> &ids, Vector &n) 
{
  vector<Point3> pts;
  for (auto& i : ids) 
    pts.push_back(lsPts[i]);
  CgalPolyhedron::Plane_3 plane;
  linear_least_squares_fitting_3(pts.begin(), pts.end(), plane, CGAL::Dimension_tag<0>()); 
  n = plane.orthogonal_vector();
  return true;
}  


bool create_polygon(const vector<Point3>& lsPts, const vector<int>& ids, Polygon &pgn, bool ccworient)
{
  int proj = projection_plane(lsPts, ids);
  vector<int>::const_iterator it = ids.begin();
  for ( ; it != ids.end(); it++)
  {
    Point3 p = lsPts[*it];
    if (proj == 2)
      pgn.push_back(Point2(p.x(), p.y()));
    else if (proj == 1)
      pgn.push_back(Point2(p.x(), p.z()));
    else if (proj == 0)
      pgn.push_back(Point2(p.y(), p.z()));
  }
  
  if (!pgn.is_simple()) //-- CGAL polygon requires that a polygon be simple to test orientation
    return false;
  if (pgn.orientation() == CGAL::COLLINEAR)
    return false;
  if ( (ccworient == true) && (pgn.is_counterclockwise_oriented() == false) )
    pgn.reverse_orientation();
  return true;
}

bool is_face_planar_normals(const vector<int*> &trs, const vector<Point3>& lsPts, double& value, float angleTolerance)
{
  vector<int*>::const_iterator ittr = trs.begin();
  int* a = *ittr;
  Vector v0 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]]);
  ittr++;
  bool isPlanar = true;
  for ( ; ittr != trs.end(); ittr++)
  {
    a = *ittr;
    Vector v1 = unit_normal( lsPts[a[0]], lsPts[a[1]], lsPts[a[2]] );
    Vector a = CGAL::cross_product(v0, v1);
    K::FT norm = sqrt(a.squared_length());
    double dot = CGAL::to_double((v0*v1));
    double angle = atan2(CGAL::to_double(norm), dot);
    if (angle*180/PI > angleTolerance)
    {
      // cout << "\t---angle: " << angle*180/PI << endl;
      value = angle*180/PI;
      isPlanar = false;
      break;
    }
  }
  return isPlanar;
}
