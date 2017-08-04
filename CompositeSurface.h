//
//  CompositeSurface.h
//  val3dity
//
//  Created by Hugo Ledoux on 2017-04-25
//
//

#ifndef CompositeSurface_h
#define CompositeSurface_h

#include "Primitive.h"
#include "Surface.h"

#include <string>

namespace val3dity
{

class CompositeSurface : public Primitive 
{
public:
              CompositeSurface(std::string id = ""); 
              ~CompositeSurface(); 

  bool        validate(double tol_planarity_d2p, double tol_planarity_normals, double tol_overlap = -1);
  int         is_valid();
  bool        is_empty();
  std::string get_report_xml();
  Primitive3D get_type();

  void          get_min_bbox(double& x, double& y);
  void          translate_vertices(double minx, double miny);

  int           number_faces();
  bool          set_surface(Surface* s);
  Surface*      get_surface();
  std::set<int> get_unique_error_codes();

protected:
  Surface* _surface;
};

} // namespace val3dity

#endif /* CompositeSurface_h */
