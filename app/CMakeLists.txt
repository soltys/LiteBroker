# Add source to this project's executable.
add_executable(app "main.cpp" "main.h")

target_link_libraries(app PRIVATE brokerLib)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET app PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
