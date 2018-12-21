cmake_minimum_required(VERSION 3.1)
project(pious_tests)

set(SOURCE_FILES
        class_method_notifier.hpp
        count_calls.hpp
        test_device_spec.cpp
        test_id.cpp
        test_pious_db.cpp
        test_rack.cpp
        test_var_rms.cpp)

add_executable(runPiousTests ${TEST_MAIN} ${SOURCE_FILES})

target_link_libraries(runPiousTests emcee pious pious_dsp_lib)
target_link_libraries(runPiousTests gtest)
target_link_libraries(runPiousTests gmock gmock_main)

install(TARGETS runPiousTests DESTINATION bin)