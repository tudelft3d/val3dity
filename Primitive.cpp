//
//  Primitive.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "Primitive.h"
#include "input.h"
#include <iostream>

Primitive::Primitive() {
}

Primitive::~Primitive() {
}

std::string  Primitive::get_id()
{
  return _id;
}

void Primitive::set_id(std::string id)
{
  _id = id;
}

void Primitive::add_error(int code, std::string whichgeoms, std::string info)
{
  _is_valid = 0;
  std::tuple<std::string, std::string> a(whichgeoms, info);
  _errors[code].push_back(a);
  std::clog << "\tERROR " << code << ": " << errorcode2description(code);
  if (whichgeoms.empty() == false)
    std::clog << " (id: " << whichgeoms << ")";
  std::clog << std::endl;
  if (info.empty() == false)
    std::clog << "\t[" << info << "]" << std::endl;

}

std::set<int> Primitive::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
  {
    errs.insert(std::get<0>(err));
  }
  return errs;
}



