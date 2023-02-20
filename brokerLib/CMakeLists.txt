
add_library(brokerLib STATIC "brokerLib.cpp" "include/brokerLib.h")

target_include_directories(brokerLib
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
                           )

find_package(cppzmq CONFIG REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)

target_link_libraries(brokerLib PRIVATE cppzmq cppzmq-static SQLiteCpp)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET brokerLib PROPERTY CXX_STANDARD 20)
endif()