# AGENTS.md

## Build

```bash
mkdir build && cd build && cmake .. && make
```

Dependencies: CGAL 5.4+, Eigen, GEOS, Boost (filesystem), CMake 3.30+

On Linux, if CGAL from apt is too old, download CGAL manually and set `CGAL_DIR`:
```bash
export CGAL_DIR=/path/to/CGAL-5.6.1
```

## Test

```bash
# From repository root (not from tests/)
python -m pytest                    # basic tests
python -m pytest --runfull          # full test suite
python -m pytest -k "test_101"      # single test
python -m pytest --exe=/path/to/exe # custom binary path
```

Tests expect the binary at `./build/val3dity`. They use subprocess to invoke it.

## Architecture

- **Entry point**: `src/main.cpp` (CLI parsing with TCLAP, orchestration)
- **Core logic**: `src/input.cpp` (file parsing, report generation)
- **Validation**: `src/Feature.cpp`, `src/Primitive.cpp`, `src/Solid.cpp`, `src/Surface.cpp`
- **Data structures**: `src/definitions.h` (error codes, types, CGAL typedefs)

Error codes are numeric: 1xx (ring), 2xx (polygon), 3xx (shell), 4xx (solid), 5xx (composite), 6xx (cityobject), 7xx (indoorgml), 9xx (io/other).

## Code conventions

- C++17
- JSON: nlohmann/json (`using json = nlohmann::json`)
- CLI: TCLAP
- Logging: spdlog
- Geometry: CGAL
- Third-party libs bundled in `thirdparty/` (pugixml, nlohmann-json, spdlog, tclap)

## Gotchas

- Tests must run from repository root, not from `tests/` directory
- Version string is hardcoded in `src/main.cpp` as `VAL3DITY_VERSION`
- No separate lint/typecheck commands (C++ project)
- Building as library: `cmake .. -DVAL3DITY_LIBRARY=true`
- Gitflow branching model (main, develop, feature branches)
