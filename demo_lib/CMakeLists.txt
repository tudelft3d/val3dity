cmake_minimum_required (VERSION 3.16)

project (myprogram)

add_definitions(-std=c++14)
set (CMAKE_BUILD_TYPE "Release")
set( CMAKE_CXX_FLAGS "-O2" )

add_executable (myprogram main.cpp)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../ build)
# add_subdirectory (/home/elvis/code/val3dity/ build)

target_link_libraries (myprogram LINK_PUBLIC val3dity)