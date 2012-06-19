/*
 val3dity - Copyright (c) 2011-2012, Hugo Ledoux.  All rights reserved.
 
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

#include <string>
#include "validate.h"
#include "validate_shell.h"
#include "validate_solid.h"
#include "validate_2d.h"


bool    triangulate_all_shells(vector<Shell*> &shells, vector<TrShell*> &trShells, cbf cb);
bool    triangulate_one_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb);
bool    construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
double  find_range_area(int ignored, const vector< Point3 > &lsPts, const vector<int> &ids);


//--------------------------------------------------------------

bool validate(vector<Shell*> &shells, bool bRepair, cbf cb)
{
  bool foundError(false);
  
  if (bRepair == true)
    (*cb)(STATUS_OK, -1, -1, "Automatic repair will be attempted. Watch out.");
  
//-- FIRST: use GEOS to test is (projected) surface are valid in 2D
  if (! validate_2D(shells, cb))
    return false;
  else
    (*cb)(STATUS_OK, -1, -1, "-----all valid");
  
//-- SECOND: triangulate every shell 
  vector<TrShell*> trShells;
  if (! triangulate_all_shells(shells, trShells, cb))
  {
    (*cb)(INVALID_INPUT_FILE, -1, -1, "Input polyhedra are not valid enough to be triangulated.");
    return false;
  }
  else
    (*cb)(STATUS_OK, -1, -1, "-----done");
  
//-- THIRD: validate each (triangulated) shell, one by one
  vector<CgalPolyhedron*> polyhedra;
  CgalPolyhedron* p = NULL;
  for (unsigned int i = 0; i < trShells.size(); i++)
  {
    std::stringstream st;
    st << endl << "Validating shell #" << i;
    (*cb)(STATUS_OK, -1, -1, st.str());
    p  = validate_triangulated_shell(*(trShells[i]), i, bRepair, cb);  
    st.str("");
    st << "Shell #" << (i);
    if (p != NULL)
    {
      st << " valid";
      (*cb)(STATUS_OK, -1, -1, st.str());
      polyhedra.push_back(p);  
    }
    else
    {
      st << " invalid";
      //(*cb)(300, 0, -1, st.str());
      foundError = true;
    }
  }
  (*cb)(STATUS_OK, -1, -1, "");
  
//-- FOURTH: put all the valid shells in a Nef_polyhedron and check their configuration  
  bool isValid = validate_solid_with_nef(polyhedra, bRepair, cb);
  return isValid;
}

bool triangulate_all_shells(vector<Shell*> &shells, vector<TrShell*> &trShells, cbf cb)
{
  std::stringstream st;
  // Now let's triangulate the outer shell from the input.
  st << endl << "Triangulating outer shell";
  (*cb)(STATUS_OK, -1, -1, st.str());
  TrShell* tshell = new TrShell;
  if (! triangulate_one_shell(*(shells[0]), 0, *tshell, cb))
  {
    (*cb)(STATUS_OK, -1, -1, "Could not triangulate in the outer shell.");
    return false;
  }
  
  trShells.push_back(tshell);
  tshell = NULL; // don't own this anymore
  for (unsigned int is=1; is<shells.size(); is++)
  {
    // Now let's triangulate the inner shell from the input.
    tshell = new TrShell;
    st.str("");
    st << "Triangulating inner shell #" << (is-1);
    (*cb)(STATUS_OK, -1, -1, st.str());
    if (!triangulate_one_shell(*(shells[is]), is, *tshell, cb))
    {
      (*cb)(NOT_VALID_2_MANIFOLD, is, -1, "Could not triangulate the shell.");
      return false;
    }
    trShells.push_back(tshell);
    tshell = NULL; // don't own this anymore
  }
//  (*cb)(STATUS_OK, -1, -1, "");
  return true;
}


bool triangulate_one_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb)
{
  //-- read the facets
  size_t num = shell.faces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    //cout << "---- face ---- " << i << endl;
    
    // These are the number of rings on this facet
    size_t numf = shell.faces[i].size();
    //-- read oring (there's always one and only one)
    if (numf < 1)
    {
      (*cb)(SURFACE_PROJECTION_INVALID, shellNum, -1, "surface does not have an outer boundary.");
      return false;
    }
    vector<int> &idsob = shell.faces[i][0]; // helpful alias for the outer boundary
    
    int proj = projection_plane_range(shell.lsPts, idsob);
    Vector v0 = unit_normal( shell.lsPts[idsob[0]], shell.lsPts[idsob[1]], shell.lsPts[idsob[2]] );
    
    //-- get projected Polygon
    Polygon pgn;
    vector<Polygon> lsRings;
    create_polygon(shell.lsPts, idsob, pgn);
    lsRings.push_back(pgn);
    vector< vector<int> > pgnids;
    pgnids.push_back(idsob);
    
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      vector<int> &ids2 = shell.faces[i][j]; // helpful alias for the inner boundary
      //-- get projected Polygon
      Polygon pgn;
      create_polygon(shell.lsPts, ids2, pgn);
      lsRings.push_back(pgn);
      pgnids.push_back(ids2);
    }
    
    //-- get projected CT
    vector<int*> oneface;
    if (construct_ct(shell.lsPts, pgnids, lsRings, oneface, i) == false)
    {
      (*cb)(SURFACE_PROJECTION_INVALID, shellNum, i, "face does not have an outer boundary.");
      return false;
    }
    
    //-- modify orientation of every triangle if necessary
    bool invert = false;
    if (proj == 2)
    {
      Vector n(0, 0, 1);
      if ( (v0*n) < 0)
        invert = true;
    }
    else if (proj == 1)
    {
      Vector n(0, 1, 0);
      if ( (v0*n) > 0)
        invert = true;
    }
    else
    {
      Vector n(1, 0, 0);
      if ( (v0*n) < 0)
        invert = true;
    }
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
    tshell.faces.push_back(oneface);
  }
  //-- here are the points: 
  tshell.lsPts = shell.lsPts;
  return true;
}

void create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &pgn)
{
  int proj = projection_plane_range(lsPts, ids);
  //-- build projected polygon
  vector<int>::const_iterator it = ids.begin();
  for ( ; it != ids.end(); it++)
  {
    Point3 p = lsPts[*it];
    if (proj == 2)
      pgn.push_back(Point2(p.x(), p.y()));
    else if (proj == 1)
      pgn.push_back(Point2(p.x(), p.z()));
    else
      pgn.push_back(Point2(p.y(), p.z()));
  }
  if (pgn.is_counterclockwise_oriented() == false)
    pgn.reverse_orientation();
}

bool construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum)
{
  bool isValid = true;
  vector<int> ids = pgnids[0];
  int proj = projection_plane_range(lsPts, ids);
  
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
      Point3 p1  = lsPts[*it2];
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
  //  cout << "faces " << ct.number_of_faces() << endl;
  //  cout << "ct vertices " << ct.number_of_vertices() << endl;
  //  cout << "constraints " << ct.number_of_constraints() << endl;
  
  //-- validation of the face itself
  //-- if the CT introduced new points, then there are irings intersectings either oring or other irings
  //-- which is not allowed
  if (numpts < ct.number_of_vertices())
  {
    cout << "\tIntersection(s) between rings of the face #" << faceNum << "." << endl;
    isValid = false;
  } 
  //TODO: deal with degenerate case here, ie holes completely outside the oring
  
  
  
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



int projection_plane_range(const vector< Point3 > &lsPts, const vector<int> &ids)
{
  double rangearea = find_range_area(2, lsPts, ids);
  int ignoredplane = 2;
  if (find_range_area(1, lsPts, ids) > rangearea) {
    rangearea = find_range_area(1, lsPts, ids);
    ignoredplane = 1;
  }
  if (find_range_area(0, lsPts, ids) > rangearea) 
    ignoredplane = 0;
  return ignoredplane;
}
  
    


double find_range_area(int ignored, const vector< Point3 > &lsPts, const vector<int> &ids)
{
  vector<int>::const_iterator it = ids.begin();
  vector<double> range;
  if (ignored == 2) {
    range.push_back(lsPts[*it].x());
    range.push_back(lsPts[*it].y());
    range.push_back(lsPts[*it].x());
    range.push_back(lsPts[*it].y());
  }
  if (ignored == 1) {
    range.push_back(lsPts[*it].x());
    range.push_back(lsPts[*it].z());
    range.push_back(lsPts[*it].x());
    range.push_back(lsPts[*it].z());
  }
  if (ignored == 0) {
    range.push_back(lsPts[*it].y());
    range.push_back(lsPts[*it].z());
    range.push_back(lsPts[*it].y());
    range.push_back(lsPts[*it].z());
  }

  for ( ; it != ids.end(); it++)
  {
    if (ignored == 2) {
      if (lsPts[*it].x() < range[0])
        range[0] = lsPts[*it].x();
      if (lsPts[*it].y() < range[1])
        range[1] = lsPts[*it].y();
      if (lsPts[*it].x() > range[2])
        range[2] = lsPts[*it].x();
      if (lsPts[*it].y() > range[3])
        range[3] = lsPts[*it].y();
    }
    if (ignored == 1) {
      if (lsPts[*it].x() < range[0])
        range[0] = lsPts[*it].x();
      if (lsPts[*it].z() < range[1])
        range[1] = lsPts[*it].z();
      if (lsPts[*it].x() > range[2])
        range[2] = lsPts[*it].x();
      if (lsPts[*it].z() > range[3])
        range[3] = lsPts[*it].z();
    }
    if (ignored == 0) {
      if (lsPts[*it].y() < range[0])
        range[0] = lsPts[*it].y();
      if (lsPts[*it].z() < range[1])
        range[1] = lsPts[*it].z();
      if (lsPts[*it].y() > range[2])
        range[2] = lsPts[*it].y();
      if (lsPts[*it].z() > range[3])
        range[3] = lsPts[*it].z();
    }
  }
  return ( (range[2]-range[0]) * (range[3]-range[1]) );
}
    
 