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
#include <iostream>
#include <sstream>

Building::Building(std::string id)
{
  _id = id;
  _is_valid = -1;
}


Building::~Building()
{}
  
bool Building::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
  // std::cout << "----- " << this->get_id() << " -----" << std::endl;
  bool isvalid = true;
  int numberprimitives = 0;
  //-- 1. validate each primitive of the Building and the BuildingParts
  for (auto& p : _lsPrimitives)
  {
    numberprimitives++;
    if (p->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
  for (auto& bp : _lsBP)
  {
    numberprimitives++;
    if (bp->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isvalid = false;
  }
//-- 2. make sure solids from the parts don't overlap (their interior)
  if ( (isvalid == true) && (numberprimitives > 1) )
  {
    // std::cout << "----- **********BuildingParts validation (overlap) -----" << std::endl;

    Nef_polyhedron  emptynef(Nef_polyhedron::EMPTY);
    Nef_polyhedron* mynef = new Nef_polyhedron;

    for (auto& p : _lsPrimitives)
    {
      // TODO : CompositeSolid to add here 
      if (p->get_type() == "Solid")
      {
        Solid* tmp = dynamic_cast<Solid*>(p);
        Nef_polyhedron* tmpnef = tmp->get_nef_polyhedron();
        if (mynef->interior() * tmpnef->interior() != emptynef)
        {
          std::cout << "----- " << this->get_id() << " -----" << std::endl;
          std::cout << "INTERSECTION INTERIOR BuildingParts" << std::endl;
          Nef_polyhedron a(mynef->interior() * tmpnef->interior());
          std::cout << a.number_of_volumes() << std::endl;

          Nef_polyhedron* dilated = dilate_nef_polyhedron(tmpnef, 0.1);

          isvalid = false;
        }
        *mynef += *tmpnef;
      }
    }
    for (auto& bp : _lsBP)
    {
      for (auto& p2 : bp->get_primitives())
      {
        if (p2->get_type() == "Solid")
        {
          Solid* tmp = dynamic_cast<Solid*>(p2);
          Nef_polyhedron* p2nef = tmp->get_nef_polyhedron();
          if (mynef->interior() * p2nef->interior() != emptynef)
          {
            std::cout << "----- " << this->get_id() << " -----" << std::endl;
            std::cout << "INTERSECTION INTERIOR BuildingParts" << std::endl;
            Nef_polyhedron a(mynef->interior() * p2nef->interior());
            std::cout << a.number_of_volumes() << std::endl;

            Nef_polyhedron* dilated = erode_nef_polyhedron(p2nef, 0.1);
            // Nef_polyhedron* dilated = dilate_nef_polyhedron(p2nef, 10);
            std::cout << dilated->number_of_volumes() << std::endl;
            if (mynef->interior() * dilated->interior() == emptynef)
              std::cout << "no intersection" << std::endl;
            isvalid = false;
          }
          *mynef += *p2nef;
        }
      }
    }
  }  
  //-- 3. make sure the union of all _Solids forms one Solid
  if ( (isvalid == true) && (numberprimitives > 1) )
  {
    // std::cout << "----- **********BuildingParts validation (union) -----" << std::endl;

    Nef_polyhedron  emtpynef(Nef_polyhedron::EMPTY);
    Nef_polyhedron* mynef = new Nef_polyhedron;
    for (auto& p : _lsPrimitives)
    {
      // TODO : CompositeSolid to add here 
      if (p->get_type() == "Solid")
      {
        Solid* tmp = dynamic_cast<Solid*>(p);
        *mynef += *tmp->get_nef_polyhedron();
      }
    }
    for (auto& bp : _lsBP)
    {
      for (auto& p2 : bp->get_primitives())
      {
        if (p2->get_type() == "Solid")
        {
          Solid* tmp = dynamic_cast<Solid*>(p2);
          *mynef += *tmp->get_nef_polyhedron();
        }
      }
    }
    std::clog << "# of volumes: " << mynef->number_of_volumes() << std::endl;
    if (mynef->number_of_volumes() != 2) 
    {
      std::cout << "----- " << this->get_id() << " -----" << std::endl;
      std::cout << "DISCONNECTED BuildingParts" << std::endl;
      isvalid = false;
    }
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
  for (auto& p : _lsPrimitives)
  {
    ss << p->get_report_xml();
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
  
bool BuildingPart::validate(double tol_planarity_d2p, double tol_planarity_normals)
{
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
  return "<EMPTY>";
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
