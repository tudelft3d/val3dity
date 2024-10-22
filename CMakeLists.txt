if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
  cmake_policy(SET CMP0011 NEW)
endif(COMMAND cmake_policy)

cmake_minimum_required (VERSION 3.16)
project( val3dity )

option(VAL3DITY_LIBRARY "Build val3dity as a library instead of an executable." OFF)
option(VAL3DITY_USE_INTERNAL_DEPS "Use the thirdparty dir that ship with val3dity (for pugixml, nlohmann-json, spdlog and tclap). Turn off in case you want to provide these dependencies yourself." ON)

add_definitions(-std=c++17)

set( CMAKE_BUILD_TYPE "Release")
set( CMAKE_CXX_FLAGS "-O2" )

set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()

if (MSVC)
    add_definitions("/EHsc")
endif(MSVC)

# CGAL
find_package( CGAL QUIET COMPONENTS )
if ( CGAL_FOUND )
  message(STATUS "CGAL found")
  message(STATUS ${CGAL_LIBRARIES})
  message(STATUS ${CGAL_3RD_PARTY_LIBRARIES})
else()
  message(SEND_ERROR "val3dity requires the CGAL library")
  return()  
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Eigen
find_package(Eigen3 3.1.0 QUIET)
include(CGAL_Eigen3_support)


# Boost
find_package( Boost REQUIRED COMPONENTS filesystem)

if ( NOT Boost_FOUND )
  message( SEND_ERROR "val3dity requires the Boost library" )
  return()  
endif()

# GEOS
find_package( GEOS CONFIG REQUIRED )
if ( GEOS_FOUND )
    get_target_property(GEOS_LOCATION GEOS::geos_c LOCATION)
    message( STATUS "Found GEOS: ${GEOS_LOCATION}" )
else()
  message( SEND_ERROR "val3dity requires the GEOS library" )
endif()

if ( VAL3DITY_USE_INTERNAL_DEPS )
  message(STATUS "Using internal dependencies")

  FILE(GLOB_RECURSE THIRDPARTY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/*.cpp)
  add_library(val3dity_thirdparty STATIC ${THIRDPARTY})
  target_include_directories(val3dity_thirdparty PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/pugixml)
  set_property(TARGET val3dity_thirdparty PROPERTY POSITION_INDEPENDENT_CODE ON)
else()
  message(STATUS "Using external dependencies")
  # nlohmann
  find_package(nlohmann_json CONFIG REQUIRED)
  # spdlog
  find_package(spdlog CONFIG REQUIRED)
  # pugixml
  find_package(pugixml CONFIG REQUIRED)
  
  # Find TCLAP's include path using find_path (tclap provides no cmake target)
  find_path(TCLAP_INCLUDE_DIR "tclap/CmdLine.h")

  if (TCLAP_INCLUDE_DIR)
      message(STATUS "Found TCLAP: ${TCLAP_INCLUDE_DIR}")
  else()
      message(FATAL_ERROR "TCLAP not found. Make sure it is installed via eg. vcpkg.")
  endif()
endif()

# Create an object file for the stuff that is shared between library and executable
FILE(GLOB SRC_FILES src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/val3dity.cpp)

add_library(val3dity_core OBJECT ${SRC_FILES})

target_link_libraries(val3dity_core 
  PUBLIC
  CGAL::CGAL
  PRIVATE
  CGAL::Eigen3_support
  GEOS::geos_c 
)
if ( VAL3DITY_USE_INTERNAL_DEPS )
  target_link_libraries(val3dity_core PUBLIC val3dity_thirdparty)
else()
  target_link_libraries(val3dity_core PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog PRIVATE pugixml::static)
endif()

if ( VAL3DITY_LIBRARY )
  message(STATUS "Building val3dity library")
  
  add_library(val3dity STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/val3dity.cpp)
  target_include_directories(val3dity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
  target_link_libraries(val3dity PUBLIC val3dity_core)
  set_property(TARGET val3dity PROPERTY POSITION_INDEPENDENT_CODE ON)
else()
  message(STATUS "Building val3dity executable")
  add_executable(val3dity ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
  target_link_libraries(val3dity PRIVATE val3dity_core Boost::filesystem)
  install(TARGETS val3dity DESTINATION bin)

  if ( NOT VAL3DITY_USE_INTERNAL_DEPS )
    target_include_directories(val3dity PRIVATE ${TCLAP_INCLUDE_DIR})
  endif()
endif()