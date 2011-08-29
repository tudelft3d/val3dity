
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

#include "validate_shell.h"


#include <CGAL/intersections.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

#include<set>
#include<list>

//-- misc
#define PI 3.14159265

//-- CGAL stuff
typedef CgalPolyhedron::HalfedgeDS HalfedgeDS;


template <class HDS>
class ConstructShell : public CGAL::Modifier_base<HDS> {
  vector< vector<int*> > *faces;
  vector<Point3> *lsPts;
  int shellID;
  int bRepair;
  int _width;
  cbf cb;
public:
  bool isValid;
  ConstructShell(vector< vector<int*> > *faces, vector<Point3> *lsPts, int shellID, bool bRepair, cbf cb)
    :faces(faces), lsPts(lsPts), shellID(shellID), cb(cb), bRepair(bRepair), isValid(true), _width(lsPts->size())
  {
  }
  void operator()( HDS& hds) 
  {
    typedef typename HDS::Vertex          Vertex;
    typedef typename Vertex::Point        Point;
    typedef typename HDS::Face_handle     FaceH;
    typedef typename HDS::Halfedge_handle heH;
    CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
    B.begin_surface((*lsPts).size(), (*faces).size());
    vector<Point3>::const_iterator itPt = lsPts->begin();
    for ( ; itPt != lsPts->end(); itPt++)
    { 
      B.add_vertex( Point(itPt->x(), itPt->y(), itPt->z()));
    }
    if (bRepair == false)
      construct_faces_order_given(B, cb);
    else
      construct_faces_ensure_adjacency(B, cb);
    B.end_surface();
  }
  
  void construct_faces_order_given(CGAL::Polyhedron_incremental_builder_3<HDS>& B, cbf cb)
  {
    vector< vector<int*> >::const_iterator itF = faces->begin();
    int faceID = 0;
    for ( ; itF != faces->end(); itF++)
    {
      vector<int*>::const_iterator itF2 = itF->begin();
      for ( ; itF2 != itF->end(); itF2++)
      {
        int* a = *itF2;
        add_one_face(B, a[0], a[1], a[2], faceID, cb);
      }
      faceID++;
    }
  }

  int m2a(int m, int n)
  {
    return (m+(n*_width));
  }

  void construct_faces_ensure_adjacency(CGAL::Polyhedron_incremental_builder_3<HDS>& B, cbf cb)
  {
    int size = (*lsPts).size();
    bool *halfedges = new bool[size*size];
    for (int i = 0; i <= (size*size); i++)
      halfedges[i] = false;
    
    //-- build one flat list of the triangular faces, for convenience
    list<int*> trFaces;
    vector< vector<int*> >::const_iterator itF = faces->begin();
    for ( ; itF != faces->end(); itF++)
    {
      vector<int*>::const_iterator itF2 = itF->begin();
      for ( ; itF2 != itF->end(); itF2++)
      {
        int* a = *itF2;
        trFaces.push_back(a);
      }
    }
    
    //-- start with the first one
    int* a = trFaces.front();
    std::vector< std::size_t> faceids(3);        
    faceids[0] = a[0];
    faceids[1] = a[1];
    faceids[2] = a[2];
    B.add_facet(faceids.begin(), faceids.end());

    halfedges[m2a(a[0], a[1])] = true;
    halfedges[m2a(a[1], a[2])] = true;
    halfedges[m2a(a[2], a[0])] = true;

    trFaces.pop_front();
    while (trFaces.size() > 0)
    {
      if (try_to_add_face(B, trFaces, halfedges, true) == false)
      {
        //-- add first face possible, will be dangling by definition
        //cout << "had problems..." << endl;
        if (try_to_add_face(B, trFaces, halfedges, false) == false)
        {
          //-- cannot repair. non-manifold situations.
          trFaces.clear();
        }
             
      }
    }
    delete [] halfedges; halfedges = NULL;
  }

