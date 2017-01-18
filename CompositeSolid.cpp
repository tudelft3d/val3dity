//
//  CompositeSolid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "CompositeSolid.h"


CompositeSolid::CompositeSolid(std::string id)
{
  _id = id;
  _is_valid = -1;
}


CompositeSolid::~CompositeSolid()
{}


std::string CompositeSolid::get_type() 
{
  return "CompositeSolid";
}

bool CompositeSolid::validate(double tol_planarity_d2p, double tol_planarity_normals) 
{
  bool isValid = true;
  for (auto& s : _lsSolids)
  {
    if (s->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isValid = false;
  }
  if (isValid == true) 
  {
    // TODO: implement interactions between solids for CompositeSolid
    std::clog << "INTERACTIONS BETWEEN SOLIDS FOR COMPOSITESOLID" << std::endl;
    //-- 1. store all Solids in Nef
    std::vector<Nef_polyhedron*> lsNefs;
    for (int i = 0; i < _lsSolids.size(); i++)
      lsNefs.push_back(_lsSolids[i]->get_nef_polyhedron());
    //-- 2. check if their interior intersects
    Nef_polyhedron emptynef(Nef_polyhedron::EMPTY);
    for (int i = 0; i < (lsNefs.size() - 1); i++)
    {
      Nef_polyhedron* a = lsNefs[i];
      for (int j = i + 1; j < lsNefs.size(); j++) 
      {
        Nef_polyhedron* b = lsNefs[j];
        if (a->interior() * b->interior() != emptynef)
        {
          std::cout << "!!!OVERLAP!!!" << std::endl;
          std::stringstream msg;
          msg << "Solid " << _lsSolids[i]->get_id() << "& Solid " << _lsSolids[j]->get_id();
          this->add_error(501, msg.str(), "");
          isValid = false;
        }
      }
    }
    if (isValid == true)
    {
      //-- 3. check if their union yields one solid
      std::cout << "TEST UNION OF ALL THE SOLIDS IN THE COMPOSITESOLID" << std::endl;
      Nef_polyhedron unioned(Nef_polyhedron::EMPTY);
      for (auto each : lsNefs)
        unioned = unioned + *each;
      std::cout << "# of solids in union: " << unioned.number_of_volumes() << std::endl;
    } 
    for (auto each: lsNefs)
      delete each;
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


std::string CompositeSolid::get_report_xml() {
  // TODO: xml report
  return "<EMPTY>";
}

bool CompositeSolid::add_solid(Solid* s) {
  _lsSolids.push_back(s);
  return true;
}

int CompositeSolid::num_solids() {
  return _lsSolids.size();
}
