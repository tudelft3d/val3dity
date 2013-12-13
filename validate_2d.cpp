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

#include "validate_2d.h"
#include "validate.h"
#include "cgal/squared_distance_3.h"
#include <geos_c.h>



bool validate_2D(vector<Shell*> &shells, cbf cb)
{
  initGEOS(NULL, NULL);
  (*cb)(STATUS_OK, -1, -1, "Validating surface in 2D with GEOS (their projection)");
  bool isvalid = true;
  for (unsigned int is=0; is<shells.size(); is++)
  {
    Shell* shell = shells[is];
    //-- read the facets
    size_t num = shell->faces.size();
    for (int i = 0; i < static_cast<int>(num); i++)
    {
      // These are the number of rings on this facet
      size_t numf = shell->faces[i].size();
      vector<int> &ids = shell->faces[i][0]; // helpful alias for the outer boundary

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
      //-- GEOS doesn't do its job, so we have to do it here, sadly.
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

