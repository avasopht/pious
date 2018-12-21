cmake_minimum_required(VERSION 3.1)

set(TESTS_ROOT ${PROJECT_SOURCE_DIR}/test)
set(TEST_MAIN ${TESTS_ROOT}/test_main.cpp)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PIOUS_HEADERS_DIR})
include_directories(${TESTS_ROOT}/lib/googletest/googletest/include)

add_subdirectory(lib/googletest)
add_subdirectory(emcee)
add_subdirectory(pious)