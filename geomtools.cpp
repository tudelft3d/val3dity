//
//  geomtools.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 14/08/15.
//
//

#include "geomtools.h"

int projection_plane(const vector< Point3 > &lsPts, const vector<int> &ids)
{
  Vector* pnormal = polygon_normal(lsPts, ids);
  K::FT TOL(1e-12); //-- tolerance
  // K::FT TOL(1e-8); //-- tolerance
  if (CGAL::compare(sqrt(pnormal->squared_length()), TOL) != CGAL::LARGER)
  {
    return -1;
  }
  //-- normalise the normal
  *pnormal = *pnormal / sqrt(pnormal->squared_length());
  // need to use K::FT instead of double to ensure compilation under core level 4
  K::FT a = abs(*pnormal * Vector(1.0, 0.0, 0.0));//yz
  K::FT b = abs(*pnormal * Vector(0.0, 1.0, 0.0));//xz
  K::FT c = abs(*pnormal * Vector(0.0, 0.0, 1.0));//xy
  K::FT m = max(max(a, b), c);
  delete pnormal;
  if (CGAL::compare(a, m) == CGAL::EQUAL)
  {
    return 0;//yz
  }
  else if (CGAL::compare(b, m) == CGAL::EQUAL)
  {
    return 1;//xz
  }
  else
    return 2;//xy
}


bool cmpPoint3(Point3 &p1, Point3 &p2, double tol)
{
  if ( (p1 == p2) || (CGAL::squared_distance(p1, p2) <= (tol * tol)) )
    return true;
  else
    return false;
}


Vector* polygon_normal(const vector< Point3 > &lsPts, const vector<int> &ids)
{
  //-- Newell' method
  //translate all the points to the origin to enhance the stability
  Vector centPt(0.0, 0.0, 0.0);
  vector<Point3>::const_iterator it_pt = lsPts.begin();
  for (; it_pt != lsPts.end(); it_pt++)
  {
    centPt = centPt + ((*it_pt)-CGAL::ORIGIN);
  }
  centPt = centPt/lsPts.size();
  //
  vector<Point3> newPts;
  it_pt = lsPts.begin();
  for (; it_pt != lsPts.end(); it_pt++)
  {
    newPts.push_back(*it_pt-centPt);
  }
  //
  vector<int>::const_iterator it = ids.begin();
  Point3 vert (newPts[*(ids.end()-1)]);
  Vector* pnormal = new Vector(0.0, 0.0, 0.0);
  for (;it!=ids.end();it++)
  {
    Vector next ((vert.z() + newPts[*it].z()) * (vert.y() - newPts[*it].y()),
                 (vert.x() + newPts[*it].x()) * (vert.z() - newPts[*it].z()),
                 (vert.y() + newPts[*it].y()) * (vert.x() - newPts[*it].x()));
    *pnormal = *pnormal + next;
    vert = newPts[*it];
  }
  return pnormal;
}


bool create_polygon(const vector<Point3>& lsPts, const vector<int>& ids, Polygon &pgn, bool ccworient)
{
  int proj = projection_plane(lsPts, ids);
  if (proj == -1) //-- polygon self-intersects or is collapsed to a point or a polyline
    return false;
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
