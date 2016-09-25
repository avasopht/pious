project(pious_tests)

add_definitions(-std=gnu++0x)
add_definitions(-Dgoogle_disable_pthreads=ON)

add_subdirectory(lib/gtest-1.7.0)
add_subdirectory(basic_tests)