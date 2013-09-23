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
bool    construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);


//--------------------------------------------------------------

bool validate(vector<Shell*> &shells, bool bIsPolyhedron, cbf cb)
{
  bool foundError(false);
  
//-- FIRST: use GEOS to test if (projected) surface are valid in 2D
  if (! validate_2D(shells, cb))
    return false;
  else
    (*cb)(STATUS_OK, -1, -1, "-----all valid");
  
//-- SECOND: triangulate every shell 
  vector<TrShell*> trShells;
  if (! triangulate_all_shells(shells, trShells, cb))
  {
    (*cb)(UNKNOWN_ERROR, -1, -1, "Something went wrong during the triangulation of the faces. Cannot continue.");
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
    p  = validate_triangulated_shell(*(trShells[i]), i, bIsPolyhedron, cb);
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
  bool isValid = validate_solid_with_nef(polyhedra, cb);

  // Safe Software Inc.
  // SECTION_START: Fix memory leaks.
  for (size_t i=0; i < polyhedra.size(); ++i)
  {
     delete polyhedra[i]; polyhedra[i] = NULL;
  }
  for (size_t i=0; i < trShells.size(); ++i)
  {
    TrShell*& shell = trShells[i];
    for (size_t j=0; j < shell->faces.size(); ++j)
    {
      vector<int*>& faces = shell->faces[j];
      for (size_t k=0; k < faces.size(); ++k)
      {
        delete [] faces[k]; faces[k] = NULL;
      }
    }
    delete shell; shell = NULL;
  }
  // SECTION_END: Fix memory leaks.

  return isValid;
}


bool repair(vector<Shell*> &shells, const vector<bool> &repairs, cbf cb)
{
  bool foundError(false);
  
  //-- REQUIREMENT #1: 2D faces are valid
  //TODO: implement alternative way to perform planarity, so that I can catch cases *before* triangulating?
  if (! validate_2D(shells, cb))
    return false;
  else
    (*cb)(STATUS_OK, -1, -1, "-----all valid");
  
  //-- triangulate every shell
  vector<TrShell*> trShells;
  if (! triangulate_all_shells(shells, trShells, cb))
  {
    (*cb)(INVALID_INPUT_FILE, -1, -1, "Something went wrong during the triangulation of the faces. Cannot continue.");
    return false;
  }
  else
    (*cb)(STATUS_OK, -1, -1, "-----done");
  
  //-- validate each (triangulated) shell, one by one
  vector<CgalPolyhedron*> polyhedra;
  CgalPolyhedron* p = NULL;
  for (unsigned int i = 0; i < trShells.size(); i++)
  {
    std::stringstream st;
    st << endl << "Validating shell #" << i;
    (*cb)(STATUS_OK, -1, -1, st.str());
    p  = repair_triangulated_shell(*(trShells[i]), repairs, i, cb);
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
  bool isValid = validate_solid_with_nef(polyhedra, cb);

  // Safe Software Inc.
  // SECTION_START: Fix memory leaks.
  for (size_t i=0; i < polyhedra.size(); ++i)
  {
    delete polyhedra[i]; polyhedra[i] = NULL;
  }
  for (size_t i=0; i < trShells.size(); ++i)
  {
    TrShell*& shell = trShells[i];
    for (size_t j=0; j < shell->faces.size(); ++j)
    {
      vector<int*>& faces = shell->faces[j];
      for (size_t k=0; k < faces.size(); ++k)
      {
        delete [] faces[k]; faces[k] = NULL;
      }
    }
    delete shell; shell = NULL;
  }
  // SECTION_END: Fix memory leaks.

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
    // These are the number of rings on this facet
    size_t numf = shell.faces[i].size();
    //-- read oring (there's always one and only one)
    if (numf < 1)
    {
      (*cb)(UNKNOWN_ERROR, shellNum, -1, "surface does not have an outer boundary.");
      return false;
    }
    vector<int> &idsob = shell.faces[i][0]; // helpful alias for the outer boundary
    
    int proj = projection_plane(shell.lsPts, idsob);

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
      (*cb)(UNKNOWN_ERROR, shellNum, i, "face does not have an outer boundary.");
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
    else if(proj == 0)
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

bool create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &pgn)
{
  int proj = projection_plane(lsPts, ids);

  if (proj == -1) //-- polygon self-intersects or is collapsed to a point or a polyline
  {
    return false;
  }
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
  {
    return false;
  }
  if (pgn.orientation() == CGAL::COLLINEAR)
  {
    return false;
  }
  if (pgn.is_counterclockwise_oriented() == false)
    pgn.reverse_orientation();
  return true;
}

bool construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum)
{
  bool isValid = true;
  vector<int> ids = pgnids[0];
  int proj = projection_plane(lsPts, ids);
  
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


int projection_plane(const vector< Point3 > &lsPts, const vector<int> &ids)
{
  Vector* pnormal = polygon_normal(lsPts, ids);
	K::FT TOL(1e-8); //-- tolerance 
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



 