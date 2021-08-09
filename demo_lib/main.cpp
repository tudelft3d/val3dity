
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[])
{

  // std::ifstream input("/Users/hugo/data/tu3djson/cube.json");
  std::ifstream input("/Users/hugo/data/cityjson/misc/cube.json");
  // std::ifstream input("/Users/hugo/data/cityjson/examples/delft/v100/a2.json");
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

  // if (j["type"] != "CityJSON") {
  //   std::cerr << "Input file not a valid JSON file." << std::endl;
  //   return 0;  
  // }
  
  json jr;
  // bool re = val3dity::validate_one_geom(j["features"][0]["geometry"], jr);
  // std::cout << jr << std::endl;

  // bool re = val3dity::validate_one_geom(j["features"][0]["geometry"]);
  // std::vector<bool> re = val3dity::validate_tu3djson(j);
  // std::vector<bool> re = val3dity::validate_tu3djson(j, jr);
  // std::cout << jr << std::endl;
  // std::ofstream o("/Users/hugo/temp/r.json");
  // o << jr.dump(2) << std::endl;
  // bool re = val3dity::validate_cityjson(j);
  bool re = val3dity::validate_cityjson(j, jr);

  // std::for_each(re.begin(), re.end(), [](const bool n) { std::cout << n << std::endl; });
  if (re == true)
    std::cout << "VALID" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;

  
  return 0;
}