  bool try_to_add_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, list<int*>& trFaces, bool* halfedges, bool bMustBeConnected)
  {
    bool success = false;
    for (list<int*>::iterator it1 = trFaces.begin(); it1 != trFaces.end(); it1++)
    {
      int* a = *it1;
      std::vector< std::size_t> faceids(3);        
      faceids[0] = a[0];
      faceids[1] = a[1];
      faceids[2] = a[2];
      bool test = B.test_facet(faceids.begin(), faceids.end());
      if (test == true)
      {
        if ( (bMustBeConnected == false) || (is_connected(a, halfedges) == true) )
        {
          B.add_facet(faceids.begin(), faceids.end());
          halfedges[m2a(a[0],a[1])] = true;
          halfedges[m2a(a[1],a[2])] = true;
          halfedges[m2a(a[2],a[0])] = true;
          trFaces.erase(it1);
          success = true;
          break;
        }
      }
      else //-- face conflicts with one, try to flip it and insert if possible
      {
        faceids[1] = a[2];
        faceids[2] = a[1];
        if (B.test_facet(faceids.begin(), faceids.end()))
        {
          B.add_facet(faceids.begin(), faceids.end());
          halfedges[m2a(a[0],a[1])] = true;
          halfedges[m2a(a[1],a[2])] = true;
          halfedges[m2a(a[2],a[0])] = true;
          trFaces.erase(it1);
          success = true;
          break;
        }
      }
    }
    return success;
  }
  
  
  bool is_connected(int* tr, bool* halfedges)
  {
    if ( (halfedges[m2a(tr[1],tr[0])] == true) ||
         (halfedges[m2a(tr[2],tr[1])] == true) ||
         (halfedges[m2a(tr[0],tr[2])] == true) )
      return true;
    else 
      return false;
  }
  
  void add_one_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, int i0, int i1, int i2, int faceID, cbf cb)
  {
    std::vector< std::size_t> faceids(3);        
    faceids[0] = i0;
    faceids[1] = i1;
    faceids[2] = i2;
    if (B.test_facet(faceids.begin(), faceids.end()))
        B.add_facet(faceids.begin(), faceids.end());
    else
    { //-- reverse the face and test if it would be possible to insert it
      isValid = false;
      faceids[0] = i0;
      faceids[1] = i2;
      faceids[2] = i1;
      if (B.test_facet(faceids.begin(), faceids.end()))
      {
        //std::cout << "*** Reversed orientation of the face" << std::endl;
        (*cb)(303, shellID, faceID, ""); //-- face was wrongly oriented, locally at least
/*        if (bRepair)
        {
          std::cout << "Fixin' it: flipped a face..." << std::endl;
          B.add_facet(faceids.begin(), faceids.end());
        }
*/    }
      else
        (*cb)(302, shellID, faceID, ""); //-- >2 surfaces incident to an edge: non-manifold
    }
    return ;
  } 
};



//-- function prototypes
CgalPolyhedron*   get_CgalPolyhedron_DS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts);
CgalPolyhedron*   construct_CgalPolyhedron(vector< vector<int*> >&faces, vector<Point3>& lsPts, cbf cb);
bool              check_planarity_faces(vector< vector<int*> >&faces, vector<Point3>& lsPts, int shellID, cbf cb);
bool              is_face_planar(const vector<int*>& trs, const vector<Point3>& lsPts, float angleTolerance, cbf cb);
bool              check_global_orientation_normales(CgalPolyhedron* p, bool bOuter, cbf cb);
bool              is_polyhedron_geometrically_consistent(CgalPolyhedron* p, int shellID, cbf cb);


//------------------------------------------

CgalPolyhedron* validate_triangulated_shell(TrShell& tshell, int shellID, bool bRepair, cbf cb)
{
  bool isValid = true;
  //CgalPolyhedron P;
  CgalPolyhedron *P = new CgalPolyhedron;

//-- ***** VALIDATION ONLY *****
  if (bRepair == false)
  {
//-- 1. Planarity of faces   
    if (check_planarity_faces(tshell.faces, tshell.lsPts, shellID, cb) == false)
      isValid = false;
    
  //-- 2. Combinatorial consistency
    if (isValid == true)
    {
      //-- construct the CgalPolyhedron incrementally
      ConstructShell<HalfedgeDS> s(&(tshell.faces), &(tshell.lsPts), shellID, false, cb);
      P->delegate(s);
      isValid = s.isValid;
      
      
      if (isValid == true)
      {
        if (P->is_valid() == true) //-- combinatorially valid that is
        {
          if (P->is_closed() == false)
          {
            P->normalize_border();
            //-- check for unconnected faces
            if (P->keep_largest_connected_components(1) > 0)
            {
              //TODO: how to report what face is not connected? a bitch of a problem...
              (*cb)(304, shellID, -1, "");
              isValid = false;
            }
            else
            {
              //-- check is there are holes in the surface
              if (P->size_of_border_halfedges() > 0)
              {
                (*cb)(301, shellID, -1, "");
                //TODO: how to report where the hole is? report one of the edge? centre of the hole?
                isValid = false;
              }
            }
          }
        }
        else 
        {
          (*cb)(300, shellID, -1, "Something weird went wrong during construction of the shell, not sure what...");
          isValid =  false;
        }
      }
    }

  //-- 3. Geometrical consistency (aka intersection tests between faces)
    if (isValid == true)
    {
      isValid = is_polyhedron_geometrically_consistent(P, shellID, cb);
    }
    
  //-- 4. orientation of the normales is outwards or inwards
    if (isValid == true)
    {
      bool bOuter = true;
      if (shellID > 0)
        bool bOuter = false;
      isValid = check_global_orientation_normales(P, bOuter, cb);
      if (isValid == false)
      {
        (*cb)(310, shellID, -1, "");
      }
    }
  }
//-- ***** REPAIRING IS ATTEMPTED *****
  else
  {
//-- 1. Planarity of faces   
    if (check_planarity_faces(tshell.faces, tshell.lsPts, shellID, cb) == false)
      isValid = false;
    
//-- 2. Combinatorial consistency
    if (isValid == true)
    {
      //-- construct the CgalPolyhedron incrementally
      ConstructShell<HalfedgeDS> s(&(tshell.faces), &(tshell.lsPts), shellID, true, cb);
      P->delegate(s);
      isValid = s.isValid;
      
      if  (isValid == true)
      {
        if (P->is_valid() == true) //-- combinatorially valid that is
        {
          if (P->is_closed() == false)
          {
            P->normalize_border();
            //-- check for unconnected faces
            if (P->keep_largest_connected_components(1) > 0)
            {
              //TODO: how to report what face is not connected? a bitch of a problem...
              (*cb)(304, shellID, -1, "REPAIR: unconnected faces were deleted.");
            }
            else
            {
              //-- check is there are holes in the surface
              if (P->size_of_border_halfedges() > 0)
              {
                (*cb)(301, shellID, -1, "");
                //TODO: how to report where the hole is? report one of the edge? centre of the hole?
                isValid = false;
              }
            }
          }
          //-- test if the repair operation(s) worked
          if ( (P->is_valid()) && (P->is_closed()) )
          {
            isValid = true;
            (*cb)(0, -1, -1, "Topology of the shell was successfully repaired.");
          }
          else
          {
            isValid = false;
            (*cb)(0, -1, -1, "Could not repair topology of the shell.");
          }
        }
        else 
        {
          (*cb)(300, shellID, -1, "Something weird went wrong during construction of the shell, not sure what...");
          isValid =  false;
        }
      }
    }

//-- 3. Geometrical consistency (aka intersection tests between faces)
    if (isValid == true)
    {
      isValid = is_polyhedron_geometrically_consistent(P, shellID, cb);
    }
    
//-- 4. orientation of the normales is outwards or inwards
    if (isValid == true)
    {
      bool bOuter = true;
      if (shellID > 0)
        bool bOuter = false;
      isValid = check_global_orientation_normales(P, bOuter, cb);
      if (isValid == false)
      {
        (*cb)(310, shellID, -1, "Normales are flipped.");
        P->inside_out();
        isValid = true;
      }
    }
//-- were the repair operations successfull?
    if (isValid == true)
    {
      (*cb)(0, -1, -1, "Shell is valid.");
      
    }    
  }  
  
//-- Return CgalPolyhedron if valid, NULL otherwise  
  if (isValid == false)
  {
    delete P;
    P = NULL;
  }
  return P;
}


CgalPolyhedron* construct_CgalPolyhedron(vector< vector<int*> >&faces, vector<Point3>& lsPts, cbf cb)
{
/*  CgalPolyhedron P;
  ConstructShell<HalfedgeDS> s(&faces, &lsPts, cb);
  P.delegate(s);
  std::cout << "***valid? " << P.is_valid() << std::endl;
  std::cout << "closed? " << P.is_closed() << std::endl;
  std::cout << "# facets: "   << P.size_of_facets() << std::endl;
  std::cout << "# halfedges: "    << P.size_of_halfedges() << std::endl;
  std::cout << "# vertices "  << P.size_of_vertices() << std::endl;
*/  
  return NULL;
}



