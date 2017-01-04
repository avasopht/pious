include_directories(${gmock_SOURCE_DIR}/gtest/include ${gmock_SOURCE_DIR}/gtest)
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIR})

add_executable(runBasicPiousTests
        count_calls.hpp
        class_method_notifier.hpp
        test_id.cpp
        test_main.cpp
        test_masked_cell_vector.cpp
        test_new.cpp
        test_unique_ptr.cpp
        test_shared_ptr.cpp
        test_string.cpp
        test_var_rms.cpp
        test_vector.cpp
        test_weak_count.cpp
        test_weak_ptr.cpp)

target_link_libraries(runBasicPiousTests gtest)
target_link_libraries(runBasicPiousTests gmock gmock_main)
target_link_libraries(runBasicPiousTests pious)
target_link_libraries(runBasicPiousTests emcee)
target_link_libraries(runBasicPiousTests pious_dsp_lib)