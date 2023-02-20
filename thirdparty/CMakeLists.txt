set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)

add_subdirectory(SQLiteCpp)

set_target_properties(SQLiteCpp PROPERTIES FOLDER "thirdParty")
set_target_properties(sqlite3 PROPERTIES FOLDER "thirdParty")

include_directories(uuid_v4)