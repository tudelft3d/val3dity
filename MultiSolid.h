//
//  MultiSolid.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef MultiSolid_h
#define MultiSolid_h

#include "Primitive.h"
#include "Solid.h"

#include <string>
#include <vector>


class MultiSolid : public Primitive 
{
public:
              MultiSolid(std::string id = ""); 
              ~MultiSolid(); 

  bool          validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap = -1);
  int           is_valid();
  bool          is_empty();
  std::string   get_report_xml();
  std::string   get_type();
  std::set<int> get_unique_error_codes();

  bool        add_solid(Solid* s);
  int         number_of_solids();

protected:
  std::vector<Solid*> _lsSolids;
};


#endif /* CompositeSolid_h */
