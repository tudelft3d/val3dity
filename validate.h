#ifndef VAL3DITY_VALIDATE_DEFINITIONS_H
#define VAL3DITY_VALIDATE_DEFINITIONS_H

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

// CGAL kernel
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

// STL library
#include <vector>
using namespace std;

// CGAL typedefs
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel   Ke;
//
typedef K::Point_2        Point2;
typedef K::Point_3        Point3;
typedef K::Vector_3       Vector;
typedef K::Triangle_3     Triangle;
typedef K::Tetrahedron_3  Tetrahedron;


// convenience structure
//-- the vector of faces, each which has a vector of rings, 
//-- which is a vector of IDs from vertex pool lsPts
typedef struct fullPolyhedraShell_tag {
   vector< Point3 > lsPts;
   vector< vector< vector<int> > > shells;
} polyhedraShell;


// This callback function will be used to both report progress
// as well as any validity problems that are encountered.
typedef void (* cbf)(int errorCode,    // 0 means status message, -1 means unknown error
                     int polyhedraNum, // -1 means unused
                     int facetNum,     // -1 means unused
                     std::string messageStr); // optional


// -----------------------------------------------------------
// Usage documentation for this method goes here.
//
void validatePolyhedra(vector<polyhedraShell*> &polyhedraShells, cbf cb);

#endif
