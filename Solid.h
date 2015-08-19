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
  Solid(Shell2* sh);
  ~Solid();
  
  Shell2*                 get_oshell();
  void                    set_oshell(Shell2* sh);
  Shell2*                 get_ishell(int i);
  void                    add_ishell(Shell2* sh);
  const vector<Shell2*>&  get_shells();
  int                     num_ishells();
  
  bool        validate(double tol_planarity_d2p, double tol_planarity_normals);
  void        add_error(int code, int shell1, int shell2, std::string info);

  static int  _counter;
  std::string get_id();
  void        set_id(std::string id);
  bool        is_valid();
private:
  std::string     _id;
  vector<Shell2*> _shells;
  int             _is_valid;
  // std::map<int, vector<std::pair<int, std::string> > > _errors;

  bool validate_solid_with_nef();
};


#endif /* defined(__val3dity__Solid__) */
