cmake_minimum_required(VERSION 3.26...3.29)

# Project Version
set(PROJECT_VERSION 0.0.10)

project("LiteBroker" VERSION ${PROJECT_VERSION})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(get_dependecies)
include(get_all_targets)

# Put all targets created at this point (the dependencies) into one folder

get_all_targets(all_targets)
foreach(t ${all_targets})
    set_target_properties(${t} PROPERTIES FOLDER "dependencies")
endforeach()

#### START APP

if(WIN32)
	# Export all Symbols by default (on Windows creates '.lib'+ '.dll').
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

source_group("Embeded Files" REGULAR_EXPRESSION ".*sql.hpp$")

add_subdirectory("litebroker")
add_subdirectory("app")

#### END APP