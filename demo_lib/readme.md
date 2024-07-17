
# Use val3dity as a library in your C++ code

This demonstrate how to use val3dity as a library, the file `main.cpp` shows all the possibilities.


## How to use val3dity as a library in your code

The API of the library is `val3dity.h`, you need to include the file in your source.

Also, the functions to validate take as input and return as output [nlohmann JSON objects](https://github.com/nlohmann/json), so you need to include this library. 
There is however no need to include or link to nlohmann JSON yourself, the cmake reuses that of val3dity.

The API reads `const char*` for XML data ([IndoorGML](http://indoorgml.net/) input), because I don't want to enforce a specific XML library.


```cpp
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
  //-- read a CityJSON file
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
  //-- validate it
  try {
    json re = val3dity::validate(j, val3dity::Parameters().tol_snap(0.01).planarity_d2p_tol(0.04));
    // bool re = val3dity::is_valid(j); 
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return 0;
}
```


## How to compile main.cpp?

1. modify `CMakeLists.txt` to ensure that `add_subdirectory` (line 9) points to where you have the root folder of val3dity (in this demo it's the parent directory). Use an absolute path, and not a relative one!
1. `mkdir build && cd build`
1. `cmake .. -DVAL3DITY_LIBRARY=true`
1. `make`
1. `./myprogram`


## Parameters

The parameters of val3dity can be setup by passing them to the functions `is_valid()` or `validate()`, this is an example:

```cpp
  json re = val3dity::validate(j, val3dity::Parameters().tol_snap(0.01).planarity_d2p_tol(0.04));
```

Those 5 parameters can be setup and you can see their default values:

```cpp
  double      tol_snap = 0.001;
  double      planarity_d2p_tol = 0.01;
  double      planarity_n_tol = 20.0;
  double      overlap_tol = -1.0;
  Primitive3D primitive = SOLID;
```

The `Primitive3D` is used when validating formats for which the primitive to use is unclear, eg OBJ, OFF, and when using std::vector and std::array (see below).
The 3 options are: `Solid` (default), `MultiSurface`, and `CompositeSurface`.


## Input accepted

  - [CityJSON](http://www.cityjson.org)
  - [CityJSON Sequences (CityJSONSeq)](https://www.cityjson.org/cityjsonseq/)
  - [tu3djson](https://github.com/tudelft3d/tu3djson)
  - [JSON-FG (OGC Features and Geometries JSON)](https://github.com/opengeospatial/ogc-feat-geo-json)
  - [OBJ](https://en.wikipedia.org/wiki/Wavefront_.obj_file)
  - [OFF](https://en.wikipedia.org/wiki/OFF_(file_format))
  - [IndoorGML](http://indoorgml.net/)
  - arrays of points and faces (also with holes/inner-rings)

To use arrays of vertices and faces (basically the same structure as an OFF file (0-indexed vertices)), see that example:

```cpp
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
  //-- add 6 faces (watch out: 0-indexed!)
  std::vector<std::vector<int>> faces;
  faces.push_back({0, 3, 2, 1});
  faces.push_back({4, 5, 6, 7});
  faces.push_back({0, 1, 5, 4});
  faces.push_back({1, 2, 6, 5});
  faces.push_back({2, 3, 7, 6});
  faces.push_back({3, 0, 4, 7});
  //-- validate it
  try {
    bool re = val3dity::is_valid(pts, faces, val3dity::Parameters().primitive(val3dity::MULTISURFACE));
    std::cout << re << std::endl;
  }
  catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
```

