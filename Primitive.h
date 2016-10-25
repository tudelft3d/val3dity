//
//  Primitive.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef Primitive_h
#define Primitive_h

#include "definitions.h"

class Primitive
{
public:
  Primitive  ();
  ~Primitive ();

  virtual bool          validate(double tol_planarity_d2p, double tol_planarity_normals) = 0;
  virtual bool          is_valid() = 0;
  virtual bool          is_empty() = 0;
  virtual std::string   get_report_xml() = 0;
  // virtual void          translate_vertices() = 0;

  std::string           get_id_building();
  void                  set_id_building(std::string id);
  std::string           get_id_buildingpart();
  void                  set_id_buildingpart(std::string id);

protected:

  std::string     _id_building;
  std::string     _id_buildingpart;
};


#endif /* Primitive_h */
