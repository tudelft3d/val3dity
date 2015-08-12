//
//  Solid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Solid.h"


Solid::Solid()
{
}

Solid::~Solid()
{
  
}

bool Solid::validate()
{
  std::cout << "I'm validating the solid" << std::endl;
  return true;
}

int Solid::num_ishells()
{
  return _ishells.size();
}
  