bool check_global_orientation_normales(CgalPolyhedron *p, bool bOuter, cbf cb)
{
  //-- get a 'convex corner', sorting order is x-y-z
  CgalPolyhedron::Vertex_iterator vIt;
  vIt = p->vertices_begin();
  CgalPolyhedron::Vertex_handle cc = vIt;
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

  CgalPolyhedron::Halfedge_handle curhe = cc->halfedge();
  CgalPolyhedron::Halfedge_handle otherhe;
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
  if ( ((bOuter == true) && (orient != CGAL::CLOCKWISE)) || ((bOuter == false) && (orient != CGAL::COUNTERCLOCKWISE)) ) 
    return false;
  else
    return true;
}


bool is_polyhedron_geometrically_consistent(CgalPolyhedron *p, int shellID, cbf cb)
{
  bool isValid = true;
  CgalPolyhedron::Facet_iterator curF, otherF;
  curF = p->facets_begin();
  for ( ; curF != p->facets_end(); curF++)
  {
    CgalPolyhedron::Halfedge_handle heH;
    heH = curF->halfedge();
    CgalPolyhedron::Vertex_handle vh[3];
    vh[0] = heH->vertex();
    vh[1] = heH->next()->vertex();
    vh[2] = heH->next()->next()->vertex();

    //-- check all the incident faces to the 3
    set<CgalPolyhedron::Facet_handle> incidentFaces;
    set<CgalPolyhedron::Facet_handle>::iterator itFh;
    CgalPolyhedron::Halfedge_around_vertex_circulator circ;
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
        CgalPolyhedron::Halfedge_handle heoH = otherF->halfedge();
        Triangle t2( heoH->vertex()->point(), heoH->next()->vertex()->point(), heoH->next()->next()->vertex()->point() );
        
        CGAL::Object re = intersection(t1, t2);
        K::Point_3 apoint;
        K::Segment_3 asegment;
        if (assign(asegment, re))
          count++;
        else if (assign(apoint, re) && (incidentFaces.count(otherF) == 0) )
        { //TODO: report which faces are involved.
          (*cb)(305, shellID, -1, "Self-intersection of type POINT.");
          isValid = false;
        }
      }
    }
    if (count > 3)
    {
      (*cb)(305, shellID, -1, "Self-intersection of type SEGMENT.");
      isValid = false;
    }
  }
  return isValid;
}


CgalPolyhedron* get_CgalPolyhedron_DS(const vector< vector<int*> >&faces, const vector<Point3>& lsPts)
{
  //-- construct the 2-manifold, using the "batch" way
  stringstream offrep (stringstream::in | stringstream::out);
  vector< vector<int*> >::const_iterator it = faces.begin();
  int noFaces = 0;
  for ( ; it != faces.end(); it++)
    noFaces += it->size();
  offrep << "OFF" << endl << lsPts.size() << " " << noFaces << " 0" << endl;

  vector<Point3>::const_iterator itPt = lsPts.begin();
  for ( ; itPt != lsPts.end(); itPt++)
    offrep << *itPt << endl;

  for (it = faces.begin(); it != faces.end(); it++)
  {
    vector<int*>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      int* tmp = *it2;
      offrep << "3 " << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
    }
  }
  CgalPolyhedron* P = new CgalPolyhedron();
  offrep >> *P;
  return P;
}


bool check_planarity_faces(vector< vector<int*> >&faces, vector<Point3>& lsPts, int shellID, cbf cb)
{
  vector< vector<int*> >::iterator faceIt = faces.begin();
  int i = 0;
  bool isValid = true;
  for ( ; faceIt != faces.end(); faceIt++)
  {
    if (is_face_planar(*faceIt, lsPts, 1, cb) == false)
    {
       (*cb)(210, shellID, i, "");
       isValid = false;
    }
    i++;
  }
  return isValid;
}  

bool is_face_planar(const vector<int*> &trs, const vector<Point3>& lsPts, float angleTolerance, cbf cb)
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
  



