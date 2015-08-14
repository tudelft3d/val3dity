//
//  geomtools.h
//  val3dity
//
//  Created by Hugo Ledoux on 14/08/15.
//
//

#ifndef __val3dity__geomtools__
#define __val3dity__geomtools__

#include <val3dity_defs.h>

bool    cmpPoint3(Point3 &p1, Point3 &p2, double tol);
int     projection_plane(const vector< Point3 > &lsPts, const vector<int> &ids);
Vector* polygon_normal(const vector< Point3 > &lsPts, const vector<int> &ids);


#endif /* defined(__val3dity__geomtools__) */
