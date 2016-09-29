include_directories(${gmock_SOURCE_DIR}/gtest/include ${gmock_SOURCE_DIR}/gtest)
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(/boost_1_55_0)

add_executable(runBasicPiousTests
        test_object.cpp test_main.cpp class_method_notifier.hpp)

target_link_libraries(runBasicPiousTests gtest)
target_link_libraries(runBasicPiousTests gmock gmock_main)
target_link_libraries(runBasicPiousTests pious)

add_test(NAME pious_test COMMAND example)