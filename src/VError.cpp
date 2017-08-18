//
//  VError.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 17/08/2017.
//
//

#include "VError.h"
#include "input.h"

using namespace std;

namespace val3dity
{


bool VError::has_errors()
{
  if (_errors.size() == 0)
    return false;
  else
    return true;
}


void VError::add_error(int code, std::string info, std::string whichgeoms) 
{
  std::tuple<std::string, std::string> a(info, whichgeoms);
  _errors[code].push_back(a);
  std::clog << "ERROR " << code << " : " << info << std::endl;
}


std::string VError::get_report_text()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<info>" << std::get<0>(e) << "</info>" << std::endl;
      ss << "\t\t\t<primitives>" << std::get<1>(e) << "</primitives>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  return ss.str();
}


std::string VError::get_report_xml()
{
  std::stringstream ss;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      ss << "\t\t<Error>" << std::endl;
      ss << "\t\t\t<code>" << std::get<0>(err) << "</code>" << std::endl;
      ss << "\t\t\t<type>" << errorcode2description(std::get<0>(err)) << "</type>" << std::endl;
      ss << "\t\t\t<info>" << std::get<0>(e) << "</info>" << std::endl;
      ss << "\t\t\t<primitives>" << std::get<1>(e) << "</primitives>" << std::endl;
      ss << "\t\t</Error>" << std::endl;
    }
  }
  return ss.str();
}

}