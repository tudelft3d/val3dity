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

#ifndef __val3dity__geomtools__
#define __val3dity__geomtools__

#include "definitions.h"

namespace val3dity
{

//-- misc
#define PI 3.14159265

bool    cmpPoint3(Point3 &p1, Point3 &p2, double tol);
void    get_best_fitted_plane(const std::vector< Point3 > &lsPts, CgalPolyhedron::Plane_3 &plane);
void    create_cgal_polygon(const std::vector<Point3>& lsPts, const std::vector<int>& ids, const CgalPolyhedron::Plane_3 &plane, Polygon &outpgn);
bool    is_face_planar_distance2plane(const std::vector<Point3> &pts, const CgalPolyhedron::Plane_3 &plane, double& value, float tolerance);
bool    is_face_planar_normals(const std::vector<int*> &trs, const std::vector<Point3>& lsPts, double& value, float angleTolerance);

Nef_polyhedron* dilate_nef_polyhedron(Nef_polyhedron* nef, float r);
Nef_polyhedron* erode_nef_polyhedron (Nef_polyhedron* nef, float r);
Nef_polyhedron* get_structuring_element_cube(float r);
Nef_polyhedron* get_structuring_element_dodecahedron(float r);
Nef_polyhedron* get_aabb(Nef_polyhedron* mynef) ;

} // namespace val3dity

#endif /* defined(__val3dity__geomtools__) */
