/*
  val3dity 

  Copyright (c) 2011-2017, 3D geoinformation research group, TU Delft  

  This file is part of val3dity.

  val3dity is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  val3dity is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with val3dity.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of val3dity, contact
  Hugo Ledoux
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/

#ifndef COError_hpp
#define COError_hpp


#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <fstream>
#include "nlohmann-json/json.hpp"

using json = nlohmann::json;

namespace val3dity
{

//-- City Object Errors
class COError {
  std::map<int, std::vector< std::tuple< std::string, std::string > > > _errors;
public:
  bool          has_errors();
  void          add_error(int code, std::string info, std::string whichgeoms);
  std::string   get_report_text();
  json          get_report_json();
  std::string   get_report_xml();
  std::set<int> get_unique_error_codes();
};

}

#endif /* COError_hpp */
