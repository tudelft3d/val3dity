//
//  Primitive.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 25/10/16.
//
//

#include "Primitive.h"


Primitive::Primitive() {
  _id_building = "";
  _id_buildingpart = "";
}


std::string Primitive::get_id_building()
{
  return _id_building;
}

void Primitive::set_id_building(std::string id)
{
  _id_building = id;
}

std::string Primitive::get_id_buildingpart()
{
  return _id_buildingpart;
}

void Primitive::set_id_buildingpart(std::string id)
{
  _id_buildingpart = id;
}
