//
//  Building.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 27/10/16.
//
//

#include "Building.h"

Building::Building();
{}


Building::~Building()
{}
  
bool Building::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "VALIDATING BUILDING" << std::endl;
  return true;
}

void Building::add_primitive(Primitive* p)
{
  _lsPrimitives.push_back();
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
  return true;
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

BuildingPart::BuildingPart();
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
  _lsPrimitives.push_back();
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
