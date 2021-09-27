/*
  val3dity 

  Copyright (c) 2011-2021, 3D geoinformation research group, TU Delft

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



namespace val3dity
{

std::string VAL3DITY_VERSION = "2.3.0-beta.1";

void validate_no_coutclog(std::vector<Feature*>& lsFeatures,                        
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


bool is_valid_onegeom(json& j,
                       double tol_snap, 
                       double planarity_d2p_tol, 
                       double planarity_n_tol, 
                       double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson_geom(j, lsFeatures, tol_snap);
  //-- validate
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- compile errors
  bool isvalid;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      isvalid = p->is_valid();
  return isvalid;
}

json validate_onegeom(json& j,
                      double tol_snap, 
                      double planarity_d2p_tol, 
                      double planarity_n_tol, 
                      double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson_geom(j, lsFeatures, tol_snap);
  //-- validate
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- compile errors
  bool isvalid;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      isvalid = p->is_valid();
  //-- get report in json 
  json jr;
  IOErrors ioerrs;
  ioerrs.set_input_file_type("tu3djson_geom");
  get_report_json(jreport, 
                  "JSON object",
                  lsFeatures,
                  VAL3DITY_VERSION,
                  tol_snap,
                  overlap_tol,
                  planarity_d2p_tol,
                  planarity_n_tol,
                  ioerrs);
  return isvalid;
}

std::vector<bool> is_valid_tu3djson(json& j,
                                    double tol_snap, 
                                    double planarity_d2p_tol, 
                                    double planarity_n_tol, 
                                    double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson(j, lsFeatures, tol_snap);
  //-- validate
  validate_no_coutclog(lsFeatures, planarity_d2p_tol, planarity_n_tol, overlap_tol);
  //-- compile errors
  std::vector<bool> re;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      re.push_back(p->is_valid());
  return re;
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
  //-- compile errors
  std::vector<bool> re;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      re.push_back(p->is_valid());
  //-- get report in json 
  IOErrors ioerrs;
  ioerrs.set_input_file_type("tu3djson");
  get_report_json(jreport, 
                  "JSON object",
                  lsFeatures,
                  VAL3DITY_VERSION,
                  tol_snap,
                  overlap_tol,
                  planarity_d2p_tol,
                  planarity_n_tol,
                  ioerrs);
}


bool is_valid_cityjson(json& j, 
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
  if (errors.size() == 0) {
    return true;
  }
  else {
    return false;
  }
}

json validate_cityjson(json& j,
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
  json jr;
  IOErrors ioerrs;
  ioerrs.set_input_file_type("CityJSON");
  get_report_json(jreport, 
                  "JSON object",
                  lsFeatures,
                  VAL3DITY_VERSION,
                  tol_snap,
                  overlap_tol,
                  planarity_d2p_tol,
                  planarity_n_tol,
                  ioerrs);
  if (errors.size() == 0) {
    return true;
  }
  else {
    return false;
  }
}


}