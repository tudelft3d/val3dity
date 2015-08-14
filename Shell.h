//
//  Shell.h
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#ifndef __val3dity__Shell__
#define __val3dity__Shell__

#include "val3dity_defs.h"
//#include "geomtools.h"

class Shell2
{
public:
  Shell2  (int id, double tol_snap, cbf cb);
  ~Shell2 ();
  
  int    number_points();
  int    number_faces();
  bool   is_outer();
  
  int    add_point(Point3 p);
  void   add_face(vector< vector<int> > f);

  bool   validate_2d_primitives(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_shell(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_compositesurface(double tol_planarity_d2p, double tol_planarity_normals);
  bool   validate_as_multisurface(double tol_planarity_d2p, double tol_planarity_normals);
  
private:
  int                             _id;
  vector<Point3>                  _lsPts;
  vector< vector< vector<int> > > _lsFaces;
  CgalPolyhedron*                 _polyhedron;
  vector< vector<int*> >          _lsTr;
  double                          _tol_snap;
  cbf                             _cb;
  int                             _is_valid;    //-1: not done yet; 0: nope; 1: yes it's valid
  int                             _is_valid_2d; //-1: not done yet; 0: nope; 1: yes it's valid

  bool triangulate_shell();
  bool construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
};


#endif /* defined(__val3dity__Shell__) */
