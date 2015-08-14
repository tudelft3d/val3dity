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
#include "geomtools.h"

class Shell2
{
public:
  Shell2  (int id, double tol_snap, cbf cb);
  ~Shell2 ();
  
  int     number_points();
  int     number_faces();
  bool    is_outer();
  
  int     add_point(Point3 p);
  void    add_face(vector< vector<int> > f);


  bool            validate();
  bool            validate_2d_primitives();
  bool            validate_as_shell();
  bool            validate_as_compositesurface();
  bool            validate_as_multisurface();
  
  // vector<Point3>& get_lsPts();

private:
  int                             _id;
  vector<Point3>                  _lsPts;
  vector< vector< vector<int> > > _lsFaces;
  vector< vector<int*> >          _lsTr;
  double                          _tol_snap;
  cbf                             _cb;

  bool triangulate_shell();
  bool create_polygon(const vector<int>& ids, Polygon &pgn, bool ccworient);
  bool construct_ct(const vector< vector<int> >& pgnids, const vector<Polygon>& lsRings, vector<int*>& oneface, int faceNum);
};


#endif /* defined(__val3dity__Shell__) */
