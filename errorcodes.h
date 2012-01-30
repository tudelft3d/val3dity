#ifndef VAL3DITY_ERROR_CODES_H
#define VAL3DITY_ERROR_CODES_H

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

typedef enum
{
   STATUS_OK                              = 0,
   // Ring level
   DUPLICATE_POINTS                       = 100,
   RING_NOT_CLOSED                        = 110,
   // Surface level
   INNER_RING_WRONG_ORIENTATION           = 200,
   NON_PLANAR_SURFACE                     = 210,
   SURFACE_PROJECTION_INVALID             = 220,
   INNER_RING_INTERSECTS_OUTER            = 221,
   INNER_RING_OUTSIDE_OUTER               = 222,
   //INNER_OUTER_RINGS_INTERSECT          = 223,
   INTERIOR_OF_RING_NOT_CONNECTED         = 224,
   // Shell level
   NOT_VALID_2_MANIFOLD                   = 300,
   SURFACE_NOT_CLOSED                     = 301,
   DANGLING_FACES                         = 302,
   FACE_ORIENTATION_INCORRECT_EDGE_USAGE  = 303,
   FREE_FACES                             = 304,
   SURFACE_SELF_INTERSECTS                = 305,
   SURFACE_NORMALS_BAD_ORIENTATION        = 310,
   // Solid level
   SHELLS_FACE_ADJACENT                   = 400,
   SHELL_INTERIOR_INTERSECT               = 410,
   INNER_SHELL_OUTSIDE_OUTER              = 420,
   INTERIOR_OF_SHELL_NOT_CONNECTED        = 430,
   // Processing problem
   INVALID_INPUT_FILE                     = 999
} Val3dity_ErrorCode;

#endif