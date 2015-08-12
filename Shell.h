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

class Shell2
{
public:
  Shell2(bool outershell, double tol_snap);
  ~Shell2();
  
  int number_points();
  int add_point(Point3 p);
  void add_face(vector< vector<int> > f);

  vector<Point3>& get_lsPts();

  bool            is_outer();
  bool            validate();
  
private:
  vector<Point3>                  _lsPts;
  vector< vector< vector<int> > > _lsFaces;
  bool                            _is_oshell;
  double                          _tol_snap;
};


#endif /* defined(__val3dity__Shell__) */
