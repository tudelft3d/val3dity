
project( val3dity )

cmake_minimum_required(VERSION 2.6.2)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" VERSION_GREATER 2.6)
  if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
    cmake_policy(VERSION 2.8.4)
  else()
    cmake_policy(VERSION 2.6)
  endif()
endif()

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

# GDAL
set( GEOS_DIR .)
find_package( GEOS )

if ( NOT GEOS_FOUND )
  message(SEND_ERROR "val3dity requires the GEOS library")
endif()

include_directories( ${GEOS_INCLUDE_DIR}, include )


# Creating entries for target: val3dity
# ############################

add_executable( val3dity input.cpp pugixml.cpp geomtools.cpp Primitive.cpp Surface.cpp Solid.cpp CompositeSolid.cpp MultiSolid.cpp Surface.cpp MultiSurface.cpp validate_shell.cpp Building.cpp main.cpp )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS val3dity )

# Link the executable to CGAL and third-party libraries
target_link_libraries(val3dity ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} ${GEOS_LIBRARY})

# Have the option to properly install val3dity to the system 
install(TARGETS val3dity DESTINATION bin)
