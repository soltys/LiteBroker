# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.14...3.29)

include(FetchContent)

# Project Version
set(PROJECT_VERSION 0.0.10)

project("LiteBroker" VERSION ${PROJECT_VERSION})

if(WIN32)
	# Export all Symbols by default (on Windows creates '.lib'+ '.dll').
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#### START TOOLS
FetchContent_Declare(
  embed_resource
  GIT_REPOSITORY https://github.com/soltys/embed-resource.git
  GIT_TAG        0.2.0
)
FetchContent_MakeAvailable(embed_resource)
set_target_properties(embed_resource PROPERTIES FOLDER "tools")
#### END TOOLS

#### START Third Party
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        3.3.1
)
FetchContent_MakeAvailable(SQLiteCpp)
set_target_properties(SQLiteCpp PROPERTIES FOLDER "thirdParty")
set_target_properties(sqlite3 PROPERTIES FOLDER "thirdParty")

# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)

##
#  crossguid requires uuid library from uuid-dev, which can be aquired by
#  $ sudo apt-get install uuid-dev
#  but we like to have everything from source to be compiled
##
  set(LIBUUID_SHARED ON)

  FetchContent_Declare(libuuid
    GIT_REPOSITORY  https://github.com/gershnik/libuuid-cmake.git
    GIT_TAG         v2.39.1
    GIT_SHALLOW     TRUE
  )

  FetchContent_MakeAvailable(libuuid) 

  set(LIBUUID_INCLUDE_DIR uuid_shared)
  set(LIBUUID_LIBRARY uuid_shared)  

  ##
  # crossguid requires to have uuid/uuid.h at configure time, but uuid_shared generates header at compile time
  # we are creating dummy file to satify configure time, and remove it before compilation step
  # to allow build system to generate header file for us 
  ## 
  file(MAKE_DIRECTORY "${libuuid-cmake_BINARY_DIR}/include/uuid")
  file(TOUCH "${libuuid-cmake_BINARY_DIR}/include/uuid/uuid.h")  

  
  # We are creating target which requires dummy_marker_file.txt to exists, when evaluated
  # this triggers add_custom_command to create dummy_marker_file.txt and remove "one-time only" uuid.h
  # remove_dummy_uuid_header won't be called again beacuse dummy_marker_file.txt is already existing
  add_custom_target(
    remove_dummy_uuid_header
    DEPENDS "${libuuid-cmake_BINARY_DIR}/include/uuid/dummy_marker_file.txt"    
  )

  add_custom_command(
    OUTPUT "${libuuid-cmake_BINARY_DIR}/include/uuid/dummy_marker_file.txt"
    COMMAND ${CMAKE_COMMAND} -E touch "${libuuid-cmake_BINARY_DIR}/include/uuid/dummy_marker_file.txt"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${libuuid-cmake_BINARY_DIR}/include/uuid/uuid.h"
  )

  # removing header target will be done before uuid_shared target
  add_dependencies(uuid_shared remove_dummy_uuid_header)

endif()

set(CROSSGUID_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  crossguid
  GIT_REPOSITORY https://github.com/graeme-hill/crossguid.git
  GIT_TAG        ca1bf4b810e2d188d04cb6286f957008ee1b7681
)
FetchContent_MakeAvailable(crossguid)
set_target_properties(crossguid PROPERTIES FOLDER "thirdParty")

#### END Third Party

#### START APP

add_subdirectory("litebroker")
add_subdirectory("app")

#### END APP