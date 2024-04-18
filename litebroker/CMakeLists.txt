set(LIBRARY_NAME litebroker)
set(LIBRARY_RESOURCES_NAME ${LIBRARY_NAME}-resources)

set(EMBEDED_FILES "schema.sql" "create_task.sql" "receive_tasks.sql" "task_set_status.sql")
embed_resources(LIBRARY_RESOURCES_HPP ${EMBEDED_FILES})
add_custom_target(${LIBRARY_RESOURCES_NAME} SOURCES ${EMBEDED_FILES})
source_group("EmbededFiles" REGULAR_EXPRESSION ".*sql.hpp$")

configure_file("${CMAKE_SOURCE_DIR}/litebroker/litebroker.h.in" "${CMAKE_SOURCE_DIR}/litebroker/litebroker.h")

set(PUBLIC_HEADERS "include/broker.h")
set(BROKER_SOURCES ${LIBRARY_RESOURCES_HPP} "broker.cpp" ${PUBLIC_HEADERS})

add_library(${LIBRARY_NAME} SHARED ${BROKER_SOURCES})

target_include_directories(${LIBRARY_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties (${LIBRARY_NAME} PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS})

target_link_libraries(${LIBRARY_NAME} PRIVATE SQLiteCpp crossguid)

# Files to Install
install( TARGETS ${LIBRARY_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${LIBRARY_NAME} PROPERTY CXX_STANDARD 20)
endif()