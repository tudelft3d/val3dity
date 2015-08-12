//
//  Shell.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Shell.h"

bool cmpPoint3(Point3 &p1, Point3 &p2, double tol)
{
  if ( (p1 == p2) || (CGAL::squared_distance(p1, p2) <= (tol * tol)) )
    return true;
  else
    return false;
}


Shell2::Shell2(bool oshell, double tol_snap)
{
  _is_oshell = oshell;
  _tol_snap = tol_snap;
}

bool Shell2::validate()
{
  return true;
}

int Shell2::add_point(Point3 p)
{
  int pos = -1;
  int cur = 0;
  for (auto &itr : _lsPts)
  {
    // std::cout << "---" << itr << std::endl;
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


Shell2::~Shell2()
{
  // TODO: clear memory properly
  _lsPts.clear();
  
}


bool Shell2::is_outer()
{
  return _is_oshell;
}
