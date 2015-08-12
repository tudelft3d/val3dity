//
//  Shell.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Shell.h"


Shell2::Shell2(bool oshell)
{
  _is_oshell = oshell;
}

bool Shell2::validate()
{
  return true;
}

int Shell2::add_point(Point3 p)
{
  _lsPts.push_back(p);
}


Shell2::~Shell2()
{
  // TODO: clear memory properly
  _lsPts.clear();
  
}


bool Shell2::is_outer()
{
  return _is_oshell;
}
