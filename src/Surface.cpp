/*
 val3dity - Copyright (c) 2011-2017, Hugo Ledoux.  All rights reserved.
 
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

#include "Surface.h"

#include "geomtools.h"
#include "input.h"
#include "validate_shell.h"
#include <CGAL/Polygon_mesh_processing/self_intersections.h>
#include <geos_c.h>
#include <sstream>

using namespace std;



namespace val3dity
{

double Surface::_shiftx = 0.0;
double Surface::_shifty = 0.0;

Surface::Surface(int id, double tol_snap)
{
  _id = id;
  _is_valid_2d = -1;
  _vertices_added = 0;
  if (tol_snap < 1e-8)
    _tol_snap = -1;
  else
    _tol_snap = tol_snap;
}

Surface::~Surface()
{
  // TODO: clear memory properly
  _lsPts.clear();
}

int Surface::get_id()
{
  return _id;
}

CgalPolyhedron* Surface::get_cgal_polyhedron()
{
  return _polyhedron;
}

bool Surface::has_errors()
{
return !(_errors.empty());
}

bool Surface::is_empty()
{
  return (_lsPts.empty() || _lsFaces.empty());
}


void Surface::add_error(int code, std::string faceid, std::string info)
{
  std::tuple<std::string, std::string> a(faceid, info);
  _errors[code].push_back(a);
  std::clog << "\tERROR " << code << ": " << errorcode2description(code);
  if (faceid.empty() == false)
    std::clog << " (face " << faceid << ")";
  std::clog << std::endl;
  if (info.empty() == false)
    std::clog << "\t[" << info << "]" << std::endl;
}

std::set<int> Surface::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
  {
    errs.insert(std::get<0>(err));
  }
  return errs;
}


json Surface::get_report_json()
{
  json j;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])    
    {
      json jj;
      jj["type"] = "Error";
      jj["code"] = std::get<0>(err);
      jj["description"] = errorcode2description(std::get<0>(err));
      jj["id"] = std::get<0>(e);
      jj["info"] = std::get<1>(e);
      j.push_back(jj);
    }
  }
  return j;
}


std::string Surface::get_report_xml()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      // ss << "\t\t\t<shell_number>" << this->_id << "</shell_number>" << std::endl;
      ss << "\t\t\t<surface_id>" << std::get<0>(e) << "</surface_id>" << std::endl;
      ss << "\t\t\t<info>" << std::get<1>(e) << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  return ss.str();
}


std::string Surface::get_report_text()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t" << std::get<0>(err) << " -- " << errorcode2description(std::get<0>(err)) << std::endl;
      ss << "\t\tSurface: " << this->_id << std::endl;
      ss << "\t\tFace: "  << std::get<0>(e) << std::endl;
      ss << "\t\tInfo: "  << std::get<1>(e) << std::endl;
    }
  }
  return ss.str();
}


std::string Surface::get_poly_representation()
{
  std::ostringstream s;
  //-- points
  s << _lsPts.size() << " 3 0 0" << std::endl;
  int i = 0;
  for (auto& p : _lsPts)
  {
    s << i << " " << setprecision(15) << p.x() << " " << p.y() << " " << p.z() << std::endl;
    i++;
  }
  //-- faces
  s << _lsFaces.size() << " 0" << std::endl;
  for (auto& f : _lsFaces)
  {
    s << f.size() << " " << (f.size() - 1) << std::endl;
    for (auto& r : f)
    {
      s << r.size() << " ";
      for (auto p : r)
      {
        s << p << " ";
      }
      s << std::endl;
    }
  }
  s << "0" << std::endl;
  s << "0" << std::endl;
  return s.str();
}

std::string Surface::get_off_representation()
{
  std::stringstream ss;
  ss << "OFF" << std::endl;
  int notr = 0;
  for (auto& f: _lsTr) 
    for (auto& t: f) 
      notr++;
  ss << _lsPts.size() << " " << notr << " 0" << std::endl;
  //-- points
  for (auto& p : _lsPts)
    ss << setprecision(15) << p.x() << " " << p.y() << " " << p.z() << std::endl;
  //-- triangles
  for (auto& f: _lsTr)
  {
    for (auto& t: f) 
    {
      ss << "3 " << t[0] << " " << t[1] << " " << t[2] << std::endl;
    }
  }
  return ss.str();
}


std::string Surface::get_coords_key(Point3* p)
{
  std::string s;
  if (_tol_snap < 0.0)
  {
    s = std::to_string(p->x()) + std::to_string(p->y()) + std::to_string(p->z());
  }
  else
  {
    int tol = int(1 / _tol_snap);
    s = std::to_string(int64(p->x() * tol)) + " " + std::to_string(int64(p->y() * tol)) + " " + std::to_string(int64(p->z() * tol));
  }
  return s;
}

bool Surface::were_vertices_merged_during_parsing()
{
  if (this->number_vertices() == this->_vertices_added)
    return false;
  else 
    return true;
}


int Surface::get_number_parsed_vertices()
{
  return _vertices_added;
}


int Surface::add_point(Point3 p)
{
  _vertices_added += 1;
  auto it = _dPts.find(get_coords_key(&p));
  if (it == _dPts.end()) 
  {
    _lsPts.push_back(p);
    _dPts[get_coords_key(&p)] = (_lsPts.size() - 1); 
    return (_lsPts.size() - 1);
  }
  return it->second;
}


void Surface::add_face(std::vector< std::vector<int> > f, std::string id)
{
  _lsFaces.push_back(f);
  if (id.empty() == true)
    _lsFacesID.push_back(std::to_string(_lsFaces.size()));
  else
    _lsFacesID.push_back(id);
}


int Surface::number_vertices()
{
  return _lsPts.size();
}


int Surface::number_faces()
{
  return _lsFaces.size();
}


bool Surface::triangulate_shell()
{
  std::clog << "-----Triangulation of each surface" << std::endl;
  //-- read the facets
  size_t num = _lsFaces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    // These are the number of rings on this facet
    size_t numf = _lsFaces[i].size();
    std::vector<int> &idsob = _lsFaces[i][0]; // helpful alias for the outer boundary
    if ( (numf == 1) && (idsob.size() == 3)) 
    {
      std::vector<int*> oneface;
      int* tr = new int[3];
      tr[0] = idsob[0] ;
      tr[1] = idsob[1];
      tr[2] = idsob[2];
      oneface.push_back(tr);
      _lsTr.push_back(oneface);
      continue;
    }
    
    std::vector<Point3> allpts;
    std::vector<int>::const_iterator itp = idsob.begin();
    for ( ; itp != idsob.end(); itp++)
      allpts.push_back(_lsPts[*itp]);
    //-- irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      std::vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      std::vector<int>::const_iterator itp2 = ids2.begin();
      for ( ; itp2 != ids2.end(); itp2++)
        allpts.push_back(_lsPts[*itp2]);
    }
    CgalPolyhedron::Plane_3 bestfitplane;
    get_best_fitted_plane(allpts, bestfitplane);
    
    // int proj = projection_plane(_lsPts, idsob);
    // Vector v0 = bestfitplane.orthogonal_vector();

    //-- get projected Polygon
    Polygon pgn;
    std::vector<Polygon> lsRings;
    create_cgal_polygon(_lsPts, idsob, bestfitplane, pgn);
    //-- all polygons should be cw for Triangle
    //-- if reversed then re-reversed later
    bool reversed = false;
    if (pgn.is_counterclockwise_oriented() == false) {
      pgn.reverse_orientation();
      reversed = true;
    }
    lsRings.push_back(pgn);
    std::vector< std::vector<int> > pgnids;
    pgnids.push_back(idsob);
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      std::vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      //-- get projected Polygon
      Polygon pgn;
      create_cgal_polygon(_lsPts, ids2, bestfitplane, pgn);
      if (pgn.is_counterclockwise_oriented() == false) {
        pgn.reverse_orientation();
      }
      lsRings.push_back(pgn);
      pgnids.push_back(ids2);
    }
    //-- get projected CT
    std::vector<int*> oneface;
    if (construct_ct(pgnids, lsRings, oneface, i, bestfitplane) == false)
    {
      this->add_error(999, _lsFacesID[i], "face does not have an outer boundary.");
      return false;
    }
    if (reversed == true) //-- reversed back to keep orientation of original surface
    {
      std::vector<int*>::iterator it3 = oneface.begin();
      int tmp;
      int* id;
      for ( ; it3 != oneface.end(); it3++)
      {
        id = *it3;
        tmp = id[0];
        id[0] = id[1];
        id[1] = tmp;
      }
    }
    _lsTr.push_back(oneface);
  }
  return true;
}


bool Surface::construct_ct(const std::vector< std::vector<int> >& pgnids, const std::vector<Polygon>& lsRings, std::vector<int*>& oneface, int faceNum, const CgalPolyhedron::Plane_3 &plane)
{
  std::vector<int> ids = pgnids[0];
  CT ct;
  std::vector< std::vector<int> >::const_iterator it = pgnids.begin();
  size_t numpts = 0;
  for ( ; it != pgnids.end(); it++)
  {
    numpts += it->size();
  }
  for ( it = pgnids.begin(); it != pgnids.end(); it++)
  {
    std::vector<Point2> pts2d;
    std::vector<int>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      Point3 p1 = _lsPts[*it2];
      pts2d.push_back(plane.to_2d(p1));
    }
    std::vector<Point2>::const_iterator itPt;
    CT::Vertex_handle v0;
    CT::Vertex_handle v1;
    CT::Vertex_handle firstv;
    itPt = pts2d.begin();
    v0 = ct.insert(*itPt);
    firstv = v0;
    it2 = it->begin();
    v0->id() = *it2;
    itPt++;
    it2++;
    for (; itPt != pts2d.end(); itPt++)
    {
      v1 = ct.insert(*itPt);
      v1->id() = *it2;
      ct.insert_constraint(v0, v1);
      v0 = v1;
      it2++;
    }
    ct.insert_constraint(v0,firstv);
  }
  //Mark facets that are inside the domain bounded by the polygon
  mark_domains(ct); 
  if (!ct.is_valid()) 
    return false;
    
  for (CT::Finite_faces_iterator fit = ct.finite_faces_begin();
       fit != ct.finite_faces_end(); 
       ++fit) 
  {
    if (fit->info().in_domain()) {
      int* tr = new int[3];
      tr[0] = fit->vertex(0)->id();
      tr[1] = fit->vertex(1)->id();
      tr[2] = fit->vertex(2)->id();
      oneface.push_back(tr);
    }
  }
  return true;
}


void Surface::get_min_bbox(double& x, double& y)
{
  std::vector<Point3>::iterator it = _lsPts.begin();
  K::FT minx = 9e10;
  K::FT miny = 9e10;
  for ( ; it != _lsPts.end(); it++)
  {
    if (it->x() < minx)
      minx = it->x();
    if (it->y() < miny)
      miny = it->y();
  }
  x = minx;
  y = miny;
}


void Surface::translate_vertices()
{
  std::vector<Point3>::iterator it = _lsPts.begin();
  for (it = _lsPts.begin(); it != _lsPts.end(); it++)
  {
    Point3 tp(CGAL::to_double(it->x() - Surface::_shiftx), CGAL::to_double(it->y() - Surface::_shifty), CGAL::to_double(it->z()));
    *it = tp;
  }
}


void Surface::set_translation_min_values(double minx, double miny)
{
  Surface::_shiftx = minx;
  Surface::_shifty = miny;
}


bool Surface::validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "-----2D validation of each surface" << std::endl;
  bool isValid = true;
  size_t num = _lsFaces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    //-- test for too few points (<3 for a ring)
    if (has_face_rings_toofewpoints(_lsFaces[i]) == true)
    {
      this->add_error(101, _lsFacesID[i]);
      isValid = false;
      continue;
    }
    //-- test for 2 repeated consecutive points
    if (has_face_2_consecutive_repeated_pts(_lsFaces[i]) == true)
    {
      this->add_error(102, _lsFacesID[i]);
      isValid = false;
      continue;
    }
    size_t numf = _lsFaces[i].size();
    std::vector<int> &ids = _lsFaces[i][0]; // helpful alias for the outer boundary

    //-- if only 3 pts it's not valid, no need to process further
    if ( (numf == 1) && (ids.size() == 3)) 
    {
      if (CGAL::collinear(_lsPts[ids[0]], _lsPts[ids[1]], _lsPts[ids[2]]) == true) {
        this->add_error(104, _lsFacesID[i], " outer ring (a triangle) is collapsed to a line");
        isValid = false;
      }
      continue;
    }

    std::vector< Point3 > allpts;
    std::vector<int>::const_iterator itp = ids.begin();
    for ( ; itp != ids.end(); itp++)
    {
      allpts.push_back(_lsPts[*itp]);
    }
    //-- irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      std::vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      std::vector<int>::const_iterator itp2 = ids2.begin();
      for ( ; itp2 != ids2.end(); itp2++)
      {
        allpts.push_back(_lsPts[*itp2]);
      }
    }
    double value;
    CgalPolyhedron::Plane_3 bestfitplane;
    get_best_fitted_plane(allpts, bestfitplane);
    if (false == is_face_planar_distance2plane(allpts, bestfitplane, value, tol_planarity_d2p))
    {
      std::stringstream msg;
      msg << "distance to fitted plane: " << value << " (tolerance=" << tol_planarity_d2p << ")";
      this->add_error(203, _lsFacesID[i], msg.str());
      isValid = false;
      continue;
    }
    //-- get projected oring
    Polygon pgn;
    std::vector<Polygon> lsRings;
    create_cgal_polygon(_lsPts, ids, bestfitplane, pgn);
    if (validate_projected_ring(pgn, _lsFacesID[i]) == false)
    {
      isValid = false;
      continue;
    }
    lsRings.push_back(pgn);
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      std::vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      //-- get projected iring
      Polygon pgn;
      create_cgal_polygon(_lsPts, ids2, bestfitplane, pgn);
      if (validate_projected_ring(pgn, _lsFacesID[i]) == false)
      {
        isValid = false;
        continue;
      }
      lsRings.push_back(pgn);
    }
    //-- use GEOS to validate projected polygon
    if (!validate_polygon(lsRings, _lsFacesID[i]))
      isValid = false;
  }
  if (isValid)
  {
    //-- triangulate faces of the shell
    triangulate_shell();
    //-- check planarity by normal deviation method (of all triangle)
    std::clog << "-----Planarity of surfaces (with normals deviation)" << std::endl;
    std::vector< std::vector<int*> >::iterator it = _lsTr.begin();
    int j = 0;
    double deviation;
    for ( ; it != _lsTr.end(); it++)
    { 
      if (is_face_planar_normals(*it, _lsPts, deviation, tol_planarity_normals) == false)
      {
        std::ostringstream msg;
        msg << "deviation normals: " << deviation << " (tolerance=" << tol_planarity_normals << ")";
        this->add_error(204, _lsFacesID[j], msg.str());
        isValid = false;
      }
      j++;
    }
  }
  _is_valid_2d = isValid;
  return isValid;
}


bool Surface::validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "--- MultiSurface validation ---" << std::endl;
  if (_is_valid_2d == -1)
    return validate_2d_primitives(tol_planarity_d2p, tol_planarity_normals);
  else
  {
    if (_is_valid_2d == 1)
      return true;
    else
      return false;
  }
}


bool Surface::is_shell(double tol_planarity_d2p, double tol_planarity_normals) 
{
  return validate_as_shell(tol_planarity_d2p, tol_planarity_normals);
}


bool Surface::validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "--- CompositeSurface validation ---" << std::endl;
//-- 1. Each surface should individually be valid
  if (_is_valid_2d == -1)
    validate_2d_primitives(tol_planarity_d2p, tol_planarity_normals);
  if (_is_valid_2d == 0)
    return false;
//-- 2. Combinatorial consistency
  std::clog << "--Combinatorial consistency" << std::endl;
  _polyhedron = construct_CgalPolyhedron_incremental(&(_lsTr), &(_lsPts), this);
  if (this->has_errors() == true)
    return false;
  if (_polyhedron != NULL)
  {
    if (_polyhedron->is_valid() == true)
    {
      if (_polyhedron->keep_largest_connected_components(1) > 0)
      {
        this->add_error(305);
        return false;
      }
    }
    else 
    {
      this->add_error(300, "", "Something went wrong during construction of the shell, reason is unknown.");
      return false;
    }
    //-- check for non-manifold vertices
    //-- errors will be added to the Surface
    this->contains_nonmanifold_vertices();
  }
  else
  {
    this->add_error(300, "", "Something went wrong during construction of the shell, reason is unknown.");
    return false;
  }
  if (this->has_errors() == true)
    return false;
//-- 2. Geometrical consistency (aka intersection tests between faces)
  std::clog << "--Geometrical consistency" << std::endl;
  if (does_self_intersect() == false)
    return false;
  return true;
}


bool Surface::contains_nonmanifold_vertices()
{
  //-- check for non-manifold vertices (which oddly CGAL doesn't expose as a function)
  //-- the trick is to check if a given vertex has >2 incident edges (not half-edges, but edges)
  //-- that are border edges
  // count border edges 
  std::map<CgalPolyhedron::Vertex_handle, int> noincident;
  for (CgalPolyhedron::Halfedge_handle heh = _polyhedron->halfedges_begin(); heh != _polyhedron->halfedges_end(); heh++)
  {
    if (heh->is_border() == true)
    {
      auto it = noincident.find(heh->vertex());
      if (it == noincident.end())
        noincident[heh->vertex()] = 1;
      else
        noincident[heh->vertex()] += 1;
      it = noincident.find(heh->opposite()->vertex());
      if (it == noincident.end())
        noincident[heh->opposite()->vertex()] = 1;
      else
        noincident[heh->opposite()->vertex()] += 1;
    }
  }
  for (auto& v : noincident)
  {
    if (v.second > 2)
    {
      std::stringstream st;
      st << "Vertex location: (";;
      st << (v.first->point().x() + _shiftx);
      st << ", ";
      st << (v.first->point().y() + _shifty);
      st << ", ";
      st << v.first->point().z();
      st << ")";
      this->add_error(303, "", st.str());
    }
  }
  return (this->has_errors());
}

bool Surface::does_self_intersect()
{
  if (CGAL::Polygon_mesh_processing::does_self_intersect(*_polyhedron) == true)
  {
    std::vector<std::pair<CgalPolyhedron::Facet_const_handle, CgalPolyhedron::Facet_const_handle> > intersected_tris;
    CGAL::Polygon_mesh_processing::self_intersections(*_polyhedron, std::back_inserter(intersected_tris));
    std::set<CgalPolyhedron::Facet_const_handle> uniquetr;
    for (auto& each : intersected_tris)
    {
      uniquetr.insert(each.first);
      uniquetr.insert(each.second);
    }
    for (auto& each : uniquetr)
    {
      //-- report the triangle centroid, as an approximation of the intersection
      //-- faster and less error-prone than reporting exact location
      Point3 c = CGAL::centroid(each->halfedge()->vertex()->point(),
                                each->halfedge()->next()->vertex()->point(),
                                each->halfedge()->next()->next()->vertex()->point()); 
      std::stringstream st;
      st << "Location close to: (";
      st << c.x() + _shiftx;
      st << ", ";
      st << c.y() + _shifty;
      st << ", ";
      st << c.z();
      st << ")"; 
      this->add_error(306, "", st.str());
    }
    return false;
  }
  return true;
}


bool Surface::validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "--- Shell validation (#" << _id << ") ---" << std::endl;
  if (_is_valid_2d == -1)
    validate_2d_primitives(tol_planarity_d2p, tol_planarity_normals);
  if (_is_valid_2d == 0)
    return false;
//-- 1. minimum number of faces = 4
  if (_lsTr.size() < 4) 
  {
    this->add_error(301);
    return false;
  }
//-- 2. Combinatorial consistency
  std::clog << "-----Combinatorial consistency" << std::endl;
  _polyhedron = construct_CgalPolyhedron_incremental(&(_lsTr), &(_lsPts), this);
  if (this->has_errors() == true)
    return false;
  if (_polyhedron != NULL)
  {
    if (_polyhedron->is_valid() == true)
    {
      if (_polyhedron->is_closed() == false)
      {
        _polyhedron->normalize_border();
        //-- check for unconnected faces
        if (_polyhedron->keep_largest_connected_components(1) > 0)
        {
          //TODO: how to report what face is not connected? a bitch of a problem...
          this->add_error(305);
          return false;
        }
        else
        {
          //-- check if there are holes in the surface
          if (_polyhedron->is_closed() == false)
          {
            std::stringstream st;
            _polyhedron->normalize_border();
            while (_polyhedron->size_of_border_edges() > 0) {
              CgalPolyhedron::Halfedge_handle he = ++(_polyhedron->border_halfedges_begin());
              st << "Location hole: (";
              st << (he->vertex()->point().x() + _shiftx);
              st << ", ";
              st << (he->vertex()->point().y() + _shifty);
              st << ", ";
              st << he->vertex()->point().z();
              st << ")";
              this->add_error(302, "", st.str());
              st.str("");
              _polyhedron->fill_hole(he);
              _polyhedron->normalize_border();
            }
            return false;
          }
        }
      }
      else //-- check if >1 connected components exist (both valid)
      {
        if (_polyhedron->keep_largest_connected_components(1) > 0) 
        {
          this->add_error(305, "", "More than one connected components.");
          return false;
        }
      }
    }
    else 
    {
      this->add_error(300, "", "Something went wrong during construction of the shell, reason is unknown.");
      return false;
    }
  }
  else
  {
    this->add_error(300, "", "Something went wrong during construction of the shell, reason is unknown.");
    return false;
  }
//-- 3. Geometrical consistency (aka intersection tests between faces)
  std::clog << "-----Geometrical consistency" << std::endl;
  if (does_self_intersect() == false)
    return false;
  return true;
}


bool Surface::validate_projected_ring(Polygon &pgn, std::string id)
{
  if ( (!pgn.is_simple()) || (pgn.orientation() == CGAL::COLLINEAR) )
  {
    this->add_error(104, id, "ring self-intersects or is collapsed to a line");
    return false;
  }
  return true;
}


bool Surface::validate_polygon(std::vector<Polygon> &lsRings, std::string polygonid)
{
  initGEOS(NULL, NULL);
  //-- check the orientation of the rings: oring != irings
  //-- we don't care about CCW or CW at this point, just opposite is important
  //-- GEOS doesn't do its job, so we have to do it here. Shame on you GEOS.
  bool isvalid = true;
  if (lsRings.size() > 1)
  {
    CGAL::Orientation ooring = lsRings[0].orientation();
    std::vector<Polygon>::iterator it = lsRings.begin();
    it++;
    for ( ; it != lsRings.end(); it++)
    {
      if (it->orientation() == ooring)
      {
        this->add_error(208, polygonid, "same orientation for outer and inner rings");
        isvalid = false;
        break;
      }
    }
  }
  if (isvalid == false)
    return isvalid;
  //-- check 2D validity of the surface by (1) projecting them; (2) use GEOS IsValid()
  stringstream wkt;
  wkt << setprecision(15);
  wkt << "POLYGON(";
  std::vector<Polygon>::iterator it = lsRings.begin();
  //-- oring
  wkt << "(";
  Polygon::Vertex_iterator vit = it->vertices_begin();
  for ( ; vit != it->vertices_end(); vit++)
  {
    wkt << vit->x() << " " << vit->y() << ",";
  }
  vit = it->vertices_begin();
  wkt << vit->x() << " " << vit->y() << ")";
  it++;
  //-- irings
  for ( ; it != lsRings.end(); it++)
  {
    wkt << ", (";
    it->reverse_orientation();
    Polygon::Vertex_iterator vit = it->vertices_begin();
    for ( ; vit != it->vertices_end(); vit++)
    {
      wkt << vit->x() << " " << vit->y() << ",";
    }
    vit = it->vertices_begin();
    wkt << vit->x() << " " << vit->y() << ")";
    it->reverse_orientation();
  }
  wkt << ")";
  GEOSWKTReader* r;
  r = GEOSWKTReader_create();
  GEOSGeometry* mygeom;
  mygeom = GEOSWKTReader_read(r, wkt.str().c_str());
  string reason = (string)GEOSisValidReason(mygeom);
  if (reason.find("Valid Geometry") == string::npos)
  {
    isvalid = false;
    if (reason.find("Self-intersection") != string::npos)
      this->add_error(201, polygonid, reason.c_str());
    else if (reason.find("Duplicate Rings") != string::npos)
      this->add_error(202, polygonid, reason.c_str());
    else if (reason.find("Interior is disconnected") != string::npos)
      this->add_error(205, polygonid, reason.c_str());
    else if (reason.find("Hole lies outside shell") != string::npos)
      this->add_error(206, polygonid, reason.c_str());
    else if (reason.find("Holes are nested") != string::npos)
      this->add_error(207, polygonid, reason.c_str());
    else
      this->add_error(999, polygonid, reason.c_str());
  }
  GEOSGeom_destroy( mygeom );
  finishGEOS();
  return isvalid;
}

bool Surface::has_face_2_consecutive_repeated_pts(const std::vector< std::vector<int> >& theface)
{
  bool bDuplicates = false;
  std::vector< std::vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    size_t numv = itr->size();
    //-- first-last not the same (they are not in GML format anymore)
    if ((*itr)[0] == (*itr)[numv - 1]) {
      bDuplicates = true;
      break;
    }
    for (int i = 0; i < (static_cast<int>(numv) - 1); i++) {
      if ((*itr)[i] == (*itr)[i+1]) {
        bDuplicates = true;
        break;
      }
    }
  }
  return bDuplicates;
}

bool Surface::has_face_rings_toofewpoints(const std::vector< std::vector<int> >& theface)
{
  bool bErrors = false;
  std::vector< std::vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    if (itr->size() < 3) {
      bErrors = true;
      break;
    }
  }
  return bErrors;
}

} // namespace val3dity
