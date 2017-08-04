
cmake_minimum_required (VERSION 3.2)

project( val3dity )

add_definitions(-std=c++11)

set( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true )
 
if ( COMMAND cmake_policy )
  cmake_policy( SET CMP0003 NEW )  
endif()

# CGAL
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )
  message(SEND_ERROR "val3dity requires the CGAL library")
  return()  
endif()

# include helper file
include( ${CGAL_USE_FILE} )

# Boost
find_package( Boost REQUIRED )

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

include_directories( ${GEOS_INCLUDE_DIR}, ${CMAKE_SOURCE_DIR}/thirdparty/pugixml )

FILE(GLOB_RECURSE THIRDPARTY thirdparty/*.cpp)
add_library(thirdparty STATIC ${THIRDPARTY})


file(GLOB SRC_FILES src/*.cpp)
add_executable(val3dity ${SRC_FILES})

add_to_cached_list( CGAL_EXECUTABLE_TARGETS val3dity )

# Link the executable to CGAL and third-party libraries
target_link_libraries(val3dity ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} ${GEOS_LIBRARY} thirdparty)

# Have the option to properly install val3dity to the system 
install(TARGETS val3dity DESTINATION bin)
