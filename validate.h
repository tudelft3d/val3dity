#ifndef VAL3DITY_VALIDATE_DEFINITIONS_H
#define VAL3DITY_VALIDATE_DEFINITIONS_H

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

#include <string>
#include "val3dity_defs.h"

// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
bool validate(vector<Shell*> &shells, cbf cb, double TOL_PLANARITY_d2p = 0.01, double TOL_PLANARITY_normals = 1.0, bool multisurface = false);
bool repair(vector<Shell*> &shells, const vector<bool> &repairs, cbf cb);

// -----------------------------------------------------------
// Used for both triangulation of the shell and 2D validation
//
int     projection_plane(const vector< Point3 > &lsPts, const vector<int> &ids);
Vector* polygon_normal(const vector< Point3 > &lsPts, const vector<int> &ids);
bool    create_polygon(const vector< Point3 > &lsPts, const vector<int>& ids, Polygon &p, bool ccworient = false);
bool    check_degenerate_face(const vector< Point3 > &lsPts, const vector<int>& ids);
bool    check_collinear(const vector< Point3 > &lsPts, const vector<int>& ids);

// -----------------------------------------------------------
bool triangulate_one_shell(Shell& shell, int shellNum, TrShell& tshell, cbf cb);

#endif
