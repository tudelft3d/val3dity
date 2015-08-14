//
//  Shell.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Shell.h"
#include "geomtools.h"



Shell2::Shell2(int id, double tol_snap, cbf cb)
{
  _id = id;
  _tol_snap = tol_snap;
  _cb = cb;
}

Shell2::~Shell2()
{
  // TODO: clear memory properly
  _lsPts.clear();
}

bool Shell2::validate()
{
  return true;
}


int Shell2::add_point(Point3 p)
{
  int pos = -1;
  int cur = 0;
  for (auto &itr : _lsPts)
  {
    // std::cout << "---" << itr << std::endl;
    if (cmpPoint3(p, itr, _tol_snap) == true)
    {
      pos = cur;
      break;
    }
    cur++;
  }
  if (pos == -1)
  {
    _lsPts.push_back(p);
    return (_lsPts.size() - 1);
  }
  else
    return pos;
}


void Shell2::add_face(vector< vector<int> > f)
{
  _lsFaces.push_back(f);
}


int Shell2::number_points()
{
  return _lsPts.size();
}


int Shell2::number_faces()
{
  return _lsFaces.size();
}


bool Shell2::is_outer()
{
  return (_id == 0);
}

// bool Shell2::triangulate_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb)
bool Shell2::triangulate_shell()
{
  //-- read the facets
  size_t num = _lsFaces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    // These are the number of rings on this facet
    size_t numf = _lsFaces[i].size();
    //-- read oring (there's always one and only one)
    if (numf < 1)
    {
      (*_cb)(999, _id, -1, "surface does not have an outer boundary.");
      return false;
    }
    vector<int> &idsob = _lsFaces[i][0]; // helpful alias for the outer boundary
    int proj = projection_plane(_lsPts, idsob);
    Vector* v0 = polygon_normal(_lsPts, idsob);
    //-- get projected Polygon
    Polygon pgn;
    vector<Polygon> lsRings;
    create_polygon(idsob, pgn, true);
    lsRings.push_back(pgn);
    vector< vector<int> > pgnids;
    pgnids.push_back(idsob);
    
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      //-- get projected Polygon
      Polygon pgn;
      create_polygon(ids2, pgn, true);
      lsRings.push_back(pgn);
      pgnids.push_back(ids2);
    }
    //-- get projected CT
    vector<int*> oneface;
    if (construct_ct(pgnids, lsRings, oneface, i) == false)
    {
      (*_cb)(999, _id, i, "face does not have an outer boundary.");
      return false;
    }
    //-- modify orientation of every triangle if necessary
    bool invert = false;
    if (proj == 2)
    {
      Vector n(0, 0, 1);
      if ( (*v0*n) < 0)
        invert = true;
    }
    else if (proj == 1)
    {
      Vector n(0, 1, 0);
      if ( (*v0*n) > 0)
        invert = true;
    }
    else if(proj == 0)
    {
      Vector n(1, 0, 0);
      if ( (*v0*n) < 0)
        invert = true;
    }
    delete v0;
    if ( invert == true ) //-- invert
    {
      vector<int*>::iterator it3 = oneface.begin();
      int tmp;
      int* id;
      for ( ; it3 != oneface.end(); it3++)
      {
        id = *it3;
        tmp = id[0];
        id[0] = id[1];
        id[1] = tmp;
      }
    }
    _lsTr.push_back(oneface);
  }
  return true;
}

// bool Shell2::create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &pgn, bool ccworient)
bool Shell2::create_polygon(const vector<int>& ids, Polygon &pgn, bool ccworient)
{
  int proj = projection_plane(_lsPts, ids);
  if (proj == -1) //-- polygon self-intersects or is collapsed to a point or a polyline
    return false;
  vector<int>::const_iterator it = ids.begin();
  for ( ; it != ids.end(); it++)
  {
    Point3 p = _lsPts[*it];
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


// bool Shell2::construct_ct(const vector< Point3 > &_lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum)
bool Shell2::construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum)
{
  bool isValid = true;
  vector<int> ids = pgnids[0];
  int proj = projection_plane(_lsPts, ids);
  CT ct;
  vector< vector<int> >::const_iterator it = pgnids.begin();
  size_t numpts = 0;
  for ( ; it != pgnids.end(); it++)
  {
    numpts += it->size();
  }
  //  cout << "Polygon has # vertices " << numpts << endl;
  for ( it = pgnids.begin(); it != pgnids.end(); it++)
  {
    vector<Point2> pts2d;
    vector<int>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      Point3 p1  = _lsPts[*it2];
      if (proj == 2)
        pts2d.push_back( Point2(p1.x(), p1.y()) );
      else if (proj == 1)
        pts2d.push_back( Point2(p1.x(), p1.z()) );
      else
        pts2d.push_back( Point2(p1.y(), p1.z()) );
    }
    vector<Point2>::const_iterator itPt;
    CT::Vertex_handle v0;
    CT::Vertex_handle v1;
    CT::Vertex_handle firstv;
    itPt = pts2d.begin();
    v0 = ct.insert(*itPt);
    firstv = v0;
    it2 = it->begin();
    v0->info() = *it2;
    itPt++;
    it2++;
    for (; itPt != pts2d.end(); itPt++)
    {
      v1 = ct.insert(*itPt);
      v1->info() = *it2;
      ct.insert_constraint(v0, v1);
      v0 = v1;
      it2++;
    }
    ct.insert_constraint(v0,firstv);
  }
  //-- validation of the face itself
  //-- if the CT introduced new points, then there are irings intersectings either oring or other irings
  //-- which is not allowed
  if (numpts < ct.number_of_vertices())
  {
    std::stringstream ss;
    ss << "Intersection(s) between rings of the face #" << faceNum << ".";
    (*_cb)(0, -1, -1, ss.str());
    isValid = false;
  }  
  //-- fetch all the triangles forming the polygon (with holes)
  CT::Finite_faces_iterator fi = ct.finite_faces_begin();
  for( ; fi != ct.finite_faces_end(); fi++)
  {
    Point2 centre = barycenter( ct.triangle(fi).vertex(0), 1,
                               ct.triangle(fi).vertex(1), 1,
                               ct.triangle(fi).vertex(2), 1);
    bool inside = true;
    if (lsRings[0].has_on_negative_side(centre))
      inside = false;
    else
    {
      vector<Polygon>::const_iterator itpgn = lsRings.begin();
      itpgn++;
      for ( ; itpgn != lsRings.end(); itpgn++)   //-- check irings
      {
        if (itpgn->has_on_positive_side(centre))
        {
          inside = false;
          break;
        }
      }
    }
    if (inside == true)
    {
      //-- add the IDs to the face
      int* tr = new int[3];
      tr[0] = fi->vertex(0)->info();
      tr[1] = fi->vertex(1)->info();
      tr[2] = fi->vertex(2)->info();
      oneface.push_back(tr);
    }
  }
  return isValid;
}
