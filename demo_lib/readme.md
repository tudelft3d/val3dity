
## how to use val3dity as a library in your code

The API of the library is `val3dity.h`, you need to include the file in your source.

Also, the functions to validate read/return [nlohmann JSON objects](https://github.com/nlohmann/json), so you need to use this library. 
There is however no need to include or link to nlohmann JSON yourself, the cmake reuses that of val3dity.

```cpp
#include "val3dity.h" 
#include "nlohmann-json/json.hpp"

#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[])
{
  json j;
  // define j as a tu3djson object, see https://github.com/tudelft3d/tu3djson

  std::vector<bool> re = val3dity::validate_tu3djson(j);
  std::for_each(re.begin(), re.end(), [](const bool n) { std::cout << n << std::endl; });
   
  return 0;
}
```



## to compile

1. modify `CMakeLists.txt` to ensure that `add_subdirectory` (line 9) points to where you have the root folder of val3dity (in this demo it's the parent directory)
1. `mkdir build && cd build`
1. `cmake -DLIBRARY=true`
1. `./myprogram`