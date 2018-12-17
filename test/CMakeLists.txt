cmake_minimum_required(VERSION 3.1)
project(pious_tests)

add_subdirectory(lib/googletest)

include_directories(${PIOUS_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

include_directories(${Boost_INCLUDE_DIR})
set(SOURCE_FILES
    src/count_calls.hpp
    src/class_method_notifier.hpp
    src/test_device_spec.cpp
    src/test_id.cpp
    src/test_map.cpp
    src/test_masked_cell_vector.cpp
    src/test_new.cpp
    src/test_pious_db.cpp
    src/test_rack.cpp
    src/test_set.cpp
    src/test_shared_ptr.cpp
    src/test_string.cpp
    src/test_unique_ptr.cpp
    src/test_var_rms.cpp
    src/test_vector.cpp
    src/test_weak_count.cpp
    src/test_weak_ptr.cpp)

add_executable(runBasicPiousTests test_main.cpp ${SOURCE_FILES})

target_link_libraries(runBasicPiousTests gtest emcee pious pious_dsp_lib)
target_link_libraries(runBasicPiousTests gmock gmock_main)

install(TARGETS runBasicPiousTests DESTINATION bin)