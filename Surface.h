//
//  Surface.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef Surface_h
#define Surface_h

#include "definitions.h"
#include <string>
#include <vector>
#include <set>
#include <unordered_map>



class Surface
{
public:
  Surface  (int id = -1, double tol_snap = 0.0);
  ~Surface ();
  
  bool validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals);
  
  bool is_shell(double tol_planarity_d2p, double tol_planarity_normals);

  CgalPolyhedron* get_cgal_polyhedron();

  int    number_vertices();
  int    number_faces();
  void   get_min_bbox(double& x, double& y);
  int    get_id();

  bool   does_self_intersect();
  bool   is_empty();
  int    add_point(Point3 p);
  void   add_face(std::vector< std::vector<int> > f, std::string id = "");

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
  std::vector<Point3>                     _lsPts;
  std::unordered_map< std::string, int >  _dPts;
  std::vector< std::vector< std::vector<int> > >    _lsFaces;
  std::vector<std::string>                _lsFacesID;
  std::vector< std::vector<int*> >        _lsTr;
  CgalPolyhedron*                         _polyhedron;
  double                                  _tol_snap;
  int                                     _is_valid_2d; //-1: not done yet; 0: nope; 1: yes it's valid
  int                                     _vertices_added;

  std::map<int, std::vector<std::tuple<std::string, std::string> > > _errors;
  
  bool validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals);
  std::string get_coords_key(Point3* p);
  bool triangulate_shell();
  bool construct_ct(const std::vector< std::vector<int> >& pgnids, const std::vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
  bool validate_polygon(std::vector<Polygon> &lsRings, std::string polygonid);
  bool has_face_rings_toofewpoints(const std::vector< std::vector<int> >& theface);
  bool has_face_2_consecutive_repeated_pts(const std::vector< std::vector<int> >& theface);

};


#endif /* Surface_h */
