//
//  Shell.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Shell.h"
#include "geomtools.h"
#include "input.h"
#include "validate_shell.h"
#include "validate_shell_intersection.h"
#include <GEOS/geos_c.h>
#include <sstream>



Shell2::Shell2(int id, double tol_snap)
{
  _id = id;
  _tol_snap = tol_snap;
  _is_valid = -1;
  _is_valid_2d = -1;
}

Shell2::~Shell2()
{
  // TODO: clear memory properly
  _lsPts.clear();
}

int Shell2::get_id()
{
  return _id;
}

CgalPolyhedron* Shell2::get_cgal_polyhedron()
{
  return _polyhedron;
}

void Shell2::add_error(int code, int faceid, std::string info)
{
  std::pair<int, std::string> a(faceid, info);
  _errors[code].push_back(a);
  std::clog << "\tERROR " << code << ": " << errorcode2description(code);
  if (faceid != -1)
    std::clog << " (face #" << faceid << ")";
  std::clog << std::endl;
  if (info.empty() == false)
    std::clog << "\t[" << info << "]" << std::endl;
}

std::set<int> Shell2::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
  {
    errs.insert(err.first);
  }
  return errs;
}


std::string Shell2::get_report_xml()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[err.first])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << err.first << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(err.first) << "</type>" << std::endl;
      ss << "\t\t\t<shell>" << this->_id << "</shell>" << std::endl;
      ss << "\t\t\t<face>" << e.first << "</face>" << std::endl;
      ss << "\t\t\t<info>" << e.second << "</info>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  return ss.str();
}


std::string Shell2::get_report_text()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[err.first])
    {
      ss << err.first << " -- " << errorcode2description(err.first) << std::endl;
      ss << "\tShell: " << this->_id << std::endl;
      ss << "\tFace: "  << e.first << std::endl;
      ss << "\tInfo: "  << e.second << std::endl;
    }
  }
  return ss.str();
}


std::string Shell2::get_poly_representation()
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

int Shell2::add_point(Point3 p)
{
  int pos = -1;
  int cur = 0;
  for (auto &itr : _lsPts)
  {
    // std::clog << "---" << itr << std::endl;
    if (cmpPoint3(p, itr, _tol_snap) == true)
    {
      pos = cur;
      break;
    }
    cur++;
  }
  if (pos == -1)
  {
    _lsPts.push_back(p);
    return (_lsPts.size() - 1);
  }
  else
    return pos;
}


void Shell2::add_face(vector< vector<int> > f)
{
  _lsFaces.push_back(f);
}


int Shell2::number_points()
{
  return _lsPts.size();
}


int Shell2::number_faces()
{
  return _lsFaces.size();
}


bool Shell2::is_outer()
{
  return (_id == 0);
}

