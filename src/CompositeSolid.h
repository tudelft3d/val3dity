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

namespace val3dity
{

class CompositeSolid : public Primitive 
{
public:
                CompositeSolid(std::string id = ""); 
                ~CompositeSolid(); 

  bool          validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap = -1);
  int           is_valid();
  bool          is_empty();
  std::string   get_report_xml();
  json          get_report_json();
  Primitive3D   get_type();
  std::set<int> get_unique_error_codes();

  void          get_min_bbox(double& x, double& y);
  void          translate_vertices(double minx, double miny);

  Nef_polyhedron* get_nef_polyhedron();

  bool          add_solid(Solid* s);
  int           number_of_solids();

protected:
  std::vector<Solid*> _lsSolids;
  Nef_polyhedron*     _nef;
};

} // namespace val3dity

#endif /* CompositeSolid_h */
