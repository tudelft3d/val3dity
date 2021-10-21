
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>
#include <sstream>

using json = nlohmann::json;

void cityjson_demo();
void onegeom_demo();
void indoorgml_demo();

int main(int argc, char *argv[])
{
  cityjson_demo();
  onegeom_demo();
  indoorgml_demo();

  return 0;
}

void cityjson_demo() 
{
  std::cout << "\n=== cityjson_demo() ===" << std::endl;
  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  json jreport = val3dity::validate_cityjson(j);
  std::cout << "Input file is ";
  if (jreport["validity"])
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;
}


void onegeom_demo() 
{
  std::cout << "\n=== onegeom_demo() ===" << std::endl;
  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  json onegeom = j["CityObjects"]["id-1"]["geometry"][0];
  onegeom["vertices"] = j["vertices"];
  std::cout << onegeom << std::endl;
  bool re = val3dity::is_valid_onegeom(onegeom);
  if (re == true) 
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;
}


void indoorgml_demo() 
{
  std::cout << "\n=== indoorgml_demo() ===" << std::endl;
  std::stringstream buffer;
  buffer << std::ifstream("../../data/gml/FZK-Haus_full.gml").rdbuf();
  json jreport = val3dity::validate_indoorgml(buffer.str().c_str());

  std::cout << "Input file is ";
  if (jreport["validity"])
    std::cout << "VALID!" << std::endl;
  else
    std::cout << "INVALID :(" << std::endl;
}
