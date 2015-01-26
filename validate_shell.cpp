
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

#include "validate_shell.h"
#include "validate_shell_intersection.h"

#include <CGAL/intersections.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_polyhedron_triangle_primitive.h>
//#include <CGAL/AABB_face_graph_triangle_primitive.h>

#include<set>
#include<list>

//-- misc
#define PI 3.14159265

//-- CGAL stuff
typedef CgalPolyhedron::HalfedgeDS              HalfedgeDS;
typedef CGAL::Bbox_3                            Bbox;
typedef K::Segment_3                            Segment;
typedef CgalPolyhedron::Halfedge_const_handle   Halfedge_const_handle;
typedef CgalPolyhedron::Facet_const_iterator    Facet_const_iterator;
typedef CgalPolyhedron::Facet_const_handle      Facet_const_handle;



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
    :faces(faces), lsPts(lsPts), shellID(shellID), cb(cb), bRepair(bRepair), isValid(true), _width(static_cast<int>(lsPts->size()))
  {
  }
  void operator()( HDS& hds) 
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
    if (bRepair == false)
      construct_faces_order_given(B, cb);
//      construct_faces_keep_adjcent(B, cb);
    else
      construct_faces_flip_when_possible(B, cb);

	//
	if (isValid)
	{
		if (B.check_unconnected_vertices() == true) {
			(*cb)(309, shellID, -1, "");
			B.remove_unconnected_vertices();
		}
	}
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
//        std::cout << a[0] << " - " << a[1] << " - " << a[2] << std::endl;

        add_one_face(B, a[0], a[1], a[2], faceID, cb);
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


  int m2a(int m, int n)
  {
    return (m+(n*_width));
  }
  

  void construct_faces_flip_when_possible(CGAL::Polyhedron_incremental_builder_3<HDS>& B, cbf cb)
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
        (*cb)(307, shellID, faceID, ""); 
   }
      else
        (*cb)(304, shellID, faceID, ""); //-- >2 surfaces incident to an edge: non-manifold
    }
    return ;
  } 
};


//-- function prototypes
CgalPolyhedron*   get_CgalPolyhedron_DS(const vector< vector<int*> >&shell, const vector<Point3>& lsPts);
CgalPolyhedron*   construct_CgalPolyhedron(vector< vector<int*> >&faces, vector<Point3>& lsPts, cbf cb);
bool              check_planarity_normals(vector< vector<int*> >&faces, vector<Point3>& lsPts, int shellID, cbf cb, double tolerance = 0.1);
bool              is_face_planar_normals(const vector<int*>& trs, const vector<Point3>& lsPts, double& value, float angleTolerance);
bool              check_global_orientation_normals(CgalPolyhedron* p, bool bOuter, cbf cb);
bool              check_global_orientation_normals_rev(CgalPolyhedron* p, bool bOuter, cbf cb);
bool              check_global_orientation_normals_rev2(CgalPolyhedron* p, bool bOuter, cbf cb);

//------------------------------------------

