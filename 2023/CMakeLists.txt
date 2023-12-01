project(AdventOfCode)
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)

file( GLOB APP_SOURCES *.cpp )
foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(barename ${testsourcefile} NAME)
    string( REPLACE ".cpp" "" testname ${barename} )
    add_executable( ${testname} ${barename} )
endforeach( testsourcefile ${APP_SOURCES} )


add_compile_options(-Wno-format)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format -pthread -O3")
