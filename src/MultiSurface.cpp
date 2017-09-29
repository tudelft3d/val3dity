//
//  MultiSurface.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "MultiSurface.h"
#include "Primitive.h"
#include "input.h"

namespace val3dity
{

MultiSurface::MultiSurface(std::string id) {
  _id = id;
  _is_valid = -1;
}

MultiSurface::~MultiSurface() {
}

bool MultiSurface::validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap)
{
  if (this->is_valid() == 0)
    return false;
  if (_surface->validate_as_multisurface(tol_planarity_d2p, tol_planarity_normals) == true) 
  {
    _is_valid = 1;
    return true;
  }
  else
  {
    _is_valid = 0;
    return false;
  }
}


Primitive3D MultiSurface::get_type() 
{
  return MULTISURFACE;
}

int MultiSurface::is_valid() {
  if (_surface->has_errors() == true)
  {
    _is_valid = 0;
    return 0;
  }
  if ( (_is_valid == 1) && (this->is_empty() == false) )
    return 1;
  else
    return _is_valid;
}


void MultiSurface::get_min_bbox(double& x, double& y)
{
  _surface->get_min_bbox(x, y);
}


void MultiSurface::translate_vertices(double minx, double miny)
{
    _surface->translate_vertices(minx, miny);
}

bool MultiSurface::is_empty() {
  return _surface->is_empty();
}


json MultiSurface::get_report_json()
{
  json j;
  bool isValid = true;
  j["type"] = "MultiSurface";
  if (this->get_id() != "")
    j["id"] = this->_id;
  else
    j["id"] = "none";
  j["numbersurfaces"] = this->number_faces();
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      json jj;
      jj["type"] = "Error";
      jj["code"] = std::get<0>(err);
      jj["description"] = errorcode2description(std::get<0>(err));
      jj["id"] = std::get<0>(e);
      jj["info"] = std::get<1>(e);
      j["errors"].push_back(jj);
      isValid = false;
    }
  }
  for (auto& each: _surface->get_report_json())
    j["errors"].push_back(each); 
  if (_surface->has_errors() == true)
    isValid = false;
  j["validity"] = isValid;  
  return j;
}


std::string MultiSurface::get_report_xml() {
  std::stringstream ss;
  ss << "\t<MultiSurface>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t<id>none</id>" << std::endl;
  ss << "\t\t<numbersurfaces>" << this->number_faces() << "</numbersurfaces>" << std::endl;
  // ss << "\t\t<numbervertices>" << this->num_vertices() << "</numbervertices>" << std::endl;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<faces>" << std::get<0>(e) << "</faces>" << std::endl;
      ss << "\t\t\t<info>" << std::get<1>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  ss << _surface->get_report_xml();
  ss << "\t</MultiSurface>" << std::endl;
  return ss.str();}


int MultiSurface::number_faces() 
{
  return _surface->number_faces();
}


bool MultiSurface::set_surface(Surface* s) 
{
  _surface = s;
  return true;
}

std::set<int> MultiSurface::get_unique_error_codes() {
  std::set<int> errs = Primitive::get_unique_error_codes();
  std::set<int> tmp = _surface->get_unique_error_codes();
  errs.insert(tmp.begin(), tmp.end());
  return errs;
}


Surface* MultiSurface::get_surface() 
{
  return _surface;
}

} // namespace val3dity
