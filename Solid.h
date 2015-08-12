//
//  Solid.h
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#ifndef __val3dity__Solid__
#define __val3dity__Solid__

#include "val3dity_defs.h"
#include "Shell.h"

class Solid
{
public:
  Solid();
  ~Solid();
  bool    validate();
  Shell&  get_oshell();
  Shell&  get_ishell(int i);
  int     num_ishells();
  
private:
  std::string   _id;
  Shell         _oshell;
  vector<Shell> _ishells;
};


#endif /* defined(__val3dity__Solid__) */
