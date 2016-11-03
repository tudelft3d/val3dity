//
//  CompositeSolid.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef CompositeSolid_h
#define CompositeSolid_h

#include "Primitive.h"
#include "Solid.h"

#include <vector>
#include <string>


class CompositeSolid : public Primitive 
{
public:
                CompositeSolid(std::string id = ""); 
                ~CompositeSolid(); 

  bool          validate(double tol_planarity_d2p, double tol_planarity_normals);
  int           is_valid();
  bool          is_empty();
  std::string   get_report_xml();
  std::string   get_type();

  bool          add_solid(Solid* s);
  int           num_solids();

protected:
  std::vector<Solid*> _lsSolids;
};


#endif /* CompositeSolid_h */
