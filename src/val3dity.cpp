/*
  val3dity 

  Copyright (c) 2011-2023, 3D geoinformation research group, TU Delft

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of the Built Environment & Architecture
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#include "val3dity.h"
#include "Feature.h"
#include "CityObject.h"
#include "GenericObject.h"
#include "Solid.h"
#include "Surface.h"
#include "input.h"

#include <iostream>
#include <exception>      // std::exception



namespace val3dity
{

std::string VAL3DITY_VERSION = "2.4.0b0";

//-----

json
validate_cityjson(json& j, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

json
validate_cityjsonfeature(json& j, 
                         double tol_snap=0.001, 
                         double planarity_d2p_tol=0.01, 
                         double planarity_n_tol=20.0, 
                         double overlap_tol=-1.0);

json
validate_tu3djson(json& j,
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

json 
validate_jsonfg(json& j,
                double tol_snap=0.001, 
                double planarity_d2p_tol=0.01, 
                double planarity_n_tol=20.0, 
                double overlap_tol=-1.0);

json 
validate_onegeom(json& j,
                 double tol_snap=0.001, 
                 double planarity_d2p_tol=0.01, 
                 double planarity_n_tol=20.0, 
                 double overlap_tol=-1.0);

json
validate_indoorgml(std::string& input, 
                   double tol_snap=0.001, 
                   double planarity_d2p_tol=0.01, 
                   double planarity_n_tol=20.0, 
                   double overlap_tol=-1.0);
 

json
validate_obj(std::string& input, 
             double tol_snap=0.001, 
             double planarity_d2p_tol=0.01, 
             double planarity_n_tol=20.0, 
             double overlap_tol=-1.0);

json
validate_off(std::string& input, 
             double tol_snap=0.001, 
             double planarity_d2p_tol=0.01, 
             double planarity_n_tol=20.0, 
             double overlap_tol=-1.0);
//-----

struct verror : std::exception {
  std::string whattext;
  verror(std::string s) : whattext(s){};
  const char* what() const noexcept {return whattext.c_str();}
};


bool 
is_valid(json& j,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  json re = validate(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);  
  return re["validity"];
}


json 
validate(json& j,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  std::streambuf* clog_buf = std::clog.rdbuf();
  std::clog.rdbuf(NULL);
  std::streambuf* cout_buf = std::cout.rdbuf();
  std::cout.rdbuf(NULL);
  json re;
  //-- CityJSON
  if (j["type"] == "CityJSON") {
    json jr = validate_cityjson(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;
  
  //-- CityJSONFeature
  } else if (j["type"] == "CityJSONFeature") {
    json jr = validate_cityjsonfeature(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;
  
  //-- tu3djson
  } else if (j["type"] == "tu3djson") {
    json jr = validate_tu3djson(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;
  
  //-- JSON-FG
  } else if (j["type"] == "Feature") { 
    json jr = validate_jsonfg(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;
  } else if (j["type"] == "FeatureCollection") { 
    json jr = validate_jsonfg(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;

  //-- tu3djson onegeom
  } else if ( (j["type"] == "MultiSurface") || 
              (j["type"] == "CompositeSurface") ||
              (j["type"] == "Solid") ||
              (j["type"] == "MultiSolid") ||
              (j["type"] == "CompositeSolid") ) { 
    json jr = validate_onegeom(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = jr;

  //-- then we don't support it   
  } else {
    std::clog.rdbuf(clog_buf);
    std::cout.rdbuf(cout_buf);
    throw verror("Flavour of JSON not supported");
  }  
  std::clog.rdbuf(clog_buf);
  std::cout.rdbuf(cout_buf);
  return re;
}

//-- for ASCII + XML formats
bool 
is_valid(std::string& input,
         std::string format,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  json re = validate(input, format, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);  
  return re["validity"];
}

json
validate(std::string& input,
         std::string format,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  std::streambuf* clog_buf = std::clog.rdbuf();
  std::clog.rdbuf(NULL);
  std::streambuf* cout_buf = std::cout.rdbuf();
  std::cout.rdbuf(NULL);
  json re;
  if (format == "IndoorGML") {
    json j = validate_indoorgml(input, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = j;
  }
  else if (format == "OBJ") {
    json j = validate_obj(input, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = j;
  }
  else if (format == "OFF") {
    json j = validate_off(input, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    re = j;
  }
  else { 
    std::clog.rdbuf(clog_buf);
    std::cout.rdbuf(cout_buf);
    throw verror("File type not supported");
  }
  std::clog.rdbuf(clog_buf);
  std::cout.rdbuf(cout_buf);
  return re;
}


json 
validate_onegeom(json& j,
                 double tol_snap, 
                 double planarity_d2p_tol, 
                 double planarity_n_tol, 
                 double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson_onegeom(j, lsFeatures, tol_snap);
  //-- validate
  for (auto& f : lsFeatures)
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- get report in json 
  IOErrors ioerrs;
  ioerrs.set_input_file_type("tu3djson_geom");
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}

bool
is_valid_tu3djson(json& j,
                  double tol_snap, 
                  double planarity_d2p_tol, 
                  double planarity_n_tol, 
                  double overlap_tol)
{
  json jr = validate_tu3djson(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
  return jr["validity"];
}


json validate_jsonfg(json& j,
                     double tol_snap, 
                     double planarity_d2p_tol, 
                     double planarity_n_tol, 
                     double overlap_tol)
{
  IOErrors ioerrs;
  ioerrs.set_input_file_type("JSON-FG");
  std::vector<Feature*> lsFeatures;
  parse_jsonfg(j, lsFeatures, tol_snap, ioerrs);
  //-- validate
  for (auto& f : lsFeatures)  
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- get report in json 
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}

json validate_tu3djson(json& j,
                       double tol_snap, 
                       double planarity_d2p_tol, 
                       double planarity_n_tol, 
                       double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson(j, lsFeatures, tol_snap);
  //-- validate
  for (auto& f : lsFeatures)
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- get report in json 
  IOErrors ioerrs;
  ioerrs.set_input_file_type("tu3djson");
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}


json 
validate_cityjson(json& j,
                  double tol_snap, 
                  double planarity_d2p_tol, 
                  double planarity_n_tol, 
                  double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  //-- parse the cityjson object
  //-- compute (_minx, _miny)
  compute_min_xy(j);
  //-- read and store the GeometryTemplates
  std::vector<GeometryTemplate*> lsGTs;
  if (j.count("geometry-templates") == 1)
  {
    process_cityjson_geometrytemplates(j["geometry-templates"], lsGTs, tol_snap);
  }
  //-- process each CO
  for (json::iterator it = j["CityObjects"].begin(); it != j["CityObjects"].end(); ++it) 
  {
    //-- BuildingParts geometries are put with those of a Building
    if (it.value()["type"] == "BuildingPart")
      continue;
    CityObject* co = new CityObject(it.key(), it.value()["type"]);
    process_json_geometries_of_co(it.value(), co, lsGTs, j, tol_snap);
    //-- if Building has Parts, put them here in _lsPrimitives
    if ( (it.value()["type"] == "Building") && (it.value().count("children") != 0) ) 
    {
      for (std::string bpid : it.value()["children"])
      {
        process_json_geometries_of_co(j["CityObjects"][bpid], co, lsGTs, j, tol_snap);
      }
    }
    lsFeatures.push_back(co);
  }
  //-- validate
  for (auto& f : lsFeatures)
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- compile errors
  std::set<int> errors;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      for (auto& code : p->get_unique_error_codes())
        errors.insert(code);
  //-- get report in json 
  IOErrors ioerrs;
  ioerrs.set_input_file_type("CityJSON");
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}


json 
validate_cityjsonfeature(json& j,
                         double tol_snap, 
                         double planarity_d2p_tol, 
                         double planarity_n_tol, 
                         double overlap_tol)
{
  // j["transform"] = jtransform;
  std::vector<Feature*> lsFeatures;
  //-- compute (_minx, _miny)
  compute_min_xy(j);
  //-- list empty GeometryTemplate TODO: populate this?
  std::vector<GeometryTemplate*> lsGTs;
  //-- process each CO
  for (json::iterator it = j["CityObjects"].begin(); it != j["CityObjects"].end(); ++it) 
  {
    //-- BuildingParts geometries are put with those of a Building
    if (it.value()["type"] == "BuildingPart")
      continue;
    CityObject* co = new CityObject(it.key(), it.value()["type"]);
    process_json_geometries_of_co(it.value(), co, lsGTs, j, tol_snap);
    //-- if Building has Parts, put them here in _lsPrimitives
    if ( (it.value()["type"] == "Building") && (it.value().count("children") != 0) ) 
    {
      for (std::string bpid : it.value()["children"])
      {
        process_json_geometries_of_co(j["CityObjects"][bpid], co, lsGTs, j, tol_snap);
      }
    }
    lsFeatures.push_back(co);
  }
  //-- validate
  for (auto& f : lsFeatures)
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- compile errors
  std::set<int> errors;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      for (auto& code : p->get_unique_error_codes())
        errors.insert(code);
  //-- get report in json 
  IOErrors ioerrs;
  ioerrs.set_input_file_type("CityJSONFeature");
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}


json
validate_indoorgml(std::string& input, 
                   double tol_snap, 
                   double planarity_d2p_tol, 
                   double planarity_n_tol, 
                   double overlap_tol) 
{
  IOErrors ioerrs;
  ioerrs.set_input_file_type("IndoorGML");
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string(input.c_str());
  if (!result) {
    ioerrs.add_error(901, "Input value not valid XML");
  }
  std::vector<Feature*> lsFeatures;
  if (ioerrs.has_errors() == false) {
    //-- parse namespace
    pugi::xml_node ncm = doc.first_child();
    std::map<std::string, std::string> thens = get_namespaces(ncm); //-- results in global variable NS in this unit
    if ( (thens.count("indoorgml") != 0) && (ncm.name() == (thens["indoorgml"] + "IndoorFeatures")) ) {
      //-- find (_minx, _miny)
      compute_min_xy(doc);
      //-- build dico of xlinks for <gml:Polygon>
      std::map<std::string, pugi::xpath_node> dallpoly;
      build_dico_xlinks(doc, dallpoly, ioerrs);
      ioerrs.set_input_file_type("IndoorGML");
      process_gml_file_indoorgml(doc, lsFeatures, dallpoly, ioerrs, tol_snap);
    }
    else
    {
      ioerrs.add_error(904, "GML files not supported (yes that includes CityGML files ==> upgrade to CityJSON)");
    }
  }
  //-- start the validation
  if (ioerrs.has_errors() == false) {
    //-- validate
    for (auto& f : lsFeatures)
      f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  }
  //-- get report in json 
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}


json
validate_obj(std::string& input, 
             double tol_snap, 
             double planarity_d2p_tol, 
             double planarity_n_tol, 
             double overlap_tol) 
{
  IOErrors ioerrs;
  ioerrs.set_input_file_type("OBJ");
  std::vector<Feature*> lsFeatures;
  std::istringstream iss(input);
  parse_obj(iss, lsFeatures, SOLID, ioerrs, tol_snap);
  //-- start the validation
  if (ioerrs.has_errors() == false) {
    //-- validate
    for (auto& f : lsFeatures)
      f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  }
  //-- get report in json 
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  return jr;
}

json
validate_off(std::string& input, 
             double tol_snap, 
             double planarity_d2p_tol, 
             double planarity_n_tol, 
             double overlap_tol) 
{
  IOErrors ioerrs;
  ioerrs.set_input_file_type("OFF");
  std::vector<Feature*> lsFeatures;
  GenericObject* o = new GenericObject("none");
  std::istringstream iss(input);
  Surface* sh = parse_off(iss, 0, ioerrs, tol_snap);
  std::cout << "1" << std::endl;
  Solid* s = new Solid;
  s->set_oshell(sh);
  o->add_primitive(s);
  lsFeatures.push_back(o);
  //-- start the validation
  // std::cout << "errors: " << ioerrs.has_errors() << std::endl;
  for (auto& each : ioerrs.get_unique_error_codes())
    std::cout << each << std::endl;

  // if (ioerrs.has_errors() == false) {
    //-- validate
    for (auto& f : lsFeatures)
      f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  // }
  std::cout << "2" << std::endl;
  //-- get report in json 
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  std::cout << "3" << std::endl;
  return jr;
}


}