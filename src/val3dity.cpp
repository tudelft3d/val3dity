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
#include "input.h"

#include <iostream>
#include <exception>      // std::exception



namespace val3dity
{

std::string VAL3DITY_VERSION = "2.3.1";

//-----

json
validate_cityjson(json& j, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

json
validate_cityjsonfeature(json& j, 
                         json jtransform,
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

//-----

struct verror : std::exception {
  std::string whattext;
  verror(std::string s) : whattext(s){};
  const char* what() const noexcept {return whattext.c_str();}
};


bool 
is_valid(json& j,
         json jtransform,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  json re = validate(j, jtransform, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);  
  return re["validity"];
}


json 
validate(json& j,
         json jtransform,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  //-- CityJSON
  if (j["type"] == "CityJSON") {
    json jr = validate_cityjson(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;
  
  //-- CityJSONFeature
  } else if (j["type"] == "CityJSONFeature") {
    json jr = validate_cityjsonfeature(j, jtransform, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;
  
  //-- tu3djson
  } else if (j["type"] == "tu3djson") {
    json jr = validate_tu3djson(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;
  
  //-- JSON-FG
  } else if (j["type"] == "Feature") { 
    json jr = validate_jsonfg(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;
  } else if (j["type"] == "FeatureCollection") { 
    json jr = validate_jsonfg(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;

  //-- tu3djson onegeom
  } else if ( (j["type"] == "MultiSurface") || 
              (j["type"] == "CompositeSurface") ||
              (j["type"] == "Solid") ||
              (j["type"] == "MultiSolid") ||
              (j["type"] == "CompositeSolid") ) { 
    json jr = validate_onegeom(j, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
    return jr;

  //-- then we don't support it   
  } else {
    throw verror("File format not supported");
  }  
  return true;
}

//-- for XML/ASCII-based formats
bool 
is_valid(const char* input,
         double tol_snap, 
         double planarity_d2p_tol, 
         double planarity_n_tol, 
         double overlap_tol)
{
  throw verror("File format not supported");
  return true;
}



void 
validate_no_coutclog(std::vector<Feature*>& lsFeatures,                        
                     double planarity_d2p_tol, 
                     double planarity_n_tol, 
                     double overlap_tol)
{
  //-- disable cout+clog
  std::streambuf* clog_buf = std::clog.rdbuf();
  std::clog.rdbuf(NULL);
  std::streambuf* cout_buf = std::cout.rdbuf();
  std::cout.rdbuf(NULL);
  //-- validate
  for (auto& f : lsFeatures)
  {
    f->validate(planarity_d2p_tol, planarity_n_tol, overlap_tol);
  }
  //-- reenable cout+clog  
  std::clog.rdbuf(clog_buf);
  std::cout.rdbuf(cout_buf);
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
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
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
  //-- disable cout+clog
  std::streambuf* clog_buf = std::clog.rdbuf();
  std::clog.rdbuf(NULL);
  std::streambuf* cout_buf = std::cout.rdbuf();
  std::cout.rdbuf(NULL);
  IOErrors ioerrs;
  ioerrs.set_input_file_type("JSON-FG");
  std::vector<Feature*> lsFeatures;
  parse_jsonfg(j, lsFeatures, tol_snap, ioerrs);
  //-- validate
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- get report in json 
  json jr = get_report_json("JSON object",
                            lsFeatures,
                            VAL3DITY_VERSION,
                            tol_snap,
                            overlap_tol,
                            planarity_d2p_tol,
                            planarity_n_tol,
                            ioerrs);
  //-- reenable cout+clog  
  std::clog.rdbuf(clog_buf);
  std::cout.rdbuf(cout_buf);
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
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
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
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
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
                         json jtransform,
                         double tol_snap, 
                         double planarity_d2p_tol, 
                         double planarity_n_tol, 
                         double overlap_tol)
{
  j["transform"] = jtransform;
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
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
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

// bool 
// is_valid_indoorgml(const char* input, 
//                   double tol_snap, 
//                   double planarity_d2p_tol, 
//                   double planarity_n_tol, 
//                   double overlap_tol)
// {
//   json jr = validate_indoorgml(input, tol_snap, planarity_d2p_tol, planarity_n_tol, overlap_tol);
//   return jr["validity"];
// }

// json
// validate_indoorgml(const char* input, 
//                   double tol_snap, 
//                   double planarity_d2p_tol, 
//                   double planarity_n_tol, 
//                   double overlap_tol) 
// {
//   IOErrors ioerrs;
//   ioerrs.set_input_file_type("IndoorGML");
//   pugi::xml_document doc;
//   pugi::xml_parse_result result = doc.load_string(input);
//   if (!result) {
//     ioerrs.add_error(901, "Input value not valid XML");
//   }
//   std::vector<Feature*> lsFeatures;
//   if (ioerrs.has_errors() == false) {
//     //-- parse namespace
//     pugi::xml_node ncm = doc.first_child();
//     std::map<std::string, std::string> thens = get_namespaces(ncm); //-- results in global variable NS in this unit
//     if ( (thens.count("indoorgml") != 0) && (ncm.name() == (thens["indoorgml"] + "IndoorFeatures")) ) {
//       //-- find (_minx, _miny)
//       compute_min_xy(doc);
//       //-- build dico of xlinks for <gml:Polygon>
//       std::map<std::string, pugi::xpath_node> dallpoly;
//       build_dico_xlinks(doc, dallpoly, ioerrs);
//       ioerrs.set_input_file_type("IndoorGML");
//       process_gml_file_indoorgml(doc, lsFeatures, dallpoly, ioerrs, tol_snap);
//     }
//     else
//     {
//       ioerrs.add_error(904, "GML files not supported (yes that includes CityGML files ==> upgrade to CityJSON)");
//     }
//   }
//   //-- start the validation
//   if (ioerrs.has_errors() == false) {
//     validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
//   }
//   //-- get report in json 
//   json jr = get_report_json("JSON object",
//                             lsFeatures,
//                             VAL3DITY_VERSION,
//                             tol_snap,
//                             overlap_tol,
//                             planarity_d2p_tol,
//                             planarity_n_tol,
//                             ioerrs);
//   return jr;
// }


}