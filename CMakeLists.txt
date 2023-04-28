# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.9)

# Project Version
set(PROJECT_VERSION 1.0.0)

project("LiteBroker" VERSION ${PROJECT_VERSION})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mavx2 -march=x86-64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx -mavx2 -march=x86-64")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory("tools")
add_subdirectory("thirdparty")

add_subdirectory("liteBroker")
add_subdirectory("app")
