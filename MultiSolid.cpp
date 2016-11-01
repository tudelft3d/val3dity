//
//  MultiSolid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "MultiSolid.h"



MultiSolid::MultiSolid(std::string id) {
  _id = id;
  _is_valid = -1;
}

MultiSolid::~MultiSolid() {
}

std::string MultiSolid::get_type() 
{
  return "MultiSolid";
}

bool MultiSolid::validate(double tol_planarity_d2p, double tol_planarity_normals) 
{
  bool isValid = true;
  for (auto& s : _lsSolids)
  {
    if (s->validate(tol_planarity_d2p, tol_planarity_normals) == false)
      isValid = false;
  }
  _is_valid = isValid;
  return isValid;
}


bool MultiSolid::is_valid() {
  return _is_valid;
}


bool MultiSolid::is_empty() {
  return _lsSolids.empty();
}


std::string MultiSolid::get_report_xml() {
  // TODO: xml report
  return "<EMPTY>";
}

bool MultiSolid::add_solid(Solid* s) {
  _lsSolids.push_back(s);
  return true;
}


int MultiSolid::num_solids() {
  return _lsSolids.size();
}
