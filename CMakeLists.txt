cmake_minimum_required(VERSION 3.1)
project(pious)

FUNCTION(Prepend var prefix)
    SET(listvar "")
    FOREACH(f ${ARGN})
        LIST(APPEND listvar "${prefix}/${f}")
    ENDFOREACH()
    SET(${var} "${listvar}" PARENT_SCOPE)
ENDFUNCTION()

add_definitions(-std=gnu++0x)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(GTest)
include_directories(include)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
enable_testing()
add_subdirectory(pious_tests)