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


#include "Primitive.h"
#include "Surface.h"
#include "MultiSurface.h"
#include "CompositeSurface.h"
#include "Solid.h"
#include "CompositeSolid.h"
#include "MultiSolid.h"
#include "Building.h"
#include <fstream>
#include <string>
#include "pugixml.hpp"

namespace val3dity
{

class IOErrors {
  std::map<int, std::vector<std::string> >  _errors;
public:
  bool        has_errors();
  void        add_error(int code, std::string info);
  std::string get_report_text();
  std::string get_report_xml();
};


//--

void          readGMLfile_buildings(std::string &ifile, std::vector<Building*>& lsBuildings, IOErrors& errs, double tol_snap);
void          readGMLfile_primitives(std::string &ifile, std::vector<Primitive*>& lsPrimitives, Primitive3D prim, IOErrors& errs, double tol_snap);
void          get_namespaces(pugi::xml_node& root, std::string& vcitygml);

void          print_information(std::string &ifile);
void          report_primitives(pugi::xml_document& doc, std::map<std::string, std::string>& ns);
void          report_building(pugi::xml_document& doc, std::map<std::string, std::string>& ns);
void          report_building_each_lod(pugi::xml_document& doc, std::map<std::string, std::string>& ns, int lod, int& total_solid, int& total_ms, int& total_sem);
void          get_namespaces(pugi::xml_node& root, std::map<std::string, std::string>& ns, std::string& vcitygml);
void          print_info_aligned(std::string o, size_t number, bool tab = false);

std::string   errorcode2description(int code, bool qie = false);
void          readOBJfile(std::vector<Primitive*>& lsPrimitives, std::string &ifile, IOErrors& errs, double tol_snap);
Surface*      readPolyfile(std::string &ifile, int shellid, IOErrors& errs);
Surface*      readOFFfile(std::string &ifile, int shellid, IOErrors& errs);

Building*     process_citygml_building(const pugi::xml_node& nsolid, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);

Solid*            process_gml_solid(const pugi::xml_node& nsolid, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
MultiSolid*       process_gml_multisolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
CompositeSolid*   process_gml_compositesolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
MultiSurface*     process_gml_multisurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
CompositeSurface* process_gml_compositesurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
Surface*          process_gml_surface(const pugi::xml_node& n, int id, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
std::vector<int>  process_gml_ring(const pugi::xml_node& n, Surface* sh, IOErrors& errs);

void          build_dico_xlinks(pugi::xml_document& doc, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs);

void          printProgressBar(int percent);
std::string   localise(std::string s);

} // namespace val3dity

#endif
