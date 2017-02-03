//
//  CompositeSolid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "CompositeSolid.h"
#include "input.h"
#include "geomtools.h"


CompositeSolid::CompositeSolid(std::string id)
{
  _id = id;
  _is_valid = -1;
}


CompositeSolid::~CompositeSolid()
{}


Primitive3D CompositeSolid::get_type() 
{
  return COMPOSITESOLID;
}


Nef_polyhedron* CompositeSolid::get_nef_polyhedron()
{
  if (_nef != NULL)
    return _nef;
  Nef_polyhedron* unioned = new Nef_polyhedron(Nef_polyhedron::EMPTY);
  for (int i = 0; i < _lsSolids.size(); i++)
  {
    Nef_polyhedron* tmp = _lsSolids[i]->get_nef_polyhedron();
    *unioned = *unioned + *tmp;
    delete tmp;
  }
  _nef = unioned;
  return unioned;
}


void CompositeSolid::get_min_bbox(double& x, double& y)
{
  double tmpx, tmpy;
  double minx = 9e10;
  double miny = 9e10;
  for (auto& s : _lsSolids)
  {
    s->get_min_bbox(tmpx, tmpy);
    if (tmpx < minx)
      minx = tmpx;
    if (tmpy < miny)
      miny = tmpy;
  }
  x = minx;
  y = miny;
}


void CompositeSolid::translate_vertices(double minx, double miny)
{
  for (auto& s : _lsSolids)
    s->translate_vertices(minx, miny);
}


bool CompositeSolid::validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap) 
{
  bool isValid = true;
  for (auto& s : _lsSolids)
  {
    if (s->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isValid = false;
  }
  if (isValid == true) 
  {
    std::vector<Nef_polyhedron*> lsNefs;
    for (int i = 0; i < _lsSolids.size(); i++)
      lsNefs.push_back(_lsSolids[i]->get_nef_polyhedron());
//-- 1. check if any 2 are the same? ERROR:502
    std::clog << "-----Are two solids duplicated" << std::endl;
    for (int i = 0; i < (lsNefs.size() - 1); i++)
    {
      for (int j = i + 1; j < lsNefs.size(); j++) 
      {
        if (*lsNefs[i] == *lsNefs[j])
        {
          std::stringstream msg;
          msg << _lsSolids[i]->get_id() << " & " << _lsSolids[j]->get_id();
          this->add_error(502, msg.str(), "");
          isValid = false;
        }
      }
    }
    if (isValid == true)
    {
//-- 2. check if their interior intersects ERROR:501
      std::clog << "-----Intersections of solids" << std::endl;
      std::vector<Nef_polyhedron*> lsNefsEroded;
      if (tol_overlap > 0.0)
      {
        for (auto each : lsNefs)
          lsNefsEroded.push_back(erode_nef_polyhedron(each, tol_overlap));
      }
      else
      {
        lsNefsEroded = lsNefs;
      }
      Nef_polyhedron emptynef(Nef_polyhedron::EMPTY);
      for (int i = 0; i < (lsNefsEroded.size() - 1); i++)
      {
        Nef_polyhedron* a = lsNefsEroded[i];
        for (int j = i + 1; j < lsNefsEroded.size(); j++) 
        {
          Nef_polyhedron* b = lsNefsEroded[j];
          if (a->interior() * b->interior() != emptynef)
          {
            std::stringstream msg;
            msg << _lsSolids[i]->get_id() << " & " << _lsSolids[j]->get_id();
            this->add_error(501, msg.str(), "");
            isValid = false;
          }
        }
      }
      if (tol_overlap > 0.0)
      {
        for (auto each : lsNefsEroded)
          delete each;
      }
    }
    if (isValid == true)
    {
//-- 3. check if their union yields one solid ERROR:503
      std::clog << "-----Forming one solid (union)" << std::endl;
      std::vector<Nef_polyhedron*> lsNefsDilated;
      if (tol_overlap > 0.0)
      {
        for (auto each : lsNefs)
          lsNefsDilated.push_back(dilate_nef_polyhedron(each, tol_overlap));
      }
      else
      {
        lsNefsDilated = lsNefs;
      }
      Nef_polyhedron unioned(Nef_polyhedron::EMPTY);
      for (auto each : lsNefsDilated)
        unioned = unioned + *each;
      if (unioned.number_of_volumes() != 2)
      {
        std::stringstream msg;
        msg << "-->CompositeSolid is formed of " << (unioned.number_of_volumes() - 1) << " parts";
        this->add_error(503, "", msg.str());
        isValid = false;
      }
      for (auto each : lsNefsDilated)
        delete each;
    } 
    //-- clear the temp Nefs
    if (tol_overlap > 0.0)
    {
      for (auto each: lsNefs)
        delete each;
    }
  }
  _is_valid = isValid;
  return isValid;
}


int CompositeSolid::is_valid()
{
  if ( (_is_valid == 1) && (this->is_empty() == false) && (_errors.empty() == true) )
    return 1;
  else
    return _is_valid;
}



bool CompositeSolid::is_empty() {
  return _lsSolids.empty();
}


std::string CompositeSolid::get_report_xml()
{
  std::stringstream ss;
  ss << "\t<CompositeSolid>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t<id>none</id>" << std::endl;
  ss << "\t\t<numbersolids>" << this->number_of_solids() << "</numbersolids>" << std::endl;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<id>" << std::get<0>(e) << "</id>" << std::endl;
      ss << "\t\t\t<info>" << std::get<1>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  for (auto& s : _lsSolids)
    ss << s->get_report_xml();
  ss << "\t</CompositeSolid>" << std::endl;
  return ss.str();
}


std::set<int> CompositeSolid::get_unique_error_codes() {
  std::set<int> errs = Primitive::get_unique_error_codes();
  for (auto& s : _lsSolids) {
    std::set<int> tmp = s->get_unique_error_codes();
    errs.insert(tmp.begin(), tmp.end());
  }
  return errs;
}


bool CompositeSolid::add_solid(Solid* s) {
  _lsSolids.push_back(s);
  return true;
}

int CompositeSolid::number_of_solids() {
  return _lsSolids.size();
}
