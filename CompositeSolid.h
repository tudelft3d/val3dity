//
//  CompositeSolid.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef CompositeSolid_h
#define CompositeSolid_h

#include "definitions.h"
#include "Primitive.h"
#include "Solid.h"

class CompositeSolid : public Primitive 
{
public:
                CompositeSolid(); 

  bool          validate(double tol_planarity_d2p, double tol_planarity_normals);
  std::string   get_report_xml();
  bool          is_valid();
  bool          is_empty();
  std::set<int> get_unique_error_codes();

  bool          add_solid(Solid* s);
  int           num_solids();

protected:
  std::vector<Solid*> _lsSolids;
};


#endif /* CompositeSolid_h */