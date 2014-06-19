/*
 val3dity - Copyright (c) 2011-2014, Hugo Ledoux.  All rights reserved.
 
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
#include <GEOS/geos_c.h>
#include <sstream>

bool is_face_planar_distance2plane(const vector<Point3> &pts, double& value, float tolerance);
bool has_face_duplicates(const vector< vector<int> >& theface);


bool has_face_duplicates(const vector< vector<int> >& theface)
{
  bool bDuplicates = false;
  vector< vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    size_t numv = itr->size();
    //-- first-last not the same (they are not in GML format anymore)
    std::cout << "one ring" << std::endl;
    if (itr[0] == itr[numv - 1]) {
      std::cout << "shit" << std::endl;
      bDuplicates = true;
      break;
    }
    for (int i = 0; i < (static_cast<int>(numv) - 1); i++) {
      if (itr[i] == itr[i+1]) {
        std::cout << "oh" << std::endl;
        std::cout << i << "-" << i+1 << std::endl;
        bDuplicates = true;
        break;
      }
    }
  }
  return bDuplicates;
}


bool is_face_planar_distance2plane(const vector<Point3> &pts, double& value, float tolerance)
{
  CgalPolyhedron::Plane_3 plane(pts[0], pts[1], pts[2]);
  int i = 3;
  while (plane.is_degenerate() == true) {
    plane = CgalPolyhedron::Plane_3(pts[0], pts[1], pts[i]);
    i++;
    if (i > pts.size()) {
      break;
    }
    
  }
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

bool validate_2D(vector<Shell*> &shells, cbf cb, double TOL_PLANARITY_d2p)
{
  initGEOS(NULL, NULL);
  (*cb)(STATUS_OK, -1, -1, "Validating surface in 2D with GEOS (their projection)");
  bool isvalid = true;
  for (unsigned int is=0; is<shells.size(); is++)
  {
    Shell* shell = shells[is];
    size_t num = shell->faces.size();
    for (int i = 0; i < static_cast<int>(num); i++)
    {

      //-- test for duplicate vertices
      if (has_face_duplicates(shell->faces[i]) == true)
      {
        (*cb)(REPEATED_POINTS, is, i, "");
        isvalid = false;
        continue;
      }

      //-- test planarity of the face
      //-- read the faces
      // These are the number of rings for this face
      size_t numf = shell->faces[i].size();
      vector<int> &ids = shell->faces[i][0]; // helpful alias for the outer boundary
      vector< Point3 > allpts;
      vector<int>::const_iterator itp = ids.begin();
      for ( ; itp != ids.end(); itp++)
      {
        allpts.push_back(shell->lsPts[*itp]);
      }
      //-- irings
      for (int j = 1; j < static_cast<int>(numf); j++)
      {
        vector<int> &ids2 = shell->faces[i][j]; // helpful alias for the inner boundary
        vector<int>::const_iterator itp2 = ids2.begin();
        for ( ; itp2 != ids2.end(); itp2++)
        {
          allpts.push_back(shell->lsPts[*itp2]);
        }
      }
      double value;
      if (false == is_face_planar_distance2plane(allpts, value, TOL_PLANARITY_d2p))
	    {
        std::ostringstream msg;
        msg << "distance to fitted plane: " << value << " (tolerance=" << TOL_PLANARITY_d2p << ")";
        (*cb)(NON_PLANAR_SURFACE, is, i, msg.str());
		    isvalid = false;
		    continue;
	    }
      
      //-- get projected oring
      Polygon pgn;
      vector<Polygon> lsRings;
      if (false == create_polygon(shell->lsPts, ids, pgn, false))
	    {
		    (*cb)(RING_SELF_INTERSECT, is, i, " outer ring self-intersects or is collapsed to a point or a line");
		    isvalid = false;
		    continue;
	    }
      lsRings.push_back(pgn);
      //-- check for irings
      for (int j = 1; j < static_cast<int>(numf); j++)
      {
        vector<int> &ids2 = shell->faces[i][j]; // helpful alias for the inner boundary
        //-- get projected iring
        Polygon pgn;
        if (false == create_polygon(shell->lsPts, ids2, pgn, false))
  	    {
  		    (*cb)(RING_SELF_INTERSECT, is, i, "Inner ring self-intersects or is collapsed to a point or a line");
  		    isvalid = false;
  		    continue;
  	    }
        lsRings.push_back(pgn);
      }
      
      //-- check the orientation of the rings: oring != irings
      //-- we don't care about CCW or CW at this point, just opposite is important
      //-- GEOS doesn't do its job, so we have to do it here. Shame on you GEOS.
      bool vSurface = true;
      if (lsRings.size() > 1)
      {
        CGAL::Orientation ooring = lsRings[0].orientation();
        vector<Polygon>::iterator it = lsRings.begin();
        it++;
        for ( ; it != lsRings.end(); it++)
        {
          if (it->orientation() == ooring)
          {
            (*cb)(ORIENTATION_RINGS_SAME, is, i, "same orientation for outer and inner rings");
            isvalid = false;
            vSurface = false;
            break;
          }
        }
        if (vSurface == false)
          continue;
      }
      //-- check 2D validity of the surface by (1) projecting them; (2) use GEOS IsValid()
      stringstream wkt;
      wkt << setprecision(15);
      wkt << "POLYGON(";
      vector<Polygon>::iterator it = lsRings.begin();
      //-- oring
      wkt << "(";
      Polygon::Vertex_iterator vit = it->vertices_begin();
      for ( ; vit != it->vertices_end(); vit++)
      {
        wkt << vit->x() << " " << vit->y() << ",";
      }
      vit = it->vertices_begin();
      wkt << vit->x() << " " << vit->y() << ")";
      it++;
      //-- irings
      for ( ; it != lsRings.end(); it++)
      {
        wkt << ", (";
        it->reverse_orientation();
        Polygon::Vertex_iterator vit = it->vertices_begin();
        for ( ; vit != it->vertices_end(); vit++)
        {
          wkt << vit->x() << " " << vit->y() << ",";
        }
        vit = it->vertices_begin();
        wkt << vit->x() << " " << vit->y() << ")";
        it->reverse_orientation();
      }
      wkt << ")";
      GEOSWKTReader* r;
      r = GEOSWKTReader_create();
      GEOSGeometry* mygeom;
      mygeom = GEOSWKTReader_read(r, wkt.str().c_str());
      string reason = (string)GEOSisValidReason(mygeom);
      if (reason.find("Valid Geometry") == string::npos)
      {
        isvalid = false;
        if (reason.find("Self-intersection") != string::npos)
          (*cb)(SELF_INTERSECTION, is, i, reason.c_str());
        else if (reason.find("Interior is disconnected") != string::npos)
          (*cb)(INTERIOR_DISCONNECTED, is, i, reason.c_str());
        else if (reason.find("Hole lies outside shell") != string::npos)
          (*cb)(HOLE_OUTSIDE, is, i, reason.c_str());
        else if (reason.find("Holes are nested") != string::npos)
          (*cb)(HOLES_ARE_NESTED, is, i, reason.c_str());
        else
          (*cb)(UNKNOWN_ERROR, is, i, reason.c_str());
      }
      GEOSGeom_destroy( mygeom );
    }
  }
  finishGEOS();
  return isvalid;
}

