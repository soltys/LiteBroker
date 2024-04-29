set(LIBRARY_NAME litebroker)
set(LIBRARY_RESOURCES_NAME ${LIBRARY_NAME}-resources)

set(EMBEDED_FILES "schema.sql" "create_task.sql" "receive_tasks.sql" "task_set_status.sql")
embed_resources(LIBRARY_RESOURCES_HPP FILES ${EMBEDED_FILES} CONTENT_AS_COMMENT)
add_custom_target(${LIBRARY_RESOURCES_NAME} SOURCES ${EMBEDED_FILES})
set_target_properties(${LIBRARY_RESOURCES_NAME}  PROPERTIES
						PROJECT_LABEL "LiteBroker Library Resources" )
configure_file("${PROJECT_SOURCE_DIR}/${LIBRARY_NAME}/litebroker_internal.h.in" "${PROJECT_BINARY_DIR}/${LIBRARY_NAME}/litebroker_internal.h")

set(PUBLIC_HEADERS "include/litebroker.h")
set(BROKER_SOURCES ${LIBRARY_RESOURCES_HPP} "broker.cpp" ${PUBLIC_HEADERS})

add_library(${LIBRARY_NAME} SHARED ${BROKER_SOURCES})

target_include_directories(${LIBRARY_NAME} 
	PUBLIC ${PROJECT_SOURCE_DIR}/${LIBRARY_NAME}/include 
	PRIVATE ${PROJECT_BINARY_DIR}/${LIBRARY_NAME})

target_link_libraries(${LIBRARY_NAME} PRIVATE SQLiteCpp crossguid)

# Files to Install
install( TARGETS ${LIBRARY_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

	
set_target_properties(${LIBRARY_NAME}  PROPERTIES
						PROJECT_LABEL "LiteBroker Library" 
						CXX_STANDARD 17
						CXX_STANDARD_REQUIRED YES
						CXX_EXTENSIONS Off
						PUBLIC_HEADER ${PUBLIC_HEADERS}
						COMPILE_DEFINITIONS "DLL_EXPORT")