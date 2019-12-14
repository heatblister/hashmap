project( AnnaHash )
cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED on )

add_library(anna_hash STATIC anna_hash.h anna_hash.cpp)

add_executable(example example.cpp)

target_link_libraries(example anna_hash)
