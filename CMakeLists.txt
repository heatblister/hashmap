project( AnnaHash )
cmake_minimum_required( VERSION 3.0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED on )

set( SOURCES anna_hash.cpp anna_hashmap.cpp)
set( HEADERS anna_hash.h anna_hashmap.h)

add_library(anna_hash STATIC ${SOURCES} ${HEADERS})

add_executable(example example.cpp)

target_link_libraries(example anna_hash)
