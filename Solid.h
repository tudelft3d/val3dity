//
//  Solid.h
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#ifndef __val3dity__Solid__
#define __val3dity__Solid__

#include "Shell.h"
#include "definitions.h"


class Solid
{
public:
  Solid();
  Solid(Shell* sh);
  ~Solid();
  
  Shell*                 get_oshell();
  void                   set_oshell(Shell* sh);
  Shell*                 get_ishell(int i);
  void                   add_ishell(Shell* sh);
  const vector<Shell*>&  get_shells();
  int                    num_ishells();
  
  bool          validate(Primitive3D prim, double tol_planarity_d2p, double tol_planarity_normals);
  std::string   get_report_xml();
  std::string   get_report_text();
  void          add_error(int code, int shell1, int Shell, std::string info);
  std::set<int> get_unique_error_codes();
  std::string   get_poly_representation();
  bool          is_valid();
  
  static int    _counter;
  std::string   get_id();
  void          set_id(std::string id);
private:
  std::string     _id;
  vector<Shell*>  _shells;
  int             _is_valid;

  bool validate_solid_with_nef();
};


#endif /* defined(__val3dity__Solid__) */
