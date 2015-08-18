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
  Solid(cbf cb);
  ~Solid();
  
  Shell2*   get_oshell();
  void      set_oshell(Shell2* sh);
  Shell2*   get_ishell(int i);
  void      add_ishell(Shell2* sh);
  int       num_ishells();
  
  bool      validate();

  static int  _counter;
  std::string get_id();
  void        set_id(std::string id);
private:
  std::string    _id;
  Shell2*         _oshell;
  vector<Shell2*> _ishells;
};


#endif /* defined(__val3dity__Solid__) */
