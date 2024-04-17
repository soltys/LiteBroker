
set(EMBEDED_FILES "schema.sql" "create_task.sql" "receive_tasks.sql" "task_set_status.sql")
embed_resources(liteBrokerRes ${EMBEDED_FILES})
add_custom_target(liteBrokerResources SOURCES ${EMBEDED_FILES})
source_group("EmbededFiles" REGULAR_EXPRESSION ".*sql.hpp$")

set(PUBLIC_HEADERS "include/broker.h")
set(BROKER_SOURCES ${liteBrokerRes} "broker.cpp" ${PUBLIC_HEADERS})

add_library(liteBroker SHARED ${BROKER_SOURCES})

target_include_directories(liteBroker INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties (liteBroker PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS})

target_link_libraries(liteBroker PRIVATE SQLiteCpp crossguid) 

# Files to Install
install( TARGETS liteBroker
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET liteBroker PROPERTY CXX_STANDARD 20)
endif()