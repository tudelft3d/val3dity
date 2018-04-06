/*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#ifndef VAL3DITY_VALIDATE_DEFS_H
#define VAL3DITY_VALIDATE_DEFS_H

// CGAL kernel
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/basic.h>
#include <CGAL/Triangulation_vertex_base_with_id_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#include <CGAL/Polyhedron_copy_3.h>

#include <CGAL/Aff_transformation_3.h>

#include <string>

namespace val3dity
{

struct FaceInfo2
{
  FaceInfo2() {}
  int nesting_level;
  bool in_domain() {
    return nesting_level % 2 == 1;
  }
};  

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

//
typedef K::Point_2                  Point2;
typedef K::Point_3                  Point3;
typedef K::Vector_3                 Vector;
typedef K::Triangle_3               Triangle;
typedef K::Tetrahedron_3            Tetrahedron;
typedef K::Plane_3                  Plane;
typedef CGAL::Polygon_2<K>          CGALPolygon;
typedef CGAL::Polyhedron_3<K>       CgalPolyhedron;


// CGAL typedefs
typedef CGAL::Triangulation_vertex_base_with_id_2 <K>             Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2, K>   Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K, Fbb>       Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_intersections_tag                             Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CT;


//-- Nef requires EPEC (exact-predicates & exact-construction) and thus diff kernels
typedef CGAL::Exact_predicates_exact_constructions_kernel   KE;
typedef KE::Point_3                                         Point3E;
typedef KE::Plane_3                                         PlaneE;
typedef CGAL::Polyhedron_3<KE>                              CgalPolyhedronE;
typedef CGAL::Nef_polyhedron_3<KE>                          Nef_polyhedron;
typedef CGAL::Aff_transformation_3<KE>                      Transformation;

typedef CGAL::Polyhedron_copy_3<CgalPolyhedron, CgalPolyhedronE::HalfedgeDS> Polyhedron_convert; 

typedef long long int64;

typedef enum
{
  SOLID            = 0,
  COMPOSITESOLID   = 1,
  MULTISOLID       = 2,
  COMPOSITESURFACE = 3,
  MULTISURFACE     = 4,
  POLYGON          = 5,
  ALL              = 6,
} Primitive3D;

typedef enum
{
  GML   = 0,
  JSON  = 1,
  OBJ   = 2,
  POLY  = 3,
  OFF   = 4,
  OTHER = 5,
} InputTypes;


struct Error {
  int         errorcode;
  std::string info1;
  std::string info2;
};

} // namespace val3dity

#endif
