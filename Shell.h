//
//  Shell.h
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#ifndef __val3dity__Shell__
#define __val3dity__Shell__

#include "definitions.h"

class Shell
{
public:
  Shell  (int id = -1, double tol_snap = 0.0);
  ~Shell ();
  
  int    number_vertices();
  int    number_faces();
  bool   is_outer();
  int    get_id();
  CgalPolyhedron* get_cgal_polyhedron();
  
  bool   validate(Primitive3D prim, double tol_planarity_d2p, double tol_planarity_normals);

  bool   is_empty();
  int    add_point(Point3 p);
  void   add_face(vector< vector<int> > f);

  std::string   get_report_xml();
  std::string   get_report_text();
  void          add_error(int code, int faceid, std::string info = "");
  bool          has_errors();
  std::set<int> get_unique_error_codes();
  void          translate_vertices();
  std::string   get_poly_representation();
  
private:
  int                             _id;
  vector<Point3>                  _lsPts;
  vector< vector< vector<int> > > _lsFaces;
  vector< vector<int*> >          _lsTr;
  CgalPolyhedron*                 _polyhedron;

  std::map<int, vector<std::tuple<int, std::string> > > _errors;

  double                          _tol_snap;
  int                             _is_valid_2d; //-1: not done yet; 0: nope; 1: yes it's valid

  bool validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals);
  bool validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals);
  
  bool triangulate_shell();
  bool construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
  bool validate_polygon(vector<Polygon> &lsRings, int polygonid);
  bool has_face_rings_toofewpoints(const vector< vector<int> >& theface);
  bool has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface);

};


#endif /* defined(__val3dity__Shell__) */
