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

#include "Primitive.h"
#include "input.h"
#include <iostream>

namespace val3dity
{

double Primitive::_shiftx = 0.0;
double Primitive::_shifty = 0.0;


Primitive::Primitive() {
}

Primitive::~Primitive() {
}

void Primitive::set_translation_min_values(double minx, double miny)
{
  Primitive::_shiftx = minx;
  Primitive::_shifty = miny;
}


std::string  Primitive::get_id()
{
  return _id;
}

void Primitive::set_id(std::string id)
{
  _id = id;
}

void Primitive::add_error(int code, std::string whichgeoms, std::string info)
{
  _is_valid = 0;
  std::tuple<std::string, std::string> a(whichgeoms, info);
  _errors[code].push_back(a);
  std::clog << "\tERROR " << code << ": " << errorcode2description(code);
  if (whichgeoms.empty() == false)
    std::clog << " (id: " << whichgeoms << ")";
  std::clog << std::endl;
  if (info.empty() == false)
    std::clog << "\t[" << info << "]" << std::endl;
}

std::set<int> Primitive::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
  {
    errs.insert(std::get<0>(err));
  }
  return errs;
}

} // namespace val3dity
