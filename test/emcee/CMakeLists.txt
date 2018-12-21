cmake_minimum_required(VERSION 3.1)
project(emcee_tests)

set(SOURCE_FILES
        test_literal.cpp
        test_map.cpp
        test_masked_cell_vector.cpp
        test_new.cpp
        test_object.cpp
        test_set.cpp
        test_shared_ptr.cpp
        test_string.cpp
        test_unique_ptr.cpp
        test_vector.cpp
        test_weak_count.cpp
        test_weak_ptr.cpp)

add_executable(runEmceeTests ${TEST_MAIN} ${SOURCE_FILES})

target_link_libraries(runEmceeTests gtest emcee)
target_link_libraries(runEmceeTests gmock gmock_main)

install(TARGETS runEmceeTests DESTINATION bin)