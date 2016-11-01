//
//  Primitive.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#ifndef Primitive_h
#define Primitive_h


#include <map>
#include <vector>
#include <set>
#include <string>


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

  std::string           get_id();
  void                  set_id(std::string id);
  void                  add_error(int code, std::string whichgeoms, std::string info);
  std::set<int>         get_unique_error_codes();

protected:
  std::string   _id;
  int           _is_valid; 

  std::map<int, std::vector< std::tuple< std::string, std::string > > > _errors;

};


#endif /* Primitive_h */
