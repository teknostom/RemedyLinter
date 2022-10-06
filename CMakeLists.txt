cmake_minimum_required(VERSION 3.0.0)
project(linter VERSION 0.1.0)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
set(CMAKE_SUPPRESS_REGENERATION true) 

enable_testing()
include(CTest)

add_executable(remedy ./project.cpp)

add_executable(testing ./tests/tests.cpp)
