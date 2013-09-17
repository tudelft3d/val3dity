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
#include <geos/geos_c.h>



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
      if (false == create_polygon(shell->lsPts, ids, pgn))
	    {
		    (*cb)(NON_SIMPLE_SURFACE, is, i, "Outer ring is collapsed to a point/line.");
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
        if (false == create_polygon(shell->lsPts, ids2, pgn))
  	    {
  		    (*cb)(NON_SIMPLE_SURFACE, is, i, "Inner ring is collapsed to a point/line.");
  		    isvalid = false;
  		    continue;
  	    }
        lsRings.push_back(pgn);
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
      char *reason = (char *)malloc(1000*sizeof(char *));    
      reason = GEOSisValidReason(mygeom);
      if (strcmp(reason, "Valid Geometry") != 0) 
      {
        isvalid = false;
        (*cb)(SURFACE_PROJECTION_INVALID, is, i, reason);
      }
      GEOSGeom_destroy( mygeom );
    }
  }
  finishGEOS();
  return isvalid;
}



// bool check_collinear(const vector< Point3 > &lsPts, const vector<int>& ids)
// {
// 	//
// 	if (lsPts.size () < 2 || ids.size() < 2)
// 	{
// 		return false;
// 	}
// 	vector< int >::const_iterator pt_itr = ids.begin();
// 	Point3 pt1 = lsPts[*pt_itr++];
// 	Point3 pt2 = lsPts[*pt_itr++];
// 	for (; pt_itr != ids.end(); pt_itr++)
// 	{
// 		Point3 ckpt = lsPts[*pt_itr];
// 		typedef K::Line_3 Line;
// 		Line ckline (pt1, pt2);
// 		if (CGAL::compare (squared_distance(ckline, ckpt), 0.0) == CGAL::LARGER)
// 		{
// 			return true;
// 		}
// 	}
// 
// 	return false;
// }
