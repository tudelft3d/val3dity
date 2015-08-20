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
//#include "geomtools.h"

class Shell2
{
public:
  Shell2  (int id = -1, double tol_snap = 0.0);
  ~Shell2 ();
  
  int    number_points();
  int    number_faces();
  bool   is_outer();
  int    get_id();
  CgalPolyhedron* get_cgal_polyhedron();
  
  int    add_point(Point3 p);
  void   add_face(vector< vector<int> > f);

  bool   validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals);

  std::string get_validation_xml();
  void   add_error(int code, int faceid, std::string info = "");
  void   translate_vertices();
  
private:
  int                             _id;
  vector<Point3>                  _lsPts;
  vector< vector< vector<int> > > _lsFaces;
  vector< vector<int*> >          _lsTr;
  CgalPolyhedron*                 _polyhedron;

  std::map<int, vector<std::pair<int, std::string> > > _errors;

  double                          _tol_snap;
  int                             _is_valid;    //-1: not done yet; 0: nope; 1: yes it's valid
  int                             _is_valid_2d; //-1: not done yet; 0: nope; 1: yes it's valid

  bool triangulate_shell();
  bool construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
  bool validate_polygon(vector<Polygon> &lsRings, int polygonid);
  bool has_face_rings_toofewpoints(const vector< vector<int> >& theface);
  bool has_face_2_consecutive_repeated_pts(const vector< vector<int> >& theface);

};


#endif /* defined(__val3dity__Shell__) */
