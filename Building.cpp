//
//  Building.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 27/10/16.
//
//

#include "Building.h"
#include <iostream>

Building::Building()
{}


Building::~Building()
{}
  
bool Building::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "VALIDATING BUILDING" << std::endl;
  bool isvalid = true;
  for (auto& p : _lsPrimitives)
  {
    if (p->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
  _is_valid = isvalid;
  return isvalid;
}

void Building::add_primitive(Primitive* p)
{
  _lsPrimitives.push_back(p);
}


int Building::get_number_primitives()
{
  return _lsPrimitives.size();
}


std::set<int> Building::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& p : _lsPrimitives)
  {
    std::set<int> tmp = p->get_unique_error_codes();
    errs.insert(tmp.begin(), tmp.end());
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
  return "<EMPTY>";
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

BuildingPart::BuildingPart()
{}


BuildingPart::~BuildingPart()
{}
  
bool BuildingPart::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "VALIDATING BUILDINGPART" << std::endl;
  return true;
}

void BuildingPart::add_primitive(Primitive* p)
{
  _lsPrimitives.push_back(p);
}


bool BuildingPart::is_valid()
{
  return true;
}


bool BuildingPart::is_empty()
{
  return _lsPrimitives.empty();
}


std::string BuildingPart::get_report_xml()
{
  return "<EMPTY>";
}


std::string BuildingPart::get_id()
{
  return _id;
}

void BuildingPart::set_id(std::string id)
{
  _id = id;
}
