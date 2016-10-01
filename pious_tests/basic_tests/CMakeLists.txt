include_directories(${gmock_SOURCE_DIR}/gtest/include ${gmock_SOURCE_DIR}/gtest)
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(/boost_1_55_0)

add_executable(runBasicPiousTests
        test_main.cpp class_method_notifier.hpp test_new_memory_block_calculation.cpp test_new.cpp test_unique_ptr.cpp count_calls.hpp)

target_link_libraries(runBasicPiousTests gtest)
target_link_libraries(runBasicPiousTests gmock gmock_main)
target_link_libraries(runBasicPiousTests pious)
target_link_libraries(runBasicPiousTests emcee)

add_test(NAME pious_test COMMAND example)