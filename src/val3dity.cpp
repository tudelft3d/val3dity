#include "val3dity.h"
#include "Feature.h"
#include "CityObject.h"
#include "input.h"

#include <iostream>



namespace val3dity
{


std::vector<bool> validate_tu3djson(json& j,
                                    double tol_snap, 
                                    double planarity_d2p_tol, 
                                    double planarity_n_tol, 
                                    double overlap_tol)
{
  std::vector<Feature*> lsFeatures;
  parse_tu3djson(j, lsFeatures, tol_snap);
  //-- validate
  for (auto& f : lsFeatures)
  {
    f->validate(0.001, 30, 0.0);
  }
  //-- compile errors
  std::vector<bool> re;
  for (auto& f : lsFeatures)
    for (auto& p : f->get_primitives())
      re.push_back(p->is_valid());
  return re;

}

bool validate_cityjson(json& j, 
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
  {
    f->validate(0.001, 30, 0.0);
  }
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


}