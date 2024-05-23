
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

void arrays_demo();
void arrays_w_holes_demo();
void cityjson_demo();
void cityjsonfeature_demo();
void indoorgml_demo();
void jsonfg_demo();
void obj_demo();
void off_demo();
void onegeom_demo();
void tu3djson_demo();

int main(int argc, char *argv[])
{
  arrays_demo();
  // arrays_w_holes_demo();
  // cityjson_demo();
  // cityjsonfeature_demo();
  // indoorgml_demo();
  // jsonfg_demo();
  // obj_demo();
  // off_demo();
  // onegeom_demo();
  // tu3djson_demo();
  return 0;
}


void arrays_demo() 
{
  std::cout << "\n=== arrays_demo() ===" << std::endl;
  //-- add 8 corners of a cube
  std::vector<std::array<double, 3>> pts;
  pts.push_back({0.0, 0.0, 0.0});
  pts.push_back({1.0, 0.0, 0.0});
  pts.push_back({1.0, 1.0, 0.0});
  pts.push_back({0.0, 1.0, 0.0});
  pts.push_back({0.0, 0.0, 1.0});
  pts.push_back({1.0, 0.0, 1.0});
  pts.push_back({1.0, 1.0, 1.0});
  pts.push_back({0.0, 1.0, 1.0});
  //-- add faces
  std::vector<std::vector<int>> faces;
  faces.push_back({0, 3, 2, 1});
  faces.push_back({4, 5, 6, 7});
  faces.push_back({0, 1, 5, 4});
  faces.push_back({1, 2, 6, 5});
  faces.push_back({2, 3, 7, 6});
  // faces.push_back({3, 0, 4, 7});
  //-- validate it
  try {
    json re = val3dity::validate(pts, faces, val3dity::Parameters().primitive(val3dity::SOLID));
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void arrays_w_holes_demo() 
{
  std::cout << "\n=== arrays_w_holes_demo() ===" << std::endl;
  //-- add vertices for a cubic torus (with a triangular prism handle)
  std::vector<std::array<double, 3>> pts;
  pts.push_back({0.0, 0.0, 0.0});
  pts.push_back({1.0, 0.0, 0.0});
  pts.push_back({1.0, 1.0, 0.0});
  pts.push_back({0.0, 1.0, 0.0});
  pts.push_back({0.0, 0.0, 1.0});
  pts.push_back({1.0, 0.0, 1.0});
  pts.push_back({1.0, 1.0, 1.0});
  pts.push_back({0.0, 1.0, 1.0});
  pts.push_back({0.2, 0.2, 1.0});
  pts.push_back({0.8, 0.2, 1.0});
  pts.push_back({0.5, 0.5, 1.0});
  pts.push_back({0.2, 0.2, 0.0});
  pts.push_back({0.8, 0.2, 0.0});
  pts.push_back({0.5, 0.5, 0.0});
  //-- add faces
  std::vector<std::vector<std::vector<int>>> faces_w_holes;
  faces_w_holes.push_back({{0, 3, 2, 1}, {11, 12, 13}});
  faces_w_holes.push_back({{4, 5, 6, 7}, {8, 10, 9}});
  faces_w_holes.push_back({{0, 1, 5, 4}});
  faces_w_holes.push_back({{1, 2, 6, 5}});
  faces_w_holes.push_back({{2, 3, 7, 6}});
  faces_w_holes.push_back({{3, 0, 4, 7}});
  //-- side interior walls
  faces_w_holes.push_back({{8, 9, 12, 11}});
  faces_w_holes.push_back({{13, 12, 9, 10}});
  faces_w_holes.push_back({{10, 8, 11, 13}});
  //-- validate it
  try {
    // json re = val3dity::validate(pts, faces_w_holes);
    bool re = val3dity::is_valid(pts, faces_w_holes);
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void obj_demo() 
{
  std::cout << "\n=== obj_demo() ===" << std::endl;
  std::stringstream buffer;
  buffer << std::ifstream("../../data/obj/duplicatevertices.obj").rdbuf();
  try {
    std::string s = buffer.str();
    bool re = val3dity::is_valid(s, "OBJ");
    if (re == true)
      std::cout << "VALID!" << std::endl;
    else
      std::cout << "INVALID :(" << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void off_demo() 
{
  std::cout << "\n=== off_demo() ===" << std::endl;
  std::stringstream buffer;
  buffer << std::ifstream("../../data/test_valid/basecube.off").rdbuf();
  try {
    std::string s = buffer.str();
    bool re = val3dity::is_valid(s, "OFF");
    if (re == true)
      std::cout << "VALID!" << std::endl;
    else
      std::cout << "INVALID :(" << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void cityjson_demo() 
{
  std::cout << "\n=== cityjson_demo() ===" << std::endl;
  std::ifstream input("../../data/cityjson/cube.json");
  json j;
  //-- deserialise the file
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  //-- validate it
  try {
    json re = val3dity::validate(j, val3dity::Parameters().tol_snap(0.01).planarity_d2p_tol(0.04));
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void cityjsonfeature_demo() {
  std::cout << "\n=== cityjsonfeature_demo() ===" << std::endl;
  std::string input("../../data/test_cityjsonl/denhaag_random_5.jsonl");
  std::ifstream infile(input.c_str(), std::ifstream::in);
  if (!infile)
    return;
  //-- transform
  json jtransform;
  std::string l;
  int linecount = 1;
  while (std::getline(infile, l)) 
  {
    std::istringstream iss(l);
    json j;
    try {
      iss >> j;
    }
    catch (nlohmann::detail::parse_error e) {
      break;
    }
    if (j["type"] == "CityJSON") {
      jtransform = j["transform"];
    }
    if (j["type"] == "CityJSONFeature") {
      try {
        //-- you have to add the "transform" property so that the coordinates can be calculated
        j["transform"] = jtransform;
        bool re = val3dity::is_valid(j);
        std::cout << "Input line #" << linecount << " is " << re << std::endl;
      }
      catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
      }
    }
    linecount++;
  }
}


void jsonfg_demo() 
{
  std::cout << "\n=== jsonfg_demo() ===" << std::endl;
  std::ifstream input("../../data/test_jsonfg/building.fg.json");
  // std::ifstream input("../../data/test_jsonfg/cubes.fg.json");
  json j;
  //-- deserialise the file
  try 
  {
    input >> j;
  }
  catch (nlohmann::detail::parse_error e) 
  {
    std::cerr << "Input file not a valid JSON file." << std::endl;
    return;
  }
  //-- validate it
  try {
    bool re = val3dity::is_valid(j);
    std::cout << "Input file is " << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}

void tu3djson_demo() 
{
  std::cout << "\n=== tu3djson_demo() ===" << std::endl;
  std::ifstream input("../../data/test_tu3djson/cube3.json");
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
  try {
    std::cout <<  val3dity::validate(j) << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
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
  // std::cout << onegeom << std::endl;
  try {
    bool re = val3dity::is_valid(onegeom);
    std::cout << "Input file is " << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}


void indoorgml_demo() 
{
  std::cout << "\n=== indoorgml_demo() ===" << std::endl;
  std::stringstream buffer;
  buffer << std::ifstream("../../data/gml/FZK-Haus_full.gml").rdbuf();
  try {
    std::string s = buffer.str();
    bool re = val3dity::is_valid(s, "IndoorGML");
    if (re == true)
      std::cout << "VALID!" << std::endl;
    else
      std::cout << "INVALID :(" << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
}
