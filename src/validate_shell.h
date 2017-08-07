
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

#include "Surface.h"
#include <CGAL/intersections.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/intersections.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

#include <set>
#include <list>

namespace val3dity
{

template <class HDS>
class ConstructShell : public CGAL::Modifier_base<HDS> {
  std::vector< std::vector<int*> > *faces;
  std::vector<Point3> *lsPts;
  int _width;
  Surface* sh;
public:
  bool isValid;
  ConstructShell(std::vector< std::vector<int*> > *faces, std::vector<Point3> *lsPts, Surface* sh)
    :faces(faces), lsPts(lsPts), sh(sh), isValid(true), _width(static_cast<int>(lsPts->size()))
  {
  }
  void operator()( HDS& hds);
  void construct_faces_order_given(CGAL::Polyhedron_incremental_builder_3<HDS>& B);
  int m2a(int m, int n);
  void construct_faces_flip_when_possible(CGAL::Polyhedron_incremental_builder_3<HDS>& B);
  bool try_to_add_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, std::list<int*>& trFaces, bool* halfedges, bool bMustBeConnected);
  bool is_connected(int* tr, bool* halfedges);
  void add_one_face(CGAL::Polyhedron_incremental_builder_3<HDS>& B, int i0, int i1, int i2, std::string faceID) ;
};


CgalPolyhedron*   construct_CgalPolyhedron_incremental(std::vector< std::vector<int*> > *lsTr, std::vector<Point3> *lsPts, Surface* sh);
CgalPolyhedron*   construct_CgalPolyhedron_batch(const std::vector< std::vector<int*> >&lsTr, const std::vector<Point3>& lsPts);
bool              check_global_orientation_normals(CgalPolyhedron* p, bool bOuter);

} // namespace val3dity
