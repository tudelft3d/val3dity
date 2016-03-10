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

#ifndef __val3dity__Solid__
#define __val3dity__Solid__

#include "Shell.h"
#include "definitions.h"

#include <tuple>

class Solid
{
public:
  Solid();
  Solid(Shell* sh);
  ~Solid();
  
  Shell*                 get_oshell();
  void                   set_oshell(Shell* sh);
  Shell*                 get_ishell(int i);
  void                   add_ishell(Shell* sh);
  const vector<Shell*>&  get_shells();
  int                    num_ishells();
  int                    num_faces();
  int                    num_vertices();
  
  bool          validate(Primitive3D prim, double tol_planarity_d2p, double tol_planarity_normals);
  std::string   get_report_xml();
  std::string   get_report_text();
  void          add_error(int code, int shell1, int shell2, std::string info);
  std::set<int> get_unique_error_codes();
  std::string   get_poly_representation();
  bool          is_valid();
  bool          is_empty();
  
  static int    _counter;
  std::string   get_id();
  void          set_id(std::string id);
private:
  std::string     _id;
  vector<Shell*>  _shells;
  int             _is_valid;
  std::map<int, vector< std::tuple<int, int, std::string> > > _errors;

  bool validate_solid_with_nef();
};


#endif /* defined(__val3dity__Solid__) */
