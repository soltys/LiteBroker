# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.14...3.29)

include(FetchContent)

# Project Version
set(PROJECT_VERSION 1.0.0)

project("LiteBroker" VERSION ${PROJECT_VERSION})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mavx2 -march=x86-64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx -mavx2 -march=x86-64")
endif()

if(WIN32())
	# Export all Symbols by default (on Windows creates '.lib'+ '.dll').
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#### START TOOLS
FetchContent_Declare(
  embed-resource
  GIT_REPOSITORY https://github.com/soltys/embed-resource.git
  GIT_TAG        a7e55562b60b76317daf9fb65ede6f8d384a5204
)
FetchContent_MakeAvailable(embed-resource)
set_target_properties(embed-resource PROPERTIES FOLDER "tools")
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

FetchContent_Declare(
  crossguid
  GIT_REPOSITORY https://github.com/graeme-hill/crossguid.git
  GIT_TAG        ca1bf4b810e2d188d04cb6286f957008ee1b7681
)
FetchContent_MakeAvailable(crossguid)
set_target_properties(crossguid PROPERTIES FOLDER "thirdParty/crossguid")
set_target_properties(crossguid-test PROPERTIES FOLDER "thirdParty/crossguid")

include_directories(uuid_v4)
include_directories(crossguid)
#### END Third Party

#### START APP

add_subdirectory("liteBroker")
add_subdirectory("app")

#### END APP