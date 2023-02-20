# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.9)

# Project Version
set(PROJECT_VERSION 1.0.0)

project("LiteBroker" VERSION ${PROJECT_VERSION})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory("tools")
add_subdirectory("thirdparty")

add_subdirectory("liteBroker")
add_subdirectory("app")