bool Shell2::triangulate_shell()
{
  std::clog << "--Triangulation of each surface" << std::endl;
  //-- read the facets
  size_t num = _lsFaces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    // These are the number of rings on this facet
    size_t numf = _lsFaces[i].size();
    vector<int> &idsob = _lsFaces[i][0]; // helpful alias for the outer boundary
    int proj = projection_plane(_lsPts, idsob);
    Vector* v0 = polygon_normal(_lsPts, idsob);
    //-- get projected Polygon
    Polygon pgn;
    vector<Polygon> lsRings;
    create_polygon(_lsPts, idsob, pgn, true);
    lsRings.push_back(pgn);
    vector< vector<int> > pgnids;
    pgnids.push_back(idsob);
    
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      //-- get projected Polygon
      Polygon pgn;
      create_polygon(_lsPts, ids2, pgn, true);
      lsRings.push_back(pgn);
      pgnids.push_back(ids2);
    }
    //-- get projected CT
    vector<int*> oneface;
    if (construct_ct(pgnids, lsRings, oneface, i) == false)
    {
      this->add_error(999, i, "face does not have an outer boundary.");
      return false;
    }
    //-- modify orientation of every triangle if necessary
    bool invert = false;
    if (proj == 2)
    {
      Vector n(0, 0, 1);
      if ( (*v0*n) < 0)
        invert = true;
    }
    else if (proj == 1)
    {
      Vector n(0, 1, 0);
      if ( (*v0*n) > 0)
        invert = true;
    }
    else if(proj == 0)
    {
      Vector n(1, 0, 0);
      if ( (*v0*n) < 0)
        invert = true;
    }
    delete v0;
    if ( invert == true ) //-- invert
    {
      vector<int*>::iterator it3 = oneface.begin();
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


bool Shell2::construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum)
{
  bool isValid = true;
  vector<int> ids = pgnids[0];
  int proj = projection_plane(_lsPts, ids);
  CT ct;
  vector< vector<int> >::const_iterator it = pgnids.begin();
  size_t numpts = 0;
  for ( ; it != pgnids.end(); it++)
  {
    numpts += it->size();
  }
  for ( it = pgnids.begin(); it != pgnids.end(); it++)
  {
    vector<Point2> pts2d;
    vector<int>::const_iterator it2 = it->begin();
    for ( ; it2 != it->end(); it2++)
    {
      Point3 p1  = _lsPts[*it2];
      if (proj == 2)
        pts2d.push_back( Point2(p1.x(), p1.y()) );
      else if (proj == 1)
        pts2d.push_back( Point2(p1.x(), p1.z()) );
      else
        pts2d.push_back( Point2(p1.y(), p1.z()) );
    }
    vector<Point2>::const_iterator itPt;
    CT::Vertex_handle v0;
    CT::Vertex_handle v1;
    CT::Vertex_handle firstv;
    itPt = pts2d.begin();
    v0 = ct.insert(*itPt);
    firstv = v0;
    it2 = it->begin();
    v0->info() = *it2;
    itPt++;
    it2++;
    for (; itPt != pts2d.end(); itPt++)
    {
      v1 = ct.insert(*itPt);
      v1->info() = *it2;
      ct.insert_constraint(v0, v1);
      v0 = v1;
      it2++;
    }
    ct.insert_constraint(v0,firstv);
  }
  //-- validation of the face itself
  //-- if the CT introduced new points, then there are irings intersectings either oring or other irings
  //-- which is not allowed
  // TODO: is this true? not 100% I think, and can be removed since caught later with GEOS
  // if (numpts < ct.number_of_vertices())
  // {
  //   std::stringstream ss;
  //   ss << "Intersection(s) between rings of the face #" << faceNum << ".";
  //   (*_cb)(0, -1, -1, ss.str());
  //   isValid = false;
  // }  
  //-- fetch all the triangles forming the polygon (with holes)
  CT::Finite_faces_iterator fi = ct.finite_faces_begin();
  for( ; fi != ct.finite_faces_end(); fi++)
  {
    Point2 centre = barycenter( ct.triangle(fi).vertex(0), 1,
                               ct.triangle(fi).vertex(1), 1,
                               ct.triangle(fi).vertex(2), 1);
    bool inside = true;
    if (lsRings[0].has_on_negative_side(centre))
      inside = false;
    else
    {
      vector<Polygon>::const_iterator itpgn = lsRings.begin();
      itpgn++;
      for ( ; itpgn != lsRings.end(); itpgn++)   //-- check irings
      {
        if (itpgn->has_on_positive_side(centre))
        {
          inside = false;
          break;
        }
      }
    }
    if (inside == true)
    {
      //-- add the IDs to the face
      int* tr = new int[3];
      tr[0] = fi->vertex(0)->info();
      tr[1] = fi->vertex(1)->info();
      tr[2] = fi->vertex(2)->info();
      oneface.push_back(tr);
    }
  }
  return isValid;
}


void Shell2::translate_vertices()
{
  vector<Point3>::iterator it = _lsPts.begin();
  K::FT minx = 9e10;
  K::FT miny = 9e10;
  for ( ; it != _lsPts.end(); it++)
  {
    if (it->x() < minx)
      minx = it->x();
    if (it->y() < miny)
      miny = it->y();
  }
  for (it = _lsPts.begin(); it != _lsPts.end(); it++)
  {
    Point3 tp(CGAL::to_double(it->x() - minx), CGAL::to_double(it->y() - miny), CGAL::to_double(it->z()));
    *it = tp;
  }
}


bool Shell2::validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "--2D validation of each surface" << std::endl;
  bool isValid = true;
  size_t num = _lsFaces.size();
  for (int i = 0; i < static_cast<int>(num); i++)
  {
    //-- test for too few points (<3 for a ring)
    if (has_face_rings_toofewpoints(_lsFaces[i]) == true)
    {
      this->add_error(101, i);
      isValid = false;
      continue;
    }
    //-- test for 2 repeated consecutive points
    if (has_face_2_consecutive_repeated_pts(_lsFaces[i]) == true)
    {
      this->add_error(102, i);
      isValid = false;
      continue;
    }
    size_t numf = _lsFaces[i].size();
    vector<int> &ids = _lsFaces[i][0]; // helpful alias for the outer boundary
    vector< Point3 > allpts;
    vector<int>::const_iterator itp = ids.begin();
    for ( ; itp != ids.end(); itp++)
    {
      allpts.push_back(_lsPts[*itp]);
    }
    //-- irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      vector<int>::const_iterator itp2 = ids2.begin();
      for ( ; itp2 != ids2.end(); itp2++)
      {
        allpts.push_back(_lsPts[*itp2]);
      }
    }
    double value;
    if (false == is_face_planar_distance2plane(allpts, value, tol_planarity_d2p))
    {
      std::stringstream msg;
      msg << "distance to fitted plane: " << value << " (tolerance=" << tol_planarity_d2p << ")";
      this->add_error(203, i, msg.str());
      isValid = false;
      continue;
    }
    //-- get projected oring
    Polygon pgn;
    vector<Polygon> lsRings;
    if (false == create_polygon(_lsPts, ids, pgn, false))
    {
      this->add_error(104, i, " outer ring self-intersects or is collapsed to a point or a line");
      isValid = false;
      continue;
    }
    lsRings.push_back(pgn);
    //-- check for irings
    for (int j = 1; j < static_cast<int>(numf); j++)
    {
      vector<int> &ids2 = _lsFaces[i][j]; // helpful alias for the inner boundary
      //-- get projected iring
      Polygon pgn;
      if (false == create_polygon(_lsPts, ids2, pgn, false))
      {
        this->add_error(104, i, "Inner ring self-intersects or is collapsed to a point or a line");
        isValid = false;
        continue;
      }
      lsRings.push_back(pgn);
    }
    //-- use GEOS to validate projected polygon
    if (!validate_polygon(lsRings, num))
      isValid = false;
  }
  if (isValid)
  {
    //-- triangulate faces of the shell
    triangulate_shell();
    //-- check planarity by normal deviation method (of all triangle)
    std::clog << "--Planarity of surfaces (with normals deviation)" << std::endl;
    vector< vector<int*> >::iterator it = _lsTr.begin();
    int j = 0;
    double deviation;
    for ( ; it != _lsTr.end(); it++)
    { 
      if (is_face_planar_normals(*it, _lsPts, deviation, tol_planarity_normals) == false)
      {
        std::ostringstream msg;
        msg << "deviation normals: " << deviation << " (tolerance=" << tol_planarity_normals << ")";
        this->add_error(204, j, msg.str());
        isValid = false;
      }
      j++;
    }
  }
  _is_valid_2d = isValid;
  return isValid;
}


