//
//  MultiSurface.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "MultiSurface.h"


MultiSurface::MultiSurface(std::string id) {
  _id = id;
  _is_valid = -1;
}


bool MultiSurface::validate(double tol_planarity_d2p, double tol_planarity_normals) 
{
  return _surface->validate_as_multisurface(tol_planarity_d2p, tol_planarity_normals);
}


bool MultiSurface::is_valid() {
  return _is_valid;
}

std::string MultiSurface::get_id() {
  return _id;
}

bool MultiSurface::is_empty() {
  return _surface->is_empty();
}


std::string MultiSurface::get_report_xml() {
  // TODO: xml report
  return "<EMPTY>";
}


int MultiSurface::number_surfaces() 
{
  return _surface->number_faces();
}


bool MultiSurface::set_surface(Surface* s) 
{
  _surface = s;
  return true;
}


Surface* MultiSurface::get_surface() 
{
  return _surface;
}

