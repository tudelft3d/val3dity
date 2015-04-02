#ifndef VAL3DITY_VALIDATE_DEFS_H
#define VAL3DITY_VALIDATE_DEFS_H

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


// CGAL kernel
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/basic.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Polygon_2.h>


// STL library
#include <vector>
using namespace std;

// CGAL typedefs
#ifdef VAL3DITY_USE_EPECSQRT
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
#else
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
#endif

//
typedef K::Point_2                  Point2;
typedef K::Point_3                  Point3;
typedef K::Vector_3                 Vector;
typedef K::Triangle_3               Triangle;
typedef K::Tetrahedron_3            Tetrahedron;
typedef CGAL::Polyhedron_3<K>       CgalPolyhedron;

// CGAL typedefs
typedef CGAL::Triangulation_vertex_base_with_info_2 <unsigned,K>  Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag>           CTa;
typedef CGAL::Constrained_triangulation_plus_2<CTa>               CT;
typedef CGAL::Polygon_2<K> Polygon;


// convenience structures:
//-- the vector of faces, each which has a vector of rings, 
//-- which is a vector of IDs from vertex pool lsPts
typedef struct fullPolyhedraShell_tag {
   vector< Point3 > lsPts;
   vector< vector< vector<int> > > faces;
} Shell;

typedef struct triangulatedShell_tag {
   vector< Point3 > lsPts;
   vector< vector<int*> > faces;
} TrShell;

typedef enum
{
  SOLID            = 0,
  COMPOSITESURFACE = 1,
  MULTISURFACE     = 2,
} Primitives3D;

// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
typedef void (* cbf)(int errorCode,    // 0 means status message, -1 means unknown error
                     int shellNum, // -1 means unused
                     int facetNum,     // -1 means unused
                     std::string messageStr); // optional

std::string errorcode2description(int code);

#endif
