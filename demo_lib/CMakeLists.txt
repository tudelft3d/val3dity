cmake_minimum_required (VERSION 3.16)

project (testval3)

set( CMAKE_BUILD_TYPE "Release")

add_executable (main main.cpp)

add_subdirectory (/Users/hugo/projects/val3dity/ build)

target_link_libraries (main LINK_PUBLIC val3dity)