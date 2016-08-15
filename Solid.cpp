/*
 val3dity - Copyright (c) 2011-2016, Hugo Ledoux.  All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the authors nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*/

#include "input.h"
#include "Solid.h"
#include "Shell.h"
#include "validate_shell.h"
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#include <CGAL/Polyhedron_copy_3.h>

//-- Nef requires EPEC (exact-predicates & exact-construction) and thus diff kernels
 //-- Polyhedron are converted when they are valid
typedef CGAL::Exact_predicates_exact_constructions_kernel   KE;
typedef CGAL::Polyhedron_3<KE>                              CgalPolyhedronE;
typedef CGAL::Nef_polyhedron_3<KE>                          Nef_polyhedron;

typedef CGAL::Polyhedron_copy_3<CgalPolyhedron, CgalPolyhedronE::HalfedgeDS> Polyhedron_convert; 

//-- to keep track of all gml:Solids in a GML file
int Solid::_counter = 0;

Solid::Solid()
{
  _id = std::to_string(_counter);
  _counter++;
  _is_valid = -1;
}


Solid::Solid(Shell* sh)
{
  _shells.push_back(sh);
  _id = std::to_string(_counter);
  _counter++;
}

Solid::~Solid()
{
  // std::clog << "DESTRUCTOR SOLIDS" << std::endl;
  // for (auto& sh : _shells)
  // {
    // delete sh;
  // }
}

Shell* Solid::get_oshell()
{
  return _shells[0];
}


void Solid::set_oshell(Shell* sh)
{
  if (_shells.empty())
    _shells.push_back(sh);
  else
    _shells[0] = sh;
}


const vector<Shell*>& Solid::get_shells()
{
  return _shells;
}


void Solid::add_ishell(Shell* sh)
{
  _shells.push_back(sh);
}


bool Solid::is_valid()
{
  if ( (_is_valid > 0) && (this->is_empty() == false) )
    return true;
  else
    return false;
}


bool Solid::is_empty()
{
  for (auto& sh : _shells)
  {
    if (sh->is_empty() == true)
      return true;
  }
  return false;
}

std::string Solid::get_id_building()
{
  return _id_building;
}

void Solid::set_id_building(std::string id)
{
  _id_building = id;
}

std::string Solid::get_id_buildingpart()
{
  return _id_buildingpart;
}

void Solid::set_id_buildingpart(std::string id)
{
  _id_buildingpart = id;
}


void Solid::translate_vertices()
{
  double minx = 9e10;
  double miny = 9e10;
  for (auto& sh : _shells)
  {
    double tx, ty;
    sh->get_min_bbox(tx, ty);
    if (tx < minx)
      minx = tx;
    if (ty < miny)
      miny = ty;
  }
  for (auto& sh : _shells)
    sh->translate_vertices(minx, miny);
}


bool Solid::validate(Primitive3D prim, double tol_planarity_d2p, double tol_planarity_normals)
{
  bool isValid = true;
  if (this->is_empty() == true)
  {
    this->add_error(902, -1, -1, "probably error while parsing the input");
    return false;
  }
  for (auto& sh : _shells)
  {
    if (sh->validate(prim, tol_planarity_d2p, tol_planarity_normals) == false) 
      isValid = false;
  }
  if ( (isValid == true) && (prim == SOLID) )
  {
    if (validate_solid_with_nef() == false)
      isValid = false;
  }
  _is_valid = isValid;
  return isValid;
}


std::set<int> Solid::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& sh : _shells)
  {
    std::set<int> errsh = sh->get_unique_error_codes();
    errs.insert(errsh.begin(), errsh.end());
  }
  for (auto& e : _errors)
  {
    errs.insert(std::get<0>(e));
  }
  return errs;
}

std::string Solid::get_poly_representation()
{
  std::ostringstream s;
  for (auto& sh : _shells)
  {
    s << sh->get_poly_representation() << std::endl;
  }
  return s.str();
}

std::string Solid::get_report_xml()
{
  std::stringstream ss;
  ss << "\t<Primitive>" << std::endl;
  ss << "\t\t<id>" << this->_id << "</id>" << std::endl;
  ss << "\t\t<numbershells>" << (this->num_ishells() + 1) << "</numbershells>" << std::endl;
  ss << "\t\t<numberfaces>" << this->num_faces() << "</numberfaces>" << std::endl;
  ss << "\t\t<numbervertices>" << this->num_vertices() << "</numbervertices>" << std::endl;
  if (_id_building.empty() == false)
  {
    ss << "\t\t<Building>" << this->get_id_building() << "</Building>" << std::endl;
  }
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      if (std::get<0>(e) == -1)
        ss << "\t\t\t<shell>-1</shell>" << std::endl;
      else if (std::get<1>(e) == -1)
        ss << "\t\t\t<shell>" << std::get<0>(e) << "</shell>" << std::endl;
      else
        ss << "\t\t\t<shell>" << std::get<0>(e) << "--" << std::get<1>(e) << "</shell>" << std::endl;
      ss << "\t\t\t<info>" << std::get<2>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  for (auto& sh : _shells)
  {
    ss << sh->get_report_xml();
  }
  ss << "\t</Primitive>" << std::endl;
  return ss.str();
}

