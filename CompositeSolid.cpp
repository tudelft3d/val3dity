//
//  CompositeSolid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "Solid.h"
#include "CompositeSolid.h"




CompositeSolid::CompositeSolid(std::string id)
{
  _id = id;
  _is_valid = -1;
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
  }
  _is_valid = isValid;
  return isValid;
}


bool CompositeSolid::is_valid() {
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
