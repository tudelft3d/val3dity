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

// CGAL classes
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/basic.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>

#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>

// CGAL typedefs
typedef CGAL::Triangulation_vertex_base_with_info_2 <unsigned,K>  Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag>           CTa;
typedef CGAL::Constrained_triangulation_plus_2<CTa>               CT;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Polyhedron_3<K>       Polyhedron;
typedef CGAL::Polyhedron_3<Ke>       PolyhedronExact;
typedef CGAL::Nef_polyhedron_3<Ke>  Nef_polyhedron;

typedef struct triangulatedPolyhedraShell_tag {
   vector< Point3 > lsPts;
   vector< vector<int*> > shell;
} triangulatedPolyhedraShell;

// misc
#define PI 3.14159265

bool is_face_planar(const vector<int*>& trs, const vector<Point3>& lsPts, float angleTolerance = 1);
bool checkPlanarityFaces(vector< vector<int*> >&shell, vector<Point3>& lsPts);
bool check2manifoldness(Polyhedron* p);
CGAL::Orientation checkGlobalOrientationNormales(Polyhedron* p);
Polyhedron* getPolyhedronDS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts);
bool isPolyhedronGeometricallyConsistent(Polyhedron* p);
Polyhedron* validateTriangulatedPolyhedraShell(triangulatedPolyhedraShell& tshell, bool isOutershell);
bool triangulatePolyhedraShells(vector<polyhedraShell*> &polyhedraShells, vector<triangulatedPolyhedraShell*> &triangulatedPolyhedraShells);
bool triangulateOneShell(polyhedraShell& pshell, triangulatedPolyhedraShell& tshell);
int projection_plane(Point3 p0, Point3 p1, Point3 p2);
bool construct_ct(const vector< Point3 > &lsPts, const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
void create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &p);

//--------------------------------------------------------------

void validatePolyHedra(vector<polyhedraShell*> &polyhedraShells, vector<invalidItem>& invalidItems)
{
   vector<triangulatedPolyhedraShell*> triangulatedPolyhedraShells;

   if (! triangulatePolyhedraShells(polyhedraShells, triangulatedPolyhedraShells))
   {
      cout << "polyhedra are not valid enough to be triangulated." << endl;
      invalidItem ii;
      ii.errorCode = 999;
      ii.polyhedraNum = -1;
      invalidItems.push_back(ii);
      return;
   }

   if (triangulatedPolyhedraShells.size() < 1)
   {
      cout << "You have to give at least one input polyhedron." << endl;
      invalidItem ii;
      ii.errorCode = 999;
      ii.polyhedraNum = 0;
      invalidItems.push_back(ii);
      return;
   }

   cout << "Validating " << triangulatedPolyhedraShells.size() << " shell(s)." << endl << endl;

   // First, let's do a quick validation of the outer shell
   cout << "Validating outer shell: " << 0 << endl;

   Polyhedron* p = validateTriangulatedPolyhedraShell(*(triangulatedPolyhedraShells[0]), true);  
   if (p != NULL)
   {
      cout << "Outer shell valid.\n" << endl;
   }
   else
   {
      cout << "Outer shell invalid.\n" << endl;
      invalidItem ii;
      ii.errorCode = 999;
      ii.polyhedraNum = 0;
      invalidItems.push_back(ii);
   }

    vector<Polyhedron*> polyhedra;
    polyhedra.push_back(p);  

    for (unsigned int i=1; i<triangulatedPolyhedraShells.size(); i++)
    {
       cout << "Validating inner shell #" << (i-1) << endl;

       p = validateTriangulatedPolyhedraShell(*(triangulatedPolyhedraShells[i]), false);  
       if (p != NULL)
       {
          cout << "Inner shell valid.\n" << endl;
       }
       else
       {
          cout << "Inner shell invalid.\n" << endl;
          invalidItem ii;
          ii.errorCode = 999;
          ii.polyhedraNum = i;
          invalidItems.push_back(ii);
       }
       polyhedra.push_back(p);
    }

    //-- if all the shells are valid, then put them in a Nef_polyhedron type
    vector<Polyhedron*>::iterator polyhedraIt = polyhedra.begin();
    for ( ; polyhedraIt != polyhedra.end(); polyhedraIt++)
    {
       if (*polyhedraIt == NULL)
       {
          invalidItem ii;
          ii.errorCode = 999;
          ii.polyhedraNum = 0;
          invalidItems.push_back(ii);
          break;
       }
    }
    if (0 == invalidItems.size())
    {
       if (polyhedra.size() == 1)
       {
          cout << "Solid is valid." << endl;
       }
       else
       {
          cout << "Calculating interactions between the shells." << endl;
          vector<Nef_polyhedron> nefs;
          for (polyhedraIt = polyhedra.begin(); polyhedraIt != polyhedra.end(); polyhedraIt++)
          {
             stringstream offrep (stringstream::in | stringstream::out);
             offrep << **polyhedraIt;
             PolyhedronExact pe;
             offrep >> pe;
             Nef_polyhedron onef(pe);
             nefs.push_back(onef);
          }
          vector<Nef_polyhedron>::iterator nefsIt = nefs.begin();
          Nef_polyhedron solid = *nefsIt;
          nefsIt++;
          for ( ; nefsIt != nefs.end(); nefsIt++) 
             solid -= *nefsIt;
          if (solid.number_of_volumes() == (polyhedra.size()+1))
          {
             cout << "Valid solid. Hourrraaa!" << endl;
          }
          else
          {
             cout << "Invalid solid :(" << endl;
             invalidItem ii;
             ii.errorCode = 999;
             ii.polyhedraNum = -1;
             invalidItems.push_back(ii);
          }
       }
    }
    return;

}