std::string Solid::get_report_text()
{
  std::stringstream ss;
  ss << "===== Primitive " << this->_id << " =====" << std::endl;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t" << std::get<0>(err) << " -- " << errorcode2description(std::get<0>(err)) << std::endl;
      if (std::get<0>(e) == -1)
        ss << "\t\tShells: -1" << std::endl;
      else if (std::get<1>(e) == -1)
        ss << "\t\tShells: " << std::get<0>(e) << std::endl;
      else
        ss << "\t\tShells: " << std::get<0>(e) << "--" << std::get<1>(e) << std::endl;
      ss << "\t\tInfo: "  << std::get<2>(e) << std::endl;
    }
  }
  for (auto& sh : _shells)
  {
    ss << sh->get_report_text();
  }
  if (this->is_valid() == true)
    ss << "\tVALID" << std::endl;
  return ss.str();
}


int Solid::num_ishells()
{
  return (_shells.size() - 1);
}

int Solid::num_faces()
{
  int total = 0;
  for (auto& sh : _shells)
    total += sh->number_faces();
  return total;
}

int Solid::num_vertices()
{
  int total = 0;
  for (auto& sh : _shells)
    total += sh->number_vertices();
  return total;
}

std::string Solid::get_id()
{
  return _id;
}


void Solid::set_id(std::string id)
{
  _id = id;
}


void Solid::add_error(int code, int shell1, int shell2, std::string info)
{
  std::tuple<int, int, std::string> a(shell1, shell2, info);
  _errors[code].push_back(a);
  std::clog << "\tERROR " << code << ": " << errorcode2description(code);
  if (shell2 == -1)
    std::clog << " (shell: #" << shell1 << ")" << std::endl;
  else
    std::clog << " (shells: #" << shell1 << " & #" << shell2 << ")" << std::endl;
  if (info.empty() == false)
    std::clog << "\t[" << info << "]" << std::endl;
}


bool Solid::validate_solid_with_nef()
{
  bool isValid = true;
  std::clog << "----- Solid validation -----" << std::endl;
  //-- check orientation of the normals is outwards or inwards
  std::clog << "--Global orientation of normals" << std::endl;
  int i = 0;
  for (auto& sh : this->get_shells())
  {
    if (check_global_orientation_normals(sh->get_cgal_polyhedron(), i == 0) == false) 
    {
      this->add_error(405, i, -1, "");
      isValid = false;
    }
    i++;
  }
  if (isValid == false)
    return false;

  if (this->num_ishells() == 0)
    return true;
    
  std::clog << "--Inspection interactions between the " << (this->num_ishells() + 1) << " shells" << std::endl;
  vector<Nef_polyhedron> nefs;
  for (auto& sh : this->get_shells())
  {
    //-- convert to an EPEC Polyhedron so that convertion to Nef is possible
    CgalPolyhedronE pe;
    Polyhedron_convert polyhedron_converter(*(sh->get_cgal_polyhedron()));
    pe.delegate(polyhedron_converter);
    Nef_polyhedron onef(pe);
    nefs.push_back(onef);
  }

  //-- test axiom #1 from the paper, Sect 4.5:
  //-- https://3d.bk.tudelft.nl/hledoux/pdfs/13_cacaie.pdf
  Nef_polyhedron nef;
  for (int i = 1; i < nefs.size(); i++) 
  {
    nef = !nefs[0] * nefs[i];
    if (nef.is_empty() == false)
    {
      nef = nefs[0] * nefs[i];
      if (nef.is_empty() == true)
      {
        std::stringstream msg;
        msg << "Inner shell (#" << i << ") is completely outside the outer shell (#0))";
        this->add_error(403, i, -1, msg.str());
        isValid = false;
      }
      else
      {
        this->add_error(401, 0, i, "");
        isValid = false; 
      }
    }
    else
    {
      nef = nefs[0] - nefs[i];
      if (nef.number_of_volumes() < 3)
      {
        this->add_error(401, 0, i, "");
        isValid = false; 
      }
    }
  }

  //-- test axiom #2 from the paper 
  nef.clear();
  for (int i = 1; i < nefs.size(); i++) 
  {
    for (int j = (i + 1); j < nefs.size(); j++) 
    {
      //-- 1. are they the same?
      if (nefs[i] == nefs[j])
      {
        this->add_error(402, i, j, "");
        isValid = false;
        continue;
      }
      //-- 2. intersection
      nef = nefs[i] * nefs[j];
      if (nef.number_of_volumes() > 1)
      {
        this->add_error(401, i, j, "");
        isValid = false;
        continue;
      }
      //-- 3. union
      nef = nefs[i] + nefs[j];
      if (nef.number_of_volumes() < 3)
      {
        this->add_error(401, i, j, "");
        isValid = false;
        continue;
      }
    }
  }
  //-- test axiom #3 from the paper
  if (isValid == true)
  {
    nef.clear();
    nef += nefs[0];
    int numvol = 2;
    for (int i = 1; i < nefs.size(); i++) 
    {
      nef = nef - nefs[i];
      numvol++;
      if (nef.number_of_volumes() != numvol)
      {
        this->add_error(404, -1, -1, "");
        isValid = false;
        break;
      }
    }
  }
  return isValid;
}