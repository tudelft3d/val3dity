#ifndef VAL3DITY_VALIDATE_2D_H
#define VAL3DITY_VALIDATE_2D_H

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
#include "val3dity_defs.h"
#include "Shell.h"


// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
bool validate_polygon(vector<Polygon> &lsRings, Shell2* sh, int polygonid, double TOL_PLANARITY_d2p = 0.001);
bool is_face_planar_distance2plane(const vector<Point3> &pts, double& value, float tolerance);
bool is_face_planar_normals(const vector<int*> &trs, const vector<Point3>& lsPts, double& value, float angleTolerance);
bool has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface);
bool has_face_rings_toofewpoints(const vector< vector<int> >& theface);

#endif