CgalPolyhedron* validate_triangulated_shell(TrShell& tshell, int shellID, cbf cb, double TOL_PLANARITY_normals)
{
  bool isValid = true;
  CgalPolyhedron *P = new CgalPolyhedron;

  //-- 0. minimum number of faces = 4
  if (tshell.faces.size() <= 4) {
    (*cb)(301, shellID, -1, "");
    isValid = false;
  }

//-- 1. Planarity of faces
  if (isValid == true) 
  {
    (*cb)(0, -1, -1, "-----Planarity");
    if (check_planarity_normals(tshell.faces, tshell.lsPts, shellID, cb, TOL_PLANARITY_normals) == false)
    {
      isValid = false;
      //(*cb)(0, -1, -1, "\tno");
    }
    else
      (*cb)(0, -1, -1, "\tyes");
  }
    
  
//-- 2. Combinatorial consistency
  if (isValid == true)
  {
    (*cb)(0, -1, -1, "-----Combinatorial consistency");

    //-- here the old simple way to construct Polyhedra can be used.
    //-- construct the CgalPolyhedron with batch operator (not used anymore)
    // P = get_CgalPolyhedron_DS(tshell.faces, tshell.lsPts);
    // std::cout << P->empty() << std::endl;
    // std::cout << P->is_valid() << std::endl;
    // std::cout << P->is_closed() << std::endl;

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
            (*cb)(305, shellID, -1, "");
            isValid = false;
          }
          else
          {
            //-- check if there are holes in the surface
            if (P->is_closed() == false)
            {
              std::stringstream st;
              P->normalize_border();
              while (P->size_of_border_edges() > 0) {
                CgalPolyhedron::Halfedge_handle he = ++(P->border_halfedges_begin());
                st << "Location hole: " << he->vertex()->point();
                (*cb)(302, shellID, -1, st.str());
                st.str("");
                P->fill_hole(he);
                P->normalize_border();
              }
              isValid = false;
            }
          }
        }
        else //-- check if >1 connected components exist (both valid)
        {
          if (P->keep_largest_connected_components(1) > 0) 
          {
            (*cb)(300, shellID, -1, "More than one connected components.");
            isValid = false;
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
    (*cb)(0, -1, -1, "\tyes");
    (*cb)(0, -1, -1, "-----Geometrical consistency");
    isValid = is_polyhedron_geometrically_consistent(P, shellID, cb);
  }
  if (isValid)
  {
	(*cb)(0, -1, -1, "\tyes");
  }
//-- 4. orientation of the normals is outwards or inwards
  if (isValid == true)
  {
    (*cb)(0, -1, -1, "-----Orientation of normals");
    bool bOuter = true;
    if (shellID > 0)
      bOuter = false;
    // TODO: fix that once and for all!
    isValid = check_global_orientation_normals_rev2(P, bOuter, cb);

    if (isValid == false)
      (*cb)(308, shellID, -1, "");
    else
      (*cb)(0, -1, -1, "\tyes");
  }
//-- Return CgalPolyhedron if valid, NULL otherwise
  if (isValid == false)
  {
    delete P;
    P = NULL;
  }

  return P;
}



