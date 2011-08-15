/*
 val3dity - Copyright (c) 2011, Hugo Ledoux.  All rights reserved.
 
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

#include "validate.h"
#include "validate_shell.h"
#include "validate_solid.h"

// CGAL classes
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Polygon_2.h>


// CGAL typedefs
typedef CGAL::Triangulation_vertex_base_with_info_2 <unsigned,K>  Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag>           CTa;
typedef CGAL::Constrained_triangulation_plus_2<CTa>               CT;
typedef CGAL::Polygon_2<K> Polygon;


// misc
#define PI 3.14159265


bool  triangulate_all_shells(vector<Shell*> &shells, vector<TrShell*> &trShells, cbf cb);
bool  triangulate_one_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb);
int   projection_plane(Point3 p0, Point3 p1, Point3 p2);
bool  construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
void  create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &p);




//--------------------------------------------------------------

bool validate(vector<Shell*> &shells, cbf cb)
{
  bool foundError(false);

//-- First: triangulate every shell 
  vector<TrShell*> trShells;
  if (! triangulate_all_shells(shells, trShells, cb))
  {
    (*cb)(999, -1, -1, "Input polyhedra are not valid enough to be triangulated.");
    return false;
  }

//-- Second: validate each (triangulated) shell, one by one
  (*cb)(0, -1, -1, "Validating the shell(s)");
  vector<CgalPolyhedron*> polyhedra;
  CgalPolyhedron* p = NULL;
  for (unsigned int i = 0; i < trShells.size(); i++)
  {
    p = validate_triangulated_shell(*(trShells[i]), i, cb);  
    std::stringstream st;
    st << "\tShell #" << (i);
    if (p != NULL)
    {
      st << " valid";
      (*cb)(0, -1, -1, st.str());
      polyhedra.push_back(p);  
    }
    else
    {
      st << " invalid";
      (*cb)(300, 0, -1, st.str());
      foundError = true;
    }
  }
  
//-- Third: put all the valid shells in a Nef_polyhedron and check their configuration  
  bool isValid = validate_solid_with_nef(polyhedra, cb);
  return isValid;
}


bool triangulate_all_shells(vector<Shell*> &shells, vector<TrShell*> &trShells, cbf cb)
{
   std::stringstream st;
   // Now let's triangulate the outer shell from the input.
   st << "Triangulating outer shell." << endl;
   (*cb)(0, -1, -1, st.str());
   TrShell* tshell = new TrShell;
   if (! triangulate_one_shell(*(shells[0]), 0, *tshell, cb))
   {
      (*cb)(0, -1, -1, "Could not triangulate in the outer shell.");
      return false;
   }

   trShells.push_back(tshell);
   tshell = NULL; // don't own this anymore
   for (unsigned int is=1; is<shells.size(); is++)
   {
      // Now let's triangulate the inner shell from the input.
      tshell = new TrShell;
      if (!triangulate_one_shell(*(shells[is]), is, *tshell, cb))
      {
         (*cb)(300, is, -1, "Could not triangulate the shell.");
         return false;
      }
      trShells.push_back(tshell);
      tshell = NULL; // don't own this anymore
   }
   return true;
}

bool triangulate_one_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb)
{
   //-- read the facets
   int num = shell.faces.size();
   for (int i = 0; i < num; i++)
   {
      //    cout << "---- face ---- " << i << endl;
      
      // These are the number of rings on this facet
      int numf = shell.faces[i].size();
      //-- read oring (there's always one and only one)
      if (numf < 1)
      {
         (*cb)(220, shellNum, -1, "facet does not have an outer boundary.");
         return false;
      }
      vector<int> &ids = shell.faces[i][0]; // helpful alias for the outer boundary

      //-- We're going to use the outer shell as the reference plane for this entire face.
      int proj = projection_plane(shell.lsPts[ids[0]], shell.lsPts[ids[1]], shell.lsPts[ids[2]]);
      Vector v0 = unit_normal( shell.lsPts[ids[0]], shell.lsPts[ids[1]], shell.lsPts[ids[2]] );

      //-- get projected Polygon
      //    cout << "proj :" << proj << endl;
      Polygon pgn;
      vector<Polygon> lsRings;
      create_polygon(shell.lsPts, ids, pgn);
      lsRings.push_back(pgn);
      vector< vector<int> > pgnids;
      pgnids.push_back(ids);

      //-- check for irings
      for (int j = 1; j < numf; j++)
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
         (*cb)(220, shellNum, i, "face does not have an outer boundary.");
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
   int proj = projection_plane(lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]]);
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
   int proj = projection_plane(lsPts[ids[0]], lsPts[ids[1]], lsPts[ids[2]]);

   CT ct;
   vector< vector<int> >::const_iterator it = pgnids.begin();

   unsigned int numpts = 0;
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

int projection_plane(Point3 p0, Point3 p1, Point3 p2)
{
   //-- calculate normale
   Vector v = normal(p0, p1, p2);
   int proj = 2; //-- xy plane
   if (v.z() == 0.0)
   {
      if (v.y() == 0.0)
         proj = 0; //-- yz plane
      else
         proj = 1; //-- xz plane
   }
   return proj;
}




