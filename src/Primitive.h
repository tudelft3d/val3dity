/*
 val3dity - Copyright (c) 2011-2017, Hugo Ledoux.  All rights reserved.
 
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

#ifndef Primitive_h
#define Primitive_h

#include "definitions.h"
#include "nlohmann-json/json.hpp"
#include <map>
#include <vector>
#include <set>
#include <string>

using json = nlohmann::json;


namespace val3dity
{

class Primitive
{
public:
  Primitive  ();
  ~Primitive ();

  virtual bool          validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap = -1) = 0;
  virtual int           is_valid() = 0;
  virtual bool          is_empty() = 0;
  virtual std::string   get_report_xml() = 0;
  virtual json          get_report_json() = 0;
  virtual Primitive3D   get_type() = 0;

  virtual void          get_min_bbox(double& x, double& y) = 0;
  virtual void          translate_vertices() = 0;
  static void           set_translation_min_values(double minx, double miny);

  std::string           get_id();
  void                  set_id(std::string id);
  void                  add_error(int code, std::string whichgeoms, std::string info);
  virtual std::set<int> get_unique_error_codes();

protected:
  std::string           _id;
  int                   _is_valid; 
  static double         _shiftx;
  static double         _shifty;

  std::map<int, std::vector< std::tuple< std::string, std::string > > > _errors;

};


} // namespace val3dity

#endif /* Primitive_h */