CgalPolyhedron* repair_triangulated_shell(TrShell& tshell, const vector<bool> &repairs, int shellID, cbf cb)
{
  bool isValid = true;
  CgalPolyhedron *P = new CgalPolyhedron;
  
  //-- 1. Planarity of faces
  //TODO: triangulate non-planar faces? tja, tough...
  if (check_planarity_normals(tshell.faces, tshell.lsPts, shellID, cb) == false)
    isValid = false;
  
  //-- 2. Combinatorial consistency
  if (isValid == true)
  {
    //-- construct the CgalPolyhedron incrementally
    ConstructShell<HalfedgeDS> s(&(tshell.faces), &(tshell.lsPts), shellID, true, cb);
    P->delegate(s);
    isValid = s.isValid;
    //TODO: here the extra vertices are removed automatically (eg for Stanford bunny)
    
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
            (*cb)(305, shellID, -1, "REPAIR: unconnected faces were deleted.");
          }
          else
          {
            //-- check if there are holes in the surface
            if (P->size_of_border_halfedges() > 0)
            {
              (*cb)(302, shellID, -1, "");
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
      bOuter = false;
    isValid = check_global_orientation_normals(P, bOuter, cb);
    if (isValid == false)
    {
      (*cb)(308, shellID, -1, "Normals all have the wrong orientation.");
      P->inside_out();
      isValid = true;
    }
  }
  //-- were the repair operations successfull?
  if (isValid == true)
  {
    (*cb)(0, -1, -1, "Shell is valid.");
    
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

//revised version of check_global_orientation_normals
//should be careful!! still have contradict cases but low probability
bool check_global_orientation_normals_rev( CgalPolyhedron* p, bool bOuter, cbf cb )
{
	/*calculation the AABB tree for select an exterior point outside the bounding box
	and calculate intersections for the ray. selected the closest intersection point and comparing the normal*/
	
	//definitions
	typedef K::Ray_3 Ray;
	typedef K::Triangle_3 Triangle;
	typedef list<Triangle>::iterator Iterator;
	typedef CGAL::AABB_polyhedron_triangle_primitive<K, CgalPolyhedron> Primitive;
	typedef CGAL::AABB_traits<K, Primitive> Traits;
	typedef CGAL::AABB_tree<Traits> AABBTree;

	//build the aabbtree for polyhedron
	AABBTree myTree(p->facets_begin(), p->facets_end());
	if (myTree.empty())
	{
		cout<<"Unable to construct AABB tree"<<endl;;
		return false;
	}
	myTree.accelerate_distance_queries();

	//calculate the exterior point (corner of bbox and shift a bit)
	AABBTree::Bounding_box bbox = myTree.bbox();

	//find the first valid result from the triangle
	float fShift = 100.0;// shift the coordinate of the projected points
	CgalPolyhedron::Facet_iterator fItr = p->facets_begin();
	while (fItr != p->facets_end())
	{
		CgalPolyhedron::Facet_handle fHandle = fItr;
		CgalPolyhedron::Halfedge_handle h = fHandle->halfedge();

		//project the face to one of the axis aligned plane
		Vector vecNormal = CGAL::cross_product(h->next()->vertex()->point() - h->vertex()->point(),
			h->next()->next()->vertex()->point() - h->next()->vertex()->point());
		
		//select the projection plane
		K::FT a = abs(vecNormal * Vector(1.0, 0.0, 0.0));//yz
		K::FT b = abs(vecNormal * Vector(0.0, 1.0, 0.0));//xz
		K::FT c = abs(vecNormal * Vector(0.0, 0.0, 1.0));//xy

		K::FT m = max(max(a, b), c);

		//construct the ray based on the projection
		Ray queryRay;
		Point3 stPt;
		if (CGAL::compare(a, m) == CGAL::EQUAL)
		{
			//yz
			stPt = Point3(bbox.xmax() + fShift, 
				(h->vertex()->point().y() + h->next()->vertex()->point().y() + h->next()->next()->vertex()->point().y())/3, 
				(h->vertex()->point().z() + h->next()->vertex()->point().z() + h->next()->next()->vertex()->point().z())/3);
			Vector vecInwards (-1.0, 0.0, 0.0);
			queryRay = Ray(stPt, vecInwards);
		}
		else if (CGAL::compare(b, m) == CGAL::EQUAL)
		{
			//xz
			stPt = Point3((h->vertex()->point().x() + h->next()->vertex()->point().x() + h->next()->next()->vertex()->point().x())/3,
				bbox.ymax() + fShift, 
				(h->vertex()->point().z() + h->next()->vertex()->point().z() + h->next()->next()->vertex()->point().z())/3);
			Vector vecInwards (0.0, -1.0, 0.0);
			queryRay = Ray(stPt, vecInwards);
		}
		else
		{
			//xy
			stPt = Point3((h->vertex()->point().x() + h->next()->vertex()->point().x() + h->next()->next()->vertex()->point().x())/3,
				(h->vertex()->point().y() + h->next()->vertex()->point().y() + h->next()->next()->vertex()->point().y())/3,
				bbox.zmax() + fShift);
			Vector vecInwards (0.0, 0.0, -1.0);
			queryRay = Ray(stPt, vecInwards);
		}

		//shoot the ray and extract the closed intersection (point and its face)
		list<AABBTree::Object_and_primitive_id> intersections;
		myTree.all_intersections(queryRay, std::back_inserter(intersections));
		//
    K::FT fDistance;
		AABBTree::Object_and_primitive_id Hit;
		//
		list<AABBTree::Object_and_primitive_id>::iterator listItr = intersections.begin();
		CGAL::Object tmpObj = listItr->first;
		Point3 tmpPt;
		if (CGAL::assign(tmpPt, tmpObj))
		{
			fDistance = (tmpPt - stPt).squared_length();
			Hit = *listItr;
		}
		else
		{
			cout<<"Unbelievable!!"<<endl;
			break;
		}
		//
		while(listItr != intersections.end())
		{
			AABBTree::Object_and_primitive_id op = *listItr;
			CGAL::Object obj = op.first;
			Point3 pt;
			if (CGAL::assign(pt, obj))
			{
				//calculate the distance
        K::FT dist = (pt - stPt).squared_length();
				if (fDistance > dist)
				{
					fDistance = dist;
					Hit = *listItr;
					//cout<<fDistance<<endl;
				}
			}
			else
			{
				cout<<"Unbelievable!!"<<endl;
				break;
			}
			++listItr;
		}
		
		//make sure the point is not one of the vertices
		bool bBadLuck = false;
		CgalPolyhedron::Vertex_iterator vItr = p->vertices_begin();
		for (; vItr != p->vertices_end(); vItr++)
		{
			Point3 pt;
			CGAL::assign(pt, Hit.first);
			if (pt == vItr->point())
			{
				bBadLuck = true;
				break;
			}
		}

		//get the answer by comparing the normals
		if (!bBadLuck)
		{
			//calculate the normal of the face
			CgalPolyhedron::Halfedge_handle h = Hit.second->halfedge();
			//cout<<h->vertex()->point()<<" "<<h->next()->vertex()->point()<<" "<<h->next()->next()->vertex()->point()<<endl;
			Vector faceNormal = CGAL::cross_product(h->next()->vertex()->point() - h->vertex()->point(),
				h->next()->next()->vertex()->point() - h->next()->vertex()->point());
			//compare
			K::FT result = faceNormal * queryRay.to_vector();
			if (CGAL::compare(result, 0.0) == CGAL::LARGER)
			{
				return !bOuter;
			}
			else if(CGAL::compare(result, 0.0) == CGAL::SMALLER)
				return bOuter;
		}
		++fItr;
	}
	return false;
}

//using local method proposed by Sjors Donkers
//Requirments: The input polyhedron should be valid without intersections or degeneracies.
bool check_global_orientation_normals_rev2( CgalPolyhedron* p, bool bOuter, cbf cb )
{
	//-- get a 'convex corner' along x
	CgalPolyhedron::Vertex_iterator vIt;
	vIt = p->vertices_begin();
	CgalPolyhedron::Vertex_handle cc = vIt;
	vIt++;

	for ( ; vIt != p->vertices_end(); vIt++)
	{
		if (vIt->point().x() > cc->point().x())
			cc = vIt;
	}
	//-- crop the convex corner using plane yz (x = cc->point().x() - TOL) and get the cropped 2D polygon 
	K::FT TOL(1e-8);
	CgalPolyhedron::Halfedge_around_vertex_circulator hCirc = cc->vertex_begin();//clockwise
	int iNum = CGAL::circulator_size(hCirc);
	Polygon lPgn;
	for (int i = 0; i < iNum; i++)
	{
		//calculate the intersection
		Vector vecR(hCirc->vertex()->point(), hCirc->opposite()->vertex()->point());
		vecR = vecR / sqrt(vecR.squared_length());
		if (CGAL::compare(vecR.x(), 0.0) != CGAL::EQUAL)
		{
			K::FT para = -TOL/vecR.x(); // (cc->point().x() - TOL - cc->point().x()) / vecR.x()
			K::FT y_2d = para * vecR.y() + cc->point().y();
			K::FT z_2d = para * vecR.z() + cc->point().z();
			lPgn.push_back(Polygon::Point_2(y_2d, z_2d));
		}
		else
		{
			//use the parallel edge (convex edge) to decide the orientation
			//The same as 2D method
			CGAL::Orientation orient = orientation( hCirc->vertex()->point(),
				hCirc->next()->vertex()->point(),
				hCirc->next()->next()->vertex()->point(),
				hCirc->opposite()->next()->vertex()->point() );
			if (orient == CGAL::NEGATIVE)
			{
				return bOuter;
			}
			else if (orient == CGAL::POSITIVE)
			{
				return !bOuter;
			}
			else
			{
				//coplanar facets
				Vector vecX (1.0, 0.0, 0.0);
				CgalPolyhedron::Plane_3 plane (hCirc->vertex()->point(),
					hCirc->next()->vertex()->point(),
					hCirc->next()->next()->vertex()->point());
				if (!plane.is_degenerate())
				{
					if (plane.orthogonal_vector()*vecX > 0)
					{
						return bOuter;
					}
					else
					{
						return !bOuter;
					}
				}
			}
		}
		hCirc++;
	}

	//-- check the orientation 
	if (lPgn.is_simple())
	{
		if(lPgn.orientation() == CGAL::CLOCKWISE)
		{
			//equal to the order of circulator
			return bOuter;
		}
		else if(lPgn.orientation() == CGAL::COUNTERCLOCKWISE)
		{
			//unequal to the order of circulator
			return !bOuter;
		}
		else//collinear
			return check_global_orientation_normals_rev(p, bOuter, cb );
	}
	else
	{
		//do ray shooting
		return check_global_orientation_normals_rev(p, bOuter, cb );
	}
}

//problematic
bool check_global_orientation_normals( CgalPolyhedron* p, bool bOuter, cbf cb )
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
	   if (otherhe->next() == curhe->next()->opposite())
	   {
		    //finished the traverse
		   break;
	   }
	   orient = orientation( curhe->vertex()->point(),
	                         curhe->next()->vertex()->point(),
	                         curhe->next()->next()->vertex()->point(),
	                         otherhe->vertex()->point() );
  }
	if ( ((bOuter == true) && (orient != CGAL::CLOCKWISE)) || ((bOuter == false) && (orient != CGAL::COUNTERCLOCKWISE)) ) 
		  return false;
	else
		  return true;

	//revised by John to check whether the normals of the star of the vertex point to the "peak" direction
	/*bool bOrient = true;
	CgalPolyhedron::Halfedge_around_vertex_circulator hcir = curhe->vertex()->vertex_begin();
	int iNum = CGAL::circulator_size(hcir);
	Vector x_direction(1.0, 1.0, 1.0);

	for(int i = 0 ; i < iNum; ++i)
	{
	CgalPolyhedron::Plane_3 plane = CgalPolyhedron::Plane_3(hcir->vertex()->point(),
	hcir->next()->vertex()->point(),
	hcir->next()->next()->vertex()->point());

	cout<<x_direction * plane.orthogonal_vector()<<endl;
	cout<<hcir->vertex()->point()<<", "<<
	hcir->next()->vertex()->point()<<", "<<
	hcir->next()->next()->vertex()->point()<<endl;

	if (CGAL::compare(x_direction * plane.orthogonal_vector(), 0.0) == CGAL::SMALLER)
	{
	bOrient  = false;
	break;
	}

	++hcir;
	}

	if ( ((bOuter == true) && (bOrient)) || ((bOuter == false) && (!bOrient)) ) 
	return true;
	else
	return false;*/
}

CgalPolyhedron* get_CgalPolyhedron_DS(const vector< vector<int*> >&faces, const vector<Point3>& lsPts)
{
  //-- construct the 2-manifold, using the "batch" way
  stringstream offrep (stringstream::in | stringstream::out);
  vector< vector<int*> >::const_iterator it = faces.begin();
  size_t noFaces = 0;
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

bool check_planarity_normals(vector< vector<int*> >&faces, vector<Point3>& lsPts, int shellID, cbf cb, double tolerance)
{
  vector< vector<int*> >::iterator faceIt = faces.begin();
  int i = 0;
  bool isValid = true;
  double value;
  for ( ; faceIt != faces.end(); faceIt++)
  { 
    if (is_face_planar_normals(*faceIt, lsPts, value, tolerance) == false)
    //-- second with normals deviation method
    {
      std::ostringstream msg;
      msg << "deviation normals: " << value << " (tolerance=" << tolerance << ")";
      (*cb)(204, shellID, i, msg.str());
      isValid = false;
    }
    i++;
  }
  return isValid;
}  


bool is_face_planar_normals(const vector<int*> &trs, const vector<Point3>& lsPts, double& value, float angleTolerance)
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
    Vector a = CGAL::cross_product(v0, v1);
    K::FT norm = sqrt(a.squared_length());
    double dot = CGAL::to_double((v0*v1));
    double angle = atan2(CGAL::to_double(norm), dot);
    if (angle*180/PI > angleTolerance)
    {
      // cout << "\t---angle: " << angle*180/PI << endl;
      value = angle*180/PI;
      isPlanar = false;
      break;
    }
  }
  return isPlanar;
}


  



