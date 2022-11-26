set(CMAKE_SYSTEM_NAME Windows)
cmake_minimum_required(VERSION 3.0.0)
project(linter VERSION 0.1.0)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
set(CMAKE_SUPPRESS_REGENERATION true) 
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()
include(CTest)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_CFLAGS}")
add_executable(remedy ./project.cpp)

add_executable(testing ./tests/tests.cpp)
