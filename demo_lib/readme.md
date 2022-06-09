
## how to use val3dity as a library in your code

The API of the library is `val3dity.h`, you need to include the file in your source.

Also, the functions to validate read/return [nlohmann JSON objects](https://github.com/nlohmann/json), so you need to include this library. 
There is however no need to include or link to nlohmann JSON yourself, the cmake reuses that of val3dity.

The API reads `const char*` for XML data ([IndoorGML](http://indoorgml.net/) input), because I don't want to enforce a specific XML library.


```cpp
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
  json j;
  // define j as a tu3djson object, see https://github.com/tudelft3d/tu3djson

  std::vector<bool> re = val3dity::is_valid_tu3djson_each(j);
  std::for_each(re.begin(), re.end(), [](const bool n) { std::cout << n << std::endl; });
   
  return 0;
}
```


## to compile

1. modify `CMakeLists.txt` to ensure that `add_subdirectory` (line 9) points to where you have the root folder of val3dity (in this demo it's the parent directory). Use an absolute path, and not a relative one!
1. `mkdir build && cd build`
1. `cmake .. -DLIBRARY=true`
1. `make`
1. `./myprogram`


## input accepted

1. one [CityJSON object](https://www.cityjson.org/specs/#cityjson-object)
2. one [tu3djson object](https://github.com/tudelft3d/tu3djson#tu3djson-object)
3. [one geometry of a tu3djson object](https://github.com/tudelft3d/tu3djson#geometry-object)
4. one [IndoorGML](http://indoorgml.net/) file (represented as a string)

## functions 

```cpp
bool 
is_valid_onegeom(json& j,
                 double tol_snap=0.001, 
                 double planarity_d2p_tol=0.01, 
                 double planarity_n_tol=20.0, 
                 double overlap_tol=-1.0);
  

json
validate_onegeom(json& j,
                 double tol_snap=0.001, 
                 double planarity_d2p_tol=0.01, 
                 double planarity_n_tol=20.0, 
                 double overlap_tol=-1.0);

bool 
is_valid_tu3djson(json& j,
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

std::vector<bool> 
is_valid_tu3djson_each(json& j,
                       double tol_snap=0.001, 
                       double planarity_d2p_tol=0.01, 
                       double planarity_n_tol=20.0, 
                       double overlap_tol=-1.0);

json
validate_tu3djson(json& j,
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

bool 
is_valid_cityjson(json& j, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

json
validate_cityjson(json& j, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

bool 
is_valid_indoorgml(const char* input, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);

json
validate_indoorgml(const char* input, 
                  double tol_snap=0.001, 
                  double planarity_d2p_tol=0.01, 
                  double planarity_n_tol=20.0, 
                  double overlap_tol=-1.0);
```