
/*
 val3dity - Copyright (c) 2011-2015, Hugo Ledoux.  All rights reserved.
 
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
#include "val3dity_defs.h"

#include <CGAL/intersections.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/box_intersection_d.h>
#include <CGAL/Bbox_3.h>

#include<set>
#include<list>

//-- CGAL stuff
typedef CgalPolyhedron::HalfedgeDS              HalfedgeDS;
typedef CGAL::Bbox_3                            Bbox;
typedef K::Segment_3                            Segment;
typedef CgalPolyhedron::Halfedge_const_handle   Halfedge_const_handle;
typedef CgalPolyhedron::Facet_const_iterator    Facet_const_iterator;
typedef CgalPolyhedron::Facet_const_handle      Facet_const_handle;
typedef CGAL::Box_intersection_d::Box_with_handle_d<double, 3, Facet_const_handle> Box;

std::vector<Triangle> gTriangles;

struct Intersect_facets {
  void operator()( const Box* b, const Box* c) const {
    Halfedge_const_handle h = b->handle()->halfedge();
    // check for shared egde --> no intersection
    if ( h->opposite()->facet() == c->handle()
        || h->next()->opposite()->facet() == c->handle()
        || h->next()->next()->opposite()->facet() == c->handle())
      return;
    // check for shared vertex --> maybe intersection, maybe not
    Halfedge_const_handle g = c->handle()->halfedge();
    Halfedge_const_handle v;
    if ( h->vertex() == g->vertex())
      v = g;
    if ( h->vertex() == g->next()->vertex())
      v = g->next();
    if ( h->vertex() == g->next()->next()->vertex())
      v = g->next()->next();
    if ( v == Halfedge_const_handle()) {
      h = h->next();
      if ( h->vertex() == g->vertex())
        v = g;
      if ( h->vertex() == g->next()->vertex())
        v = g->next();
      if ( h->vertex() == g->next()->next()->vertex())
        v = g->next()->next();
      if ( v == Halfedge_const_handle()) {
        h = h->next();
        if ( h->vertex() == g->vertex())
          v = g;
        if ( h->vertex() == g->next()->vertex())
          v = g->next();
        if ( h->vertex() == g->next()->next()->vertex())
          v = g->next()->next();
      }
    }
    if ( v != Halfedge_const_handle()) {
      // found shared vertex:
      CGAL_assertion( h->vertex() == v->vertex());
      // geomtric check if the opposite segments intersect the triangles
      Triangle t1( h->vertex()->point(),
                  h->next()->vertex()->point(),
                  h->next()->next()->vertex()->point());
      Triangle t2( v->vertex()->point(),
                  v->next()->vertex()->point(),
                  v->next()->next()->vertex()->point());
      Segment  s1( h->next()->vertex()->point(),
                  h->next()->next()->vertex()->point());
      Segment  s2( v->next()->vertex()->point(),
                  v->next()->next()->vertex()->point());
      if ( CGAL::do_intersect( t1, s2)) {
        //cerr << "Triangles intersect (t1,s2):\n    T1: " << t1
        //     << "\n    T2 :" << t2 << endl;
        gTriangles.push_back(t1);
        gTriangles.push_back(t2);
      } else if ( CGAL::do_intersect( t2, s1)) {
        //cerr << "Triangles intersect (t2,s1):\n    T1: " << t1
        //     << "\n    T2 :" << t2 << endl;
        gTriangles.push_back(t1);
        gTriangles.push_back(t2);
      }
      return;
    }
    // check for geometric intersection
    Triangle t1( h->vertex()->point(),
                h->next()->vertex()->point(),
                h->next()->next()->vertex()->point());
    Triangle t2( g->vertex()->point(),
                g->next()->vertex()->point(),
                g->next()->next()->vertex()->point());
    if ( CGAL::do_intersect( t1, t2)) {
      //cerr << "Triangles intersect:\n    T1: " << t1 << "\n    T2 :"
      //     << t2 << endl;
      gTriangles.push_back(t1);
      gTriangles.push_back(t2);
    }
  }
};

// is_polyhedron_geometrically_consistent(CgalPolyhedron* p, int shellID)
bool
is_polyhedron_geometrically_consistent(Shell2* sh)
{
  std::vector<Box> boxes;
  CgalPolyhedron* p = sh->get_cgal_polyhedron();
  boxes.reserve(p->size_of_facets());
  for ( Facet_const_iterator i = p->facets_begin(); i != p->facets_end(); ++i)
  {
    boxes.push_back(
                    Box( i->halfedge()->vertex()->point().bbox()
                        + i->halfedge()->next()->vertex()->point().bbox()
                        + i->halfedge()->next()->next()->vertex()->point().bbox(),
                        i));
  }
  std::vector<const Box*> box_ptr;
  box_ptr.reserve(p->size_of_facets());
  for ( std::vector<Box>::iterator j = boxes.begin(); j != boxes.end(); ++j){
    box_ptr.push_back( &*j);
  }
  CGAL::box_self_intersection_d( box_ptr.begin(), box_ptr.end(),
                                Intersect_facets(), std::ptrdiff_t(2000));
  
  if (gTriangles.empty())
    return true;
  else 
  {
    std::stringstream st;
    CGAL::Object re = intersection(gTriangles[0], gTriangles[1]);
    K::Point_3 apoint;
    K::Segment_3 asegment;
    if (assign(asegment, re))
     st << "Segment intersection: " << asegment[0].x() << asegment[0].y() << asegment[0].z() << endl;
    else if (assign(apoint, re))
     st << "Point intersection: " << apoint.x() << apoint.y() << apoint.z() << endl;
    sh->add_error(306, -1, st.str());
    return false;
  }
}

