//
//  MultiSurface.h
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef MultiSurface_h
#define MultiSurface_h

// #include "definitions.h"
#include "Primitive.h"
#include "Surface.h"

#include <string>

namespace val3dity
{

class MultiSurface : public Primitive 
{
public:
              MultiSurface(std::string id = ""); 
              ~MultiSurface(); 

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

#endif /* MultiSurface_h */
