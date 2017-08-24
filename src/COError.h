//
//  COError.hpp
//  val3dity
//
//  Created by Hugo Ledoux on 17/08/2017.
//
//

#ifndef COError_hpp
#define COError_hpp


#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <fstream>

namespace val3dity
{

//-- City Object Errors
class COError {
  std::map<int, std::vector< std::tuple< std::string, std::string > > > _errors;
public:
  bool          has_errors();
  void          add_error(int code, std::string info, std::string whichgeoms);
  std::string   get_report_text();
  std::string   get_report_xml();
  std::set<int> get_unique_error_codes();
};

}

#endif /* COError_hpp */
