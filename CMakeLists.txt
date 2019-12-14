project( AnnaHash )
cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED on )

add_library(anna_hash INTERFACE)
target_include_directories(anna_hash INTERFACE include/)

add_executable(example example.cpp)

target_link_libraries(example anna_hash)
