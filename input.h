#ifndef VAL3DITY_INPUT_DEFINITIONS_H
#define VAL3DITY_INPUT_DEFINITIONS_H

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

#include "Shell.h"
#include "Solid.h"
#include <fstream>
#include <string>
#include "pugixml.hpp"
#include <assimp/Importer.hpp>    
#include <assimp/scene.h>         
#include <assimp/postprocess.h>   



class IOErrors {
  std::map<int, vector<std::string> >  _errors;
public:
  bool has_errors();
  void add_error(int code, std::string info);
  std::string get_report_text();
  std::string get_report_xml();
};

std::string   errorcode2description(int code, bool qie = false);
vector<Solid> readGMLfile(std::string &ifile, Primitive3D prim, IOErrors& errs, double tol_snap);
vector<Solid> read3dAssimpfile(std::string &ifile, IOErrors& errs);
Shell*        readPolyfile(std::string &ifile, int shellid, IOErrors& errs);
Shell*        process_gml_compositesurface(pugi::xml_node n, int id, map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
vector<int>   process_gml_ring(pugi::xml_node n, Shell* sh, IOErrors& errs);

void          printProgressBar(int percent);
std::string   localise(std::string s);
#endif