bool triangulatePolyhedraShells(vector<polyhedraShell*> &polyhedraShells, vector<triangulatedPolyhedraShell*> &triangulatedPolyhedraShells)
{
   cout << "Triangulating " << polyhedraShells.size() << " shell(s)." << endl << endl;

   cout << "Triangulating outer shell." << endl;
   if (polyhedraShells.size() < 1)
   {
      cout << "Error. No outer shell." << endl;
      return false;
   }

   // Now let's triangulate the outer shell from the input.
   triangulatedPolyhedraShell* tshell = new triangulatedPolyhedraShell;
   if (! triangulateOneShell(*(polyhedraShells[0]), *tshell))
   {
      cout << "Could not triangulate in the outer shell." << endl;
      return false;
   }

   triangulatedPolyhedraShells.push_back(tshell);
   tshell = NULL; // don't own this anymore
   for (unsigned int is=1; is<polyhedraShells.size(); is++)
   {
      cout << "Triangulating inner shell #" << (is-1) << endl;

      // Now let's triangulate the inner shell from the input.
      tshell = new triangulatedPolyhedraShell;
      if (!triangulateOneShell(*(polyhedraShells[is]), *tshell))
      {
         cout << "Could not triangulate in the inner shell #" << (is-1) << endl;
         return false;
      }

      triangulatedPolyhedraShells.push_back(tshell);
      tshell = NULL; // don't own this anymore
   }

   return true;
}