bool Shell2::validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals)
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


bool Shell2::validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals)
{
  // TODO: not working yet
  std::clog << "--- MultiSurface validation ---" << std::endl;
  return validate_2d_primitives(tol_planarity_d2p, tol_planarity_normals);
}


bool Shell2::validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals)
{
  std::clog << "----- Shell validation (#" << _id << ") -----" << std::endl;
  if (_is_valid_2d == -1)
    validate_2d_primitives(tol_planarity_d2p, tol_planarity_normals);
  if (_is_valid_2d == 0)
    return false;
  bool isValid = true;
//-- 1. minimum number of faces = 4
  if (_lsTr.size() < 4) 
  {
    this->add_error(301, -1);
    isValid = false;
    return false;
  }
//-- 2. Combinatorial consistency
  std::clog << "--Combinatorial consistency" << std::endl;
  _polyhedron = construct_CgalPolyhedron_incremental(&(_lsTr), &(_lsPts), this);
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
          this->add_error(305, -1);
          isValid = false;
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
              st << "Location hole: " << he->vertex()->point();
              this->add_error(302, -1, st.str());
              st.str("");
              _polyhedron->fill_hole(he);
              _polyhedron->normalize_border();
            }
            isValid = false;
          }
        }
      }
      else //-- check if >1 connected components exist (both valid)
      {
        if (_polyhedron->keep_largest_connected_components(1) > 0) 
        {
          this->add_error(305, -1, "More than one connected components.");
          isValid = false;
        }
      }
    }
    else 
    {
      this->add_error(300, -1, "Something went wrong during construction of the shell, reason is unknown.");
      isValid = false;
    }
  }
//-- 3. Geometrical consistency (aka intersection tests between faces)
  if (isValid == true)
  {
    std::clog << "--Geometrical consistency" << std::endl;
    isValid = is_polyhedron_geometrically_consistent(this);
  }
//-- 4. orientation of the normals is outwards or inwards
  if (isValid == true)
  {
    std::clog << "--Orientation of normals" << std::endl;
    isValid = check_global_orientation_normals_rev2(_polyhedron, this->is_outer());
    if (isValid == false)
      this->add_error(308, -1);
  }
  
  if (isValid == false)
  {
    delete _polyhedron;
    _is_valid = 0;
  }
  else
  {
    // _polyhedron = P;
    _is_valid = 1;
  }
  return isValid;
}


bool Shell2::validate_polygon(vector<Polygon> &lsRings, int polygonid)
{
  // TODO: need to init GEOS and "close" it each time? I guess not...
  initGEOS(NULL, NULL);
  //-- check the orientation of the rings: oring != irings
  //-- we don't care about CCW or CW at this point, just opposite is important
  //-- GEOS doesn't do its job, so we have to do it here. Shame on you GEOS.
  bool isvalid = true;
  if (lsRings.size() > 1)
  {
    CGAL::Orientation ooring = lsRings[0].orientation();
    vector<Polygon>::iterator it = lsRings.begin();
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
  vector<Polygon>::iterator it = lsRings.begin();
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

bool Shell2::has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface)
{
  bool bDuplicates = false;
  vector< vector<int> >::const_iterator itr = theface.begin();
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

bool Shell2::has_face_rings_toofewpoints(const vector< vector<int> >& theface)
{
  bool bErrors = false;
  vector< vector<int> >::const_iterator itr = theface.begin();
  for ( ; itr != theface.end(); itr++) {
    if (itr->size() < 3) {
      bErrors = true;
      break;
    }
  }
  return bErrors;
}