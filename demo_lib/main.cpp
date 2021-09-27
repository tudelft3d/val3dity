
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[])
{

  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return 0;
  }
  
  json jreport = val3dity::validate_cityjson(j);
  std::cout << "Input file is ";
  if (jreport["validity"])
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;

  json onegeom = j["CityObjects"]["id-1"]["geometry"][0];
  onegeom["vertices"] = j["vertices"];
  // std::cout << onegeom << std::endl;
  bool re = val3dity::is_valid_onegeom(onegeom);
  if (re == true) 
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;
 
  return 0;
}
