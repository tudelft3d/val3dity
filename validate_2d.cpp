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
// OGR-- to use GEOS's IsValid() function easily to valide the faces in 2D
#include <gdal/ogrsf_frmts.h>
//#include "ogr_geos.h"
#include <geos/geos_c.h>
//#include "gdal/ogr_api.h"
//#include "gdal/ogr_p.h"



bool validate_2D(vector<Shell*> &shells, cbf cb)
{
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
	  //-- check for degeneration add by John
	  if (!check_degenerate_face(shell->lsPts, ids))
	  {
		  (*cb)(DEGENERATE_SURFACE, is, i, "Degenerated face");
		  isvalid = false;
		  continue;
	  }
      //-- get projected Polygon
      Polygon pgn;
      vector<Polygon> lsRings;
	  //
      if (false == create_polygon(shell->lsPts, ids, pgn))
	  {
		  (*cb)(NON_SIMPLE_SURFACE, is, i, "The polygon is not simple!");
		  isvalid = false;
		  continue;
	  }
      lsRings.push_back(pgn);
      //-- check for irings
      for (int j = 1; j < static_cast<int>(numf); j++)
      {
        vector<int> &ids2 = shell->faces[i][j]; // helpful alias for the inner boundary
        //-- get projected Polygon
        Polygon pgn;
        create_polygon(shell->lsPts, ids2, pgn);
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
      
      char *wktcstr = (char *)malloc((wkt.str().size())*sizeof(char *));    
      strcpy(wktcstr, wkt.str().c_str());
      OGRGeometry *geometry;
      OGRGeometryFactory::createFromWkt(&wktcstr, NULL, &geometry);
    
      //-- get a GEOSGeometry to have access to the reason of the validation error
      //-- and to prevent GEOS from writing to std output
      GEOSGeom hThisGeosGeom = NULL;
      hThisGeosGeom = geometry->exportToGEOS();
      char *reason = (char *)malloc(1000*sizeof(char *));    
      reason = GEOSisValidReason(hThisGeosGeom);
      if (strcmp(reason, "Valid Geometry") != 0) 
      {
        isvalid = false;
        (*cb)(SURFACE_PROJECTION_INVALID, is, i, reason);
      }
      GEOSGeom_destroy( hThisGeosGeom );
    }
  }
  return isvalid;
}

//check whether the face is degenerated
bool check_degenerate_face(const vector< Point3 > &lsPts, const vector<int>& ids)
{
	//vertex number
	if (ids.size() < 3)
	{
		//degeneration
		return false;
	}
	//indices check
	vector<int>::const_iterator it_chk = ids.begin();
	for (; it_chk != ids.end()-1; it_chk++)
	{
		vector<int>::const_iterator it_chk2 = it_chk + 1;
		for (; it_chk2 != ids.end(); it_chk2++)
		{
			if (*it_chk == *it_chk2)
			{
				//degeneration
				return false;
			}
		}
	}
	//check point normal
	Vector v0 (0.0,0.0,0.0);
	int proj = projection_plane_range_2(lsPts, ids, v0);
	if (CGAL::compare (v0.squared_length(), 0.0) == CGAL::LARGER)
	{
		return true;
	}
	else
		return false;
	//return check_collinear(lsPts, ids);
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
