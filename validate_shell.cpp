
/*
 val3dity - Copyright (c) 2011-2016, Hugo Ledoux.  All rights reserved.
 
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
#include <CGAL/Polygon_mesh_processing/orientation.h>


//-- CGAL stuff
typedef CgalPolyhedron::HalfedgeDS              HalfedgeDS;
typedef CGAL::Bbox_3                            Bbox;
typedef K::Segment_3                            Segment;
typedef CgalPolyhedron::Halfedge_const_handle   Halfedge_const_handle;
typedef CgalPolyhedron::Facet_const_iterator    Facet_const_iterator;
typedef CgalPolyhedron::Facet_const_handle      Facet_const_handle;



CgalPolyhedron* construct_CgalPolyhedron_incremental(vector< vector<int*> > *lsTr, vector<Point3> *lsPts, Shell* sh)
{
  CgalPolyhedron* P = new CgalPolyhedron();
  ConstructShell<HalfedgeDS> s(lsTr, lsPts, sh);
  if (s.isValid)
    P->delegate(s);
  else
  {
    delete P;
    P = NULL;
  }
  return P;
}

template <class HDS>
void ConstructShell<HDS>::operator()( HDS& hds) 
{
  typedef typename HDS::Vertex          Vertex;
  typedef typename Vertex::Point        Point;
  typedef typename HDS::Face_handle     FaceH;
  typedef typename HDS::Halfedge_handle heH;
  CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, false);
  B.begin_surface((*lsPts).size(), (*faces).size());
  vector<Point3>::const_iterator itPt = lsPts->begin();
  for ( ; itPt != lsPts->end(); itPt++)
  { 
    B.add_vertex( Point(itPt->x(), itPt->y(), itPt->z()));
  }
  construct_faces_order_given(B);
  if (isValid)
  {
    if (B.check_unconnected_vertices() == true) {
      sh->add_error(309);
      B.remove_unconnected_vertices();
    }
  }
  B.end_surface();
}

template <class HDS>
void ConstructShell<HDS>::construct_faces_order_given(CGAL::Polyhedron_incremental_builder_3<HDS>& B)
{
  vector< vector<int*> >::const_iterator itF = faces->begin();
  int faceID = 0;
  for ( ; itF != faces->end(); itF++)
  {
    vector<int*>::const_iterator itF2 = itF->begin();
    for ( ; itF2 != itF->end(); itF2++)
    {
      int* a = *itF2;
      add_one_face(B, a[0], a[1], a[2], std::to_string(faceID));
    }
    faceID++;
  }
}

//  void construct_faces_keep_adjcent(CGAL::Polyhedron_incremental_builder_3<HDS>& B, cbf cb)
//  {
//    //-- build a 2D-matrix of usage for each edge
//    int size = static_cast<int>((*lsPts).size());
//    bool halfedges[size*size];
//    for (int i = 0; i <= (size*size); i++)
//      halfedges[i] = false;
//    
//    //-- start with the first face (not only 1st triangle, first original face)
//    vector< vector<int*> >::const_iterator itF = faces->begin();
//    vector<int*>::const_iterator itF2 = itF->begin();
//    for ( ; itF2 != itF->end(); itF2++)
//    {
//      int* a = *itF2;
//      std::vector< std::size_t> faceids(3);        
//      faceids[0] = a[0];
//      faceids[1] = a[1];
//      faceids[2] = a[2];
//      B.add_facet(faceids.begin(), faceids.end());
//      halfedges[m2a(a[0], a[1])] = true;
//      halfedges[m2a(a[1], a[2])] = true;
//      halfedges[m2a(a[2], a[0])] = true;
//    }
//    itF++;
//
//    //-- process the other faces
//    int faceID = 0;
//    for ( ; itF != faces->end(); itF++)
//    {
//      itF2 = itF->begin();
//      for ( ; itF2 != itF->end(); itF2++)
//      {
//        int* a = *itF2;
//        std::vector< std::size_t> faceids(3);        
//        faceids[0] = a[0];
//        faceids[1] = a[1];
//        faceids[2] = a[2];
//        if ( (B.test_facet(faceids.begin(), faceids.end()) ==  true) && (is_connected(a, halfedges) == true) )
//        {
//          B.add_facet(faceids.begin(), faceids.end());
//          halfedges[m2a(a[0], a[1])] = true;
//          halfedges[m2a(a[1], a[2])] = true;
//          halfedges[m2a(a[2], a[0])] = true;
//        }
//      }
//      faceID++;
//    }
//    
//    /////////////////////////////////////////////////
//    
//
//    while (trFaces.size() > 0)
//    {
//      bool success = false;
//      for (list<int*>::iterator it1 = trFaces.begin(); it1 != trFaces.end(); it1++)
//      {
//        int* a = *it1;
//        std::vector< std::size_t> faceids(3);        
//        faceids[0] = a[0];
//        faceids[1] = a[1];
//        faceids[2] = a[2];
////        cout << B.test_facet(faceids.begin(), faceids.end()) << endl;
////        cout << is_connected(a, halfedges) << endl;
//        if ( (B.test_facet(faceids.begin(), faceids.end()) ==  true) && (is_connected(a, halfedges) == true) )
//        {
//          B.add_facet(faceids.begin(), faceids.end());
//          cout << "face added\n";
//          halfedges[m2a(a[0],a[1])] = true;
//          halfedges[m2a(a[1],a[2])] = true;
//          halfedges[m2a(a[2],a[0])] = true;
//          trFaces.erase(it1);
//          success = true;
//          break;
//        }
//      }
//      if (success == false)
//      {
//        (*cb)(304, shellID, 0, "");       
//      }
//    }
//  }

template <class HDS>
int ConstructShell<HDS>::m2a(int m, int n)
{
  return (m+(n*_width));
}

template <class HDS>
void ConstructShell<HDS>::construct_faces_flip_when_possible(CGAL::Polyhedron_incremental_builder_3<HDS>& B)
{
  int size = static_cast<int>((*lsPts).size());
#ifdef WIN32
  bool *halfedges = new bool[size*size];
#else
  bool halfedges[size*size];
#endif
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
#ifdef WIN32
     if (try_to_add_face(B, trFaces, halfedges, true) == false)
#else
     if (try_to_add_face(B, trFaces, &halfedges[0], true) == false)
#endif
    {
      //-- add first face possible, will be dangling by definition
      //cout << "had problems..." << endl;
#ifdef WIN32
       if (try_to_add_face(B, trFaces, halfedges, false) == false)
#else
       if (try_to_add_face(B, trFaces, &halfedges[0], false) == false)
#endif
      {
        //-- cannot repair. non-manifold situations.
        trFaces.clear();
      }
           
    }
  }
#ifdef WIN32
  delete [] halfedges; halfedges = NULL;
#endif
}


template <class HDS>
bool ConstructShell<HDS>::try_to_add_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, list<int*>& trFaces, bool* halfedges, bool bMustBeConnected)
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


template <class HDS>
bool ConstructShell<HDS>::is_connected(int* tr, bool* halfedges)
{
  if ( (halfedges[m2a(tr[1],tr[0])] == true) ||
       (halfedges[m2a(tr[2],tr[1])] == true) ||
       (halfedges[m2a(tr[0],tr[2])] == true) )
    return true;
  else 
    return false;
}

template <class HDS>
void ConstructShell<HDS>::add_one_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, int i0, int i1, int i2, std::string faceID)
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
      sh->add_error(307, faceID);
    else
      sh->add_error(304, faceID); //-- >2 surfaces incident to an edge: non-manifold
  }
  return ;
} 

bool check_global_orientation_normals( CgalPolyhedron* p, bool bOuter)
{
  return CGAL::Polygon_mesh_processing::is_outward_oriented(*p);
}


CgalPolyhedron* construct_CgalPolyhedron_batch(const vector< vector<int*> >&lsTr, const vector<Point3>& lsPts)
{
  //-- construct the 2-manifold, using the "batch" way
  stringstream offrep (stringstream::in | stringstream::out);
  vector< vector<int*> >::const_iterator it = lsTr.begin();
  size_t noFaces = 0;
  for ( ; it != lsTr.end(); it++)
    noFaces += it->size();
  offrep << "OFF" << endl << lsPts.size() << " " << noFaces << " 0" << endl;

  vector<Point3>::const_iterator itPt = lsPts.begin();
  for ( ; itPt != lsPts.end(); itPt++)
    offrep << *itPt << endl;

  for (it = lsTr.begin(); it != lsTr.end(); it++)
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


