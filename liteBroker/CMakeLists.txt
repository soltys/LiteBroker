
set(EMBEDED_FILES "schema.sql" "create_task.sql")
embed_resources(liteBrokerRes ${EMBEDED_FILES})
add_custom_target(liteBrokerResources SOURCES ${EMBEDED_FILES})
source_group("EmbededFiles" REGULAR_EXPRESSION ".*sql.hpp$")

set(PUBLIC_HEADERS "include/broker.h")
set(BROKER_SOURCES ${liteBrokerRes} "broker.cpp" ${PUBLIC_HEADERS})

# Export all Symbols by default (on Windows creates '.lib'+ '.dll').
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


add_library(liteBroker SHARED ${BROKER_SOURCES})

target_include_directories(liteBroker
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
                           PRIVATE ${CMAKE_SOURCE_DIR}/thirdparty/uuid_v4
                           )

set_target_properties (liteBroker PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS})

target_link_libraries(liteBroker PRIVATE SQLiteCpp) 

# Files to Install
install( TARGETS liteBroker
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET liteBroker PROPERTY CXX_STANDARD 20)
endif()