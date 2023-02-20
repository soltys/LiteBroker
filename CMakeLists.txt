# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.24)
project("SoltysBroker")

# Include sub-projects.
add_subdirectory("SoltysBrokerLib")
add_subdirectory("app")