bool triangulateOneShell(polyhedraShell& pshell, triangulatedPolyhedraShell& tshell)
{
   //-- read the facets
   int num = pshell.shells.size();
   for (int i = 0; i < num; i++)
   {
      //    cout << "---- face ---- " << i << endl;
      
      // These are the number of rings on this facet
      int numf = pshell.shells[i].size();
      //-- read oring (there's always one and only one)
      if (numf < 1)
      {
         cout << "facet does not have an outer boundary." << endl;
         return false;
      }
      vector<int> &ids = pshell.shells[i][0]; // helpful alias for the outer boundary

      //-- We're going to use the outer shell as the reference plane for this entire face.
      int proj = projection_plane(pshell.lsPts[ids[0]], pshell.lsPts[ids[1]], pshell.lsPts[ids[2]]);
      Vector v0 = unit_normal( pshell.lsPts[ids[0]], pshell.lsPts[ids[1]], pshell.lsPts[ids[2]] );

      //-- get projected Polygon
      //    cout << "proj :" << proj << endl;
      Polygon pgn;
      vector<Polygon> lsRings;
      create_polygon(pshell.lsPts, ids, pgn);
      lsRings.push_back(pgn);
      vector< vector<int> > pgnids;
      pgnids.push_back(ids);

      //-- check for irings
      for (int j = 1; j < numf; j++)
      {
         vector<int> &ids2 = pshell.shells[i][j]; // helpful alias for the inner boundary

         //-- get projected Polygon
         Polygon pgn;
         create_polygon(pshell.lsPts, ids2, pgn);
         lsRings.push_back(pgn);
         pgnids.push_back(ids2);
      }

      //-- get projected CT
      vector<int*> oneface;
      if (construct_ct(pshell.lsPts, pgnids, lsRings, oneface, i) == false)
      {
         cout << "cannot triangulate polyhedra face #" << i << endl;
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
      tshell.shell.push_back(oneface);
   }

   //-- here are the points: 
   tshell.lsPts = pshell.lsPts;
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


bool checkPlanarityFaces(vector< vector<int*> >&shell, vector<Point3>& lsPts)
{
  vector< vector<int*> >::iterator faceIt = shell.begin();
  int i = 0;
  bool isValid = true;
  for ( ; faceIt != shell.end(); faceIt++)
  {
    if (is_face_planar(*faceIt, lsPts) == false)
    {
      cout << "\tFace #" << i << " not planar" << endl;
      isValid = false;
    }
    i++;
  }
  return isValid;
}  
  
Polyhedron* validateTriangulatedPolyhedraShell( triangulatedPolyhedraShell& tshell, bool isOutershell )
{
   bool isValid = true;
   if (checkPlanarityFaces(tshell.shell, tshell.lsPts) == true)
   {
      Polyhedron* p = getPolyhedronDS(tshell.shell, tshell.lsPts);
      //-- check if polyhedron is 2-manifold (includes intersection tests)
      bool isValid = check2manifoldness(p);
      //-- check if orientation of the normales is outwards or inwards
      if (isValid == true)
      {
         CGAL::Orientation orient = checkGlobalOrientationNormales(p);
         if ( ((isOutershell == true) && (orient != CGAL::CLOCKWISE)) || ((isOutershell == false) && (orient != CGAL::COUNTERCLOCKWISE)) ) 
         {
            cout << "\tNormales all pointing in wrong direction." << endl;
            isValid = false;
         }
      }
      if (isValid == true)
         return p;
      else 
      {
         delete p;
         return NULL;
      }
   }
   else
      return NULL;
}
  
  

CGAL::Orientation checkGlobalOrientationNormales(Polyhedron* p)
{
  //-- get a 'convex corner', sorting order is x-y-z
  Polyhedron::Vertex_iterator vIt;
  vIt = p->vertices_begin();
  Polyhedron::Vertex_handle cc = vIt;
  vIt++;

  for ( ; vIt != p->vertices_end(); vIt++)
  {
    if (vIt->point().x() > cc->point().x())
      cc = vIt;
    else if (vIt->point().x() == cc->point().x())
    {
      if (vIt->point().y() > cc->point().y())
        cc = vIt;
      else if (vIt->point().y() == cc->point().y())
      {
        if (vIt->point().z() > cc->point().z())
          cc = vIt;
      }
    }
  }
//  cout << "CONVEX CORNER IS: " << cc->point() << endl;

  Polyhedron::Halfedge_handle curhe = cc->halfedge();
  Polyhedron::Halfedge_handle otherhe;
  otherhe = curhe->opposite()->next();
  CGAL::Orientation orient = orientation( curhe->vertex()->point(),
                                          curhe->next()->vertex()->point(),
                                          curhe->next()->next()->vertex()->point(),
                                          otherhe->vertex()->point() );
  
  while (orient == CGAL::COPLANAR)
  {
    otherhe = otherhe->next()->opposite()->next();
    orient = orientation( curhe->vertex()->point(),
                          curhe->next()->vertex()->point(),
                          curhe->next()->next()->vertex()->point(),
                          otherhe->vertex()->point() );
  }
  return orient;
}


bool check2manifoldness(Polyhedron* p)
{
  bool isValid = true;
//-- 1. check combinatorial consistency ---
  if (p->empty() == true)
  {
    std::cout << "\tOne/several of the faces have wrong orientation, or dangling faces." << std::endl;
    isValid = false;
  }
  else
  {
    if (p->is_closed() == false)
    {
      cout << "\tOne or more faces are missing, 2-manifold not closed." << endl;
      // TODO: find the missing faces and report
      isValid = false;
    }
    else
    {
// 2. check geometrical consistency (aka intersection tests between faces) ---
      isValid = isPolyhedronGeometricallyConsistent(p);
    }
  }
  return isValid;

//  if (isValid == true)
//  {
//    cout << "2-manifold valid." << endl;
//    cout << "# vertices: " << p->size_of_vertices() << endl;
//    cout << "# faces: " << p->size_of_facets() << endl;
//  }
}



bool isPolyhedronGeometricallyConsistent(Polyhedron* p)
{
  bool isValid = true;
  Polyhedron::Facet_iterator curF, otherF;
  curF = p->facets_begin();
  for ( ; curF != p->facets_end(); curF++)
  {
    Polyhedron::Halfedge_handle heH;
    heH = curF->halfedge();
    Polyhedron::Vertex_handle vh[3];
    vh[0] = heH->vertex();
    vh[1] = heH->next()->vertex();
    vh[2] = heH->next()->next()->vertex();

    //-- check all the incident faces to the 3
    set<Polyhedron::Facet_handle> incidentFaces;
    set<Polyhedron::Facet_handle>::iterator itFh;
    Polyhedron::Halfedge_around_vertex_circulator circ;
    for (int i=0; i<3; i++)
    {
      circ = vh[i]->vertex_begin();
      do 
      {
        incidentFaces.insert(circ->facet());
      } while ( ++circ != vh[i]->vertex_begin() );
    }
    
    otherF = p->facets_begin();
    Triangle t1( vh[0]->point(), vh[1]->point(), vh[2]->point() );
    int count = 0;
    for ( ; otherF != p->facets_end(); otherF++)
    {
      if (otherF != curF)
      {
        Polyhedron::Halfedge_handle heoH = otherF->halfedge();
        Triangle t2( heoH->vertex()->point(), heoH->next()->vertex()->point(), heoH->next()->next()->vertex()->point() );
        
        CGAL::Object re = intersection(t1, t2);
        K::Point_3 apoint;
        K::Segment_3 asegment;
        if (assign(asegment, re))
          count++;
        else if (assign(apoint, re) && (incidentFaces.count(otherF) == 0) )
        {
          cout << "\tSelf-intersection of type POINT." << endl;
          isValid = false;
        }
      }
    }
    if (count > 3)
    {
      cout << "\tSelf-intersection of type SEGMENT." << endl;
      isValid = false;
    }
  }
  return isValid;
}





Polyhedron* getPolyhedronDS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts)
{
  //-- construct the 2-manifold, using the "batch" way
  stringstream offrep (stringstream::in | stringstream::out);
  vector< vector<int*> >::const_iterator it = shell.begin();
  int noFaces = 0;
  for ( ; it != shell.end(); it++)
    noFaces += it->size();
  offrep << "OFF" << endl << lsPts.size() << " " << noFaces << " 0" << endl;

  vector<Point3>::const_iterator itPt = lsPts.begin();
  for ( ; itPt != lsPts.end(); itPt++)
    offrep << *itPt << endl;

  for (it = shell.begin(); it != shell.end(); it++)
  {
    vector<int*>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      int* tmp = *it2;
      offrep << "3 " << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
    }
  }
  Polyhedron* P = new Polyhedron();
  offrep >> *P;
  return P;
}

bool is_face_planar(const vector<int*> &trs, const vector<Point3>& lsPts, float angleTolerance)
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
      if ( (acos(CGAL::to_double(v0*v1))*180/PI) > angleTolerance)
      {
         //      cout << "---face not planar " << (acos((double)(v0*v1))*180/PI) << endl;
         isPlanar = false;
         break;
      }
   }
   return isPlanar;
}

