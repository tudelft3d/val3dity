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
#include "val3dity_defs.h"

class Solid
{
public:
  Solid();
  Solid(std::string id);
  ~Solid();
  Shell&  get_oshell();
  void set_oshell(Shell sh);
  Shell&  get_ishell(int i);
  void add_ishell(Shell sh);
  int     num_ishells();
  std::string get_id();
  void set_id(std::string id);
  bool    validate();
  
private:
  std::string   _id;
  Shell         _oshell;
  vector<Shell> _ishells;
};


#endif /* defined(__val3dity__Solid__) */
