# Add source to this project's executable.
add_executable(app "main.cpp" "main.h" ${MyResources})

target_link_libraries(app PRIVATE liteBroker SQLiteCpp)
target_include_directories(app PRIVATE embed-resource SQLiteCpp)

if(WIN32)
	add_custom_command(TARGET app POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
	  COMMAND_EXPAND_LISTS
	  )
ENDIF()

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET app PROPERTY CXX_STANDARD 20)
endif()
