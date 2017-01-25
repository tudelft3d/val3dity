//
//  Building.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 27/10/16.
//
//

#include "Building.h"
#include "Solid.h"
#include "definitions.h"
#include "geomtools.h"
#include "input.h"
#include <iostream>
#include <sstream>

Building::Building(std::string id)
{
  _id = id;
  _is_valid = -1;
}


Building::~Building()
{}
  
bool Building::validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap)
{
  bool isvalid = true;
  int numberprimitives = 0;
//-- 1. validate each primitive of the Building 
  for (auto& p : _lsPrimitives)
  {
    numberprimitives++;
    if (p->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
//-- 2. validate each primitive of the BuildingParts
  for (auto& bp : _lsBP)
  {
    numberprimitives++;
    if (bp->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
//-- 3. collect all primitives for the Building and BPs and "Nef" them
//-- erode if necessary
  if ( (isvalid == true) && (_lsBP.size() > 0) )
  {
    Nef_polyhedron* nefB = NULL;
    std::vector<Nef_polyhedron*> nefsBP;
    std::clog << "- Interactions between the BuildingParts -" << std::endl;
    if (_lsPrimitives.empty() == false)
    { 
      Primitive* p = _lsPrimitives[0];
      Nef_polyhedron* tmpnef;
      if (p->get_type() == "Solid")
        tmpnef = dynamic_cast<Solid*>(p)->get_nef_polyhedron();
      else if (p->get_type() == "CompositeSolid")
        tmpnef = dynamic_cast<CompositeSolid*>(p)->get_nef_polyhedron();
      if (nefB != NULL)
      {
        if (tol_overlap > 0)
        {
          nefB = erode_nef_polyhedron(tmpnef, tol_overlap);
          delete tmpnef;
        }
        else
        {
          nefB = tmpnef;
        }
      }
    }
    for (auto& bp : _lsBP)
    {
      for (auto& p : bp->get_primitives())
      {
        Nef_polyhedron* tmpnef;
        if (p->get_type() == "Solid")
          tmpnef = dynamic_cast<Solid*>(p)->get_nef_polyhedron();
        else if (p->get_type() == "CompositeSolid")
          tmpnef = dynamic_cast<CompositeSolid*>(p)->get_nef_polyhedron();
        else
          continue;
        if (tol_overlap > 0)
        {
          nefsBP.push_back(erode_nef_polyhedron(tmpnef, tol_overlap));
          delete tmpnef;
        }
        else
        {
          nefsBP.push_back(tmpnef);
        }
      }
    }  
//-- 4. make sure B & BPs do not overlap with each other (their interior that is)
    Nef_polyhedron emptynef(Nef_polyhedron::EMPTY);
    //-- verify intersection B-primitive (if any!) with each BP
    if (nefB != NULL)
    {
      for (int i = 0; i < nefsBP.size(); i++)
      {
        if (nefB->interior() * nefsBP[i]->interior() != emptynef)
        {
          std::stringstream msg;
          msg << "Building main part" << " & BuildingPart #" << _lsBP[i]->get_id();
          this->add_error(601, msg.str(), "");
          isvalid = false;
        }
      }
    }
    for (int i = 0; i < (nefsBP.size() - 1); i++)
    {
      Nef_polyhedron* a = nefsBP[i];
      for (int j = i + 1; j < nefsBP.size(); j++) 
      {
        Nef_polyhedron* b = nefsBP[j];
        if (a->interior() * b->interior() != emptynef)
        {
          std::stringstream msg;
          msg << "BuildingParts #" << _lsBP[i]->get_id() << " & #" << _lsBP[j]->get_id();
          this->add_error(601, msg.str(), "");
          isvalid = false;
        }
      }
    }
  }
  _is_valid = isvalid;
  return isvalid;
}


void Building::add_error(int code, std::string whichgeoms, std::string info)
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

void Building::add_primitive(Primitive* p)
{
  _lsPrimitives.push_back(p);
}


int Building::get_number_primitives()
{
  return _lsPrimitives.size();
}

int Building::get_number_solids()
{
  int t = 0;
  for (auto& p : _lsPrimitives)
    if (p->get_type() == "Solid")
      t++;
  return t;
}

int Building::get_number_compositesolids()
{
  int t = 0;
  for (auto& p : _lsPrimitives)
    if (p->get_type() == "CompositeSolid")
      t++;
  return t;
}

int Building::get_number_multisurfaces()
{
  int t = 0;
  for (auto& p : _lsPrimitives)
    if (p->get_type() == "MultiSurface")
      t++;
  return t;
}


std::set<int> Building::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
  {
    errs.insert(std::get<0>(err));
  }
  for (auto& p : _lsPrimitives)
  {
    std::set<int> tmp = p->get_unique_error_codes();
    errs.insert(tmp.begin(), tmp.end());
  }
  for (auto& bp : _lsBP)
  {
    for (auto& p : bp->get_primitives())
    {
      std::set<int> tmp = p->get_unique_error_codes();
      errs.insert(tmp.begin(), tmp.end());
    }
  }
  return errs;
}

void Building::add_buildingpart(BuildingPart* bp)
{
  _lsBP.push_back(bp);
}


bool Building::has_parts()
{
  return !(_lsBP.empty());
}

int Building::get_number_buildingparts()
{
  return _lsBP.size();
}

bool Building::is_valid()
{
  return _is_valid;
}


bool Building::is_empty()
{
  return _lsPrimitives.empty();
}


std::string Building::get_report_xml()
{
  std::stringstream ss;
  ss << "\t<Building>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t<id>none</id>" << std::endl;
  ss << "\t\t<numberprimitives>" << this->get_number_primitives() << "</numberprimitives>" << std::endl;
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
  for (auto& p : _lsPrimitives)
  {
    ss << p->get_report_xml();
  }
  for (auto& bp : _lsBP)
  {
    ss << bp->get_report_xml();  
  }
  ss << "\t</Building>" << std::endl;
  return ss.str();
}


std::string Building::get_id()
{
  return _id;
}

void Building::set_id(std::string id)
{
  _id = id;
}


//----------------------------------------------------------------
//----------------------------------------------------------------

BuildingPart::BuildingPart(std::string id)
{
  _id = id;
  _is_valid = -1;
}


BuildingPart::~BuildingPart()
{}
  
bool BuildingPart::validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap)
{
  std::clog << "- BuildingPart validation (#" << _id << ") -" << std::endl;
  bool isvalid = true;
  for (auto& p : _lsPrimitives)
  {
    if (p->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
  _is_valid = isvalid;
  return isvalid;
  
  
}

void BuildingPart::add_primitive(Primitive* p)
{
  _lsPrimitives.push_back(p);
}


bool BuildingPart::is_valid()
{
  return _is_valid;
}


bool BuildingPart::is_empty()
{
  return _lsPrimitives.empty();
}


std::string BuildingPart::get_report_xml()
{
  std::stringstream ss;
  ss << "\t\t<BuildingPart>" << std::endl;
  if (this->get_id() != "")
    ss << "\t\t\t<id>" << this->_id << "</id>" << std::endl;
  else
    ss << "\t\t\t<id>none</id>" << std::endl;
  for (auto& p : _lsPrimitives)
  {
    ss << p->get_report_xml();
  }
  ss << "\t\t</BuildingPart>" << std::endl;
  return ss.str();
}


std::vector<Primitive*>& BuildingPart::get_primitives()
{
  return _lsPrimitives;
}

std::string BuildingPart::get_id()
{
  return _id;
}

void BuildingPart::set_id(std::string id)
{
  _id = id;
}
