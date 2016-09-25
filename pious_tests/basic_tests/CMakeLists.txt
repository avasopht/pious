include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(runBasicPiousTests
        basic_check.cpp)

target_link_libraries(runBasicPiousTests gtest gtest_main)
target_link_libraries(runBasicPiousTests pious)

add_test(NAME pious_test COMMAND example)