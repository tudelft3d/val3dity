//
//  COError.cpp
//  val3dity
//
//  Created by Hugo Ledoux on 17/08/2017.
//
//

#include "COError.h"
#include "input.h"

using namespace std;

namespace val3dity
{


bool COError::has_errors()
{
  if (_errors.size() == 0)
    return false;
  else
    return true;
}

std::set<int> COError::get_unique_error_codes()
{
  std::set<int> errs;
  for (auto& err : _errors)
    for (auto i : err.second)
      errs.insert(std::get<0>(err));
  return errs;
}


void COError::add_error(int code, std::string info, std::string whichgeoms) 
{
  std::tuple<std::string, std::string> a(info, whichgeoms);
  _errors[code].push_back(a);
  std::clog << "ERROR " << code << " : " << info << std::endl;
}


std::string COError::get_report_text()
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


json COError::get_report_json()
{
  json j;
  for (auto& err : _errors)
  {
    for (auto& e : _errors[std::get<0>(err)])
    {
      json jj;
      jj["type"] = "Error";
      jj["code"] = std::get<0>(err);
      jj["description"] = errorcode2description(std::get<0>(err));
      jj["id"] = std::get<0>(e);
      jj["info"] = std::get<1>(e);
      j["errors"].push_back(jj);
    }
  }
  return j;
}


std::string COError::get_report_xml()
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