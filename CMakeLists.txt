cmake_minimum_required(VERSION 3.1)
project(pious)

FUNCTION(get_headers var files)
    set(include_files ${files} ${ARGN})
    list(FILTER include_files INCLUDE REGEX "\\.hpp")
    set(${var} ${include_files} PARENT_SCOPE)
ENDFUNCTION()

# Ignore warnings for find_package() calls since cmake 3.12, and opting for old behaviour
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 OLD)
endif(POLICY CMP0074)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_definitions(-std=c++0x)

set(PIOUS_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PIOUS_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(PIOUS_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(PIOUS_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include_directories(${PIOUS_INSTALL_INCLUDE_DIR})
include_directories(${PIOUS_HEADERS_DIR})
include_directories(${PIOUS_HEADERS_DIR}/include)


add_subdirectory(src)
enable_testing()
add_subdirectory(test)