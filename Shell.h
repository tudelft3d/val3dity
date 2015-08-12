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
  Shell2(bool outershell = true);
  ~Shell2();
  
  int add_point(Point3 p);

  vector<Point3>& get_lsPts();

  bool is_outer();
  bool    validate();
  
private:
  vector<Point3> _lsPts;  
  bool _is_oshell;
};


#endif /* defined(__val3dity__Shell__) */
