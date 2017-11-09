
/*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

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
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#ifndef VAL3DITY_INPUT_DEFINITIONS_H
#define VAL3DITY_INPUT_DEFINITIONS_H

#include "Primitive.h"
#include "Surface.h"
#include "MultiSurface.h"
#include "CompositeSurface.h"
#include "Solid.h"
#include "CompositeSolid.h"
#include "MultiSolid.h"
#include <fstream>
#include <string>
#include "pugixml/pugixml.hpp"
#include "nlohmann-json/json.hpp"

using json = nlohmann::json;


namespace val3dity
{

class IOErrors {
  std::map<int, std::vector<std::string> >  _errors;
public:
  bool          has_errors();
  void          add_error(int code, std::string info);
  std::string   get_report_text();
  std::string   get_report_xml();
  json          get_report_json();
  std::set<int> get_unique_error_codes();
};

  
struct citygml_objects_walker: pugi::xml_tree_walker {
  std::vector<pugi::xml_node> lsNodes;
  virtual bool for_each(pugi::xml_node &node) 
  {
    const char *nodeType = node.name();
    const char *namespaceSeparator = strchr(nodeType, ':');
    if (namespaceSeparator != NULL) {
      nodeType = namespaceSeparator+1;
    }
    if (strcmp(nodeType, "AuxiliaryTrafficArea") == 0 ||
        strcmp(nodeType, "Bridge") == 0 ||
        strcmp(nodeType, "Building") == 0 ||
        // strcmp(nodeType, "BuildingPart") == 0 ||
        strcmp(nodeType, "CityFurniture") == 0 ||
        strcmp(nodeType, "GenericCityObject") == 0 ||
        strcmp(nodeType, "LandUse") == 0 ||
        strcmp(nodeType, "PlantCover") == 0 ||
        strcmp(nodeType, "Railway") == 0 ||
        strcmp(nodeType, "ReliefFeature") == 0 ||
        strcmp(nodeType, "Road") == 0 ||
        strcmp(nodeType, "SolitaryVegetationObject") == 0 ||
        strcmp(nodeType, "TrafficArea") == 0 ||
        strcmp(nodeType, "Tunnel") == 0 ||
        strcmp(nodeType, "WaterBody") == 0) {
      lsNodes.push_back(node);
    } return true;
  }
};


struct primitives_walker: pugi::xml_tree_walker
{
  std::vector<pugi::xml_node> lsNodes;
  int depthprim = 999;
  virtual bool for_each(pugi::xml_node& node)
  { 
    const char *nodeType = node.name();
    const char *namespaceSeparator = strchr(nodeType, ':');
    if (namespaceSeparator != NULL) {
      nodeType = namespaceSeparator+1;
    }
    if (depth() == depthprim)
    {
      // std::cout << "back to reading mode" << node.name() << std::endl;
      depthprim = 999;
    }
    if ((strcmp(nodeType, "boundedBy") == 0))
      depthprim = depth();
    if ( (depth() < depthprim) && 
         ( (strcmp(nodeType, "Solid") == 0) ||
           (strcmp(nodeType, "MultiSolid") == 0) ||
           (strcmp(nodeType, "CompositeSolid") == 0) ||
           (strcmp(nodeType, "MultiSurface") == 0) ||
           (strcmp(nodeType, "boundedBy") == 0) ||
           (strcmp(nodeType, "CompositeSurface") == 0) ) )
    {
      // std::cout << "----" << node.name() << std::endl;
      // std::cout << "depth " << depth() << std::endl;
      depthprim = depth();
      lsNodes.push_back(node);
    }
    return true; 
  }
};

struct semantic_surfaces_walker: pugi::xml_tree_walker {
  std::vector<pugi::xml_node> lsNodes;
  virtual bool for_each(pugi::xml_node &node) 
  {
    const char *nodeType = node.name();
    const char *namespaceSeparator = strchr(nodeType, ':');
    if (namespaceSeparator != NULL) {
      nodeType = namespaceSeparator+1;
    }
    if (strcmp(nodeType, "MultiSurface") == 0) {
      lsNodes.push_back(node);
    } return true;
  }
};

//--

void              read_file_gml(std::string &ifile, std::map<std::string, std::vector<Primitive*> >& dPrimitives, IOErrors& errs, double tol_snap, bool geom_is_sem_surfaces);
void              get_namespaces(pugi::xml_node& root, std::string& vcitygml);

void              read_file_cityjson(std::string &ifile, std::map<std::string, std::vector<Primitive*> >& dPrimitives, IOErrors& errs, double tol_snap);

void              print_information(std::string &ifile);
void              report_primitives(pugi::xml_document& doc, std::map<std::string, std::string>& ns);
void              report_building(pugi::xml_document& doc, std::map<std::string, std::string>& ns);
void              report_building_each_lod(pugi::xml_document& doc, std::map<std::string, std::string>& ns, int lod, int& total_solid, int& total_ms, int& total_sem);
void              get_namespaces(pugi::xml_node& root, std::map<std::string, std::string>& ns, std::string& vcitygml);
void              print_info_aligned(std::string o, size_t number, bool tab = false);

std::string       errorcode2description(int code);
void              read_file_obj(std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::string &ifile, Primitive3D prim3d, IOErrors& errs, double tol_snap);
Surface*          read_file_poly(std::string &ifile, int shellid, IOErrors& errs);
Surface*          read_file_off(std::string &ifile, int shellid, IOErrors& errs);

std::vector<int>  process_gml_ring(const pugi::xml_node& n, Surface* sh, IOErrors& errs);
Surface*          process_gml_surface(const pugi::xml_node& n, int id, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
MultiSurface*     process_gml_multisurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
CompositeSurface* process_gml_compositesurface(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
Solid*            process_gml_solid(const pugi::xml_node& nsolid, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
MultiSolid*       process_gml_multisolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);
CompositeSolid*   process_gml_compositesolid(const pugi::xml_node& nms, std::map<std::string, pugi::xpath_node>& dallpoly, double tol_snap, IOErrors& errs);

void              process_json_surface(std::vector< std::vector<int> >& pgn, nlohmann::json& j, Surface* s);
void              build_dico_xlinks(pugi::xml_document& doc, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs);
void              process_gml_file_city_objects(pugi::xml_document& doc, std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs, double tol_snap, bool geom_is_sem_surfaces);
void              process_gml_file_primitives(pugi::xml_document& doc, std::map<std::string, std::vector<Primitive*> >& dPrimitives, std::map<std::string, pugi::xpath_node>& dallpoly, IOErrors& errs, double tol_snap);

void              printProgressBar(int percent);
std::string       localise(std::string s);
std::string       remove_xml_namespace(const char* input);

void              compute_min_xy(pugi::xml_document& doc);
void              compute_min_xy(json& j);

} // namespace val3dity

#endif
