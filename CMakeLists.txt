
project( val3dity )

cmake_minimum_required (VERSION 3.2)

add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS "-O2")

set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()

# CGAL
find_package( CGAL QUIET COMPONENTS core )
if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )
  message(STATUS "CGAL found")
  message(STATUS ${CGAL_LIBRARIES})
  message(STATUS ${CGAL_3RD_PARTY_LIBRARIES})
else()
  message(SEND_ERROR "val3dity requires the CGAL library")
  return()  
endif()

# Eigen
find_package(Eigen3)
include( ${EIGEN3_USE_FILE} )  

# Boost
find_package( Boost REQUIRED COMPONENTS filesystem)

if ( NOT Boost_FOUND )
  message(SEND_ERROR "val3dity requires the Boost library")
  return()  
endif()

# GEOS
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package( GEOS )
if ( NOT GEOS_FOUND )
  message(SEND_ERROR "val3dity requires the GEOS library")
endif()

include_directories( ${GEOS_INCLUDE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/thirdparty )

FILE(GLOB_RECURSE THIRDPARTY thirdparty/*.cpp)
add_library(thirdparty STATIC ${THIRDPARTY})

FILE(GLOB SRC_FILES src/*.cpp)
add_executable(val3dity ${SRC_FILES})

# add_to_cached_list( CGAL_EXECUTABLE_TARGETS val3dity )

target_link_libraries(val3dity ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} ${GEOS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} thirdparty)

install(TARGETS val3dity DESTINATION bin)
