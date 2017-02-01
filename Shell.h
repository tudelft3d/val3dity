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

#ifndef __val3dity__Shell__
#define __val3dity__Shell__

#include "definitions.h"
#include <unordered_map>

class Shell
{
public:
  Shell  (int id = -1, double tol_snap = 0.0);
  ~Shell ();
  
  int    number_vertices();
  int    number_faces();
  void   get_min_bbox(double& x, double& y);
  int    get_id();
  CgalPolyhedron* get_cgal_polyhedron();
  
  bool   validate(Primitive3D prim, double tol_planarity_d2p, double tol_planarity_normals);

  bool   is_empty();
  int    add_point(Point3 p);
  void   add_face(vector< vector<int> > f, std::string id = "");

  std::string   get_report_xml();
  std::string   get_report_text();
  void          add_error(int code, std::string faceid = "", std::string info = "");
  bool          has_errors();
  std::set<int> get_unique_error_codes();
  void          translate_vertices(double minx, double miny);
  std::string   get_poly_representation();
  bool          were_vertices_merged_during_parsing();
  int           get_number_parsed_vertices();
  
private:
  int                                     _id;
  vector<Point3>                          _lsPts;
  std::unordered_map< std::string, int >  _dPts;
  vector< vector< vector<int> > >         _lsFaces;
  vector<std::string>                     _lsFacesID;
  vector< vector<int*> >                  _lsTr;
  CgalPolyhedron*                         _polyhedron;
  double                                  _tol_snap;
  int                                     _is_valid_2d; //-1: not done yet; 0: nope; 1: yes it's valid
  int                                     _vertices_added;

  std::map<int, vector<std::tuple<std::string, std::string> > > _errors;

  bool validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals);
  
  std::string get_coords_key(Point3* p);
  bool triangulate_shell();
  bool construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
  bool validate_polygon(vector<Polygon> &lsRings, std::string polygonid);
  bool has_face_rings_toofewpoints(const vector< vector<int> >& theface);
  bool has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface);

  bool does_self_intersect();
};


#endif /* defined(__val3dity__Shell__) */
