add_executable(app "main.cpp" "main.h")

target_link_libraries(app PRIVATE litebroker SQLiteCpp)
target_include_directories(app PRIVATE embed-resource SQLiteCpp litebroker)

set_target_properties(app PROPERTIES
						PROJECT_LABEL "LiteBroker Application" 
						CXX_STANDARD 17
						CXX_STANDARD_REQUIRED YES
						CXX_EXTENSIONS Off)

if(WIN32)
	add_custom_command(TARGET app POST_BUILD
	  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:app> $<TARGET_FILE_DIR:app>
	  COMMAND_EXPAND_LISTS
	  )
ENDIF()
