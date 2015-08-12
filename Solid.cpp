//
//  Solid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Solid.h"
#include "Shell.h"

Solid::Solid()
{
  _id = "";
}

Solid::Solid(std::string id)
{
  _id = id;
}

Solid::~Solid()
{
  
}

Shell* Solid::get_oshell()
{
  return _oshell;
}


void Solid::set_oshell(Shell sh)
{

}


Shell* Solid::get_ishell(int i)
{
  return _ishells[i];
}

void Solid::add_ishell(Shell sh)
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

std::string Solid::get_id()
{
  return _id;
}

void Solid::set_id(std::string id)
{
  _id = id;
}


