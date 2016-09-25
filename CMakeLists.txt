cmake_minimum_required(VERSION 3.1)
project(pious)

add_definitions(-std=gnu++0x)

include_directories(api)

add_subdirectory(pious)
add_subdirectory(pious_tests)