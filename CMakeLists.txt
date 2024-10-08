if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
  cmake_policy(SET CMP0011 NEW)
endif(COMMAND cmake_policy)

cmake_minimum_required (VERSION 3.16)
project( val3dity )


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

#include_directories( ${GEOS_INCLUDE_DIR} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty )

FILE(GLOB_RECURSE THIRDPARTY thirdparty/*.cpp)
add_library(val3dity_thirdparty STATIC ${THIRDPARTY})

FILE(GLOB SRC_FILES src/*.cpp)

if ( VAL3DITY_LIBRARY )
  message(STATUS "Building val3dity library")
  list(REMOVE_ITEM SRC_FILES src/main.cpp)
  add_library(val3dity STATIC ${SRC_FILES})
  target_include_directories(val3dity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)
  set_property(TARGET val3dity_thirdparty PROPERTY POSITION_INDEPENDENT_CODE ON)
  set_property(TARGET val3dity PROPERTY POSITION_INDEPENDENT_CODE ON)
else()
  message(STATUS "Building val3dity executable")
  list(REMOVE_ITEM SRC_FILES src/val3dity.cpp)
  add_executable(val3dity ${SRC_FILES})
endif()

target_link_libraries(val3dity CGAL::CGAL CGAL::Eigen3_support GEOS::geos_c val3dity_thirdparty Boost::filesystem)

install(TARGETS val3dity DESTINATION bin)
