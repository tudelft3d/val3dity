//
//  Solid.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 12/08/15.
//
//

#include "Solid.h"
#include "Shell.h"

int Solid::_counter = 1;

Solid::Solid(cbf cb)
{
  _id = std::to_string(_counter);
  _counter++;
}


Solid::~Solid()
{
  // TODO: destructor for Solid, memory-management jongens
}

Shell2* Solid::get_oshell()
{
  return _oshell;
}


void Solid::set_oshell(Shell2* sh)
{
  _oshell = sh;
}


Shell2* Solid::get_ishell(int i)
{
  return _ishells[i];
}

void Solid::add_ishell(Shell2* sh)
{
  _ishells.push_back(sh);
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

void Solid::add_error(int code, int shell1, int shell2, std::string info)
{
  // TODO: how to store these errors? shell-shell numbers?
  // std::pair<int, std::string> a(faceid, info);
  // _errors[code].push_back(a);
  // std::clog << "--> errors #" << code << " for Shell " << this->_id << std::endl;
}


