cmake_minimum_required(VERSION 3.1)
project(pious)

add_definitions(-std=gnu++0x)

include_directories(include)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
enable_testing()
add_subdirectory(pious_tests)