if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

include_directories(${Boost_INCLUDE_DIR})

include_directories(${INCLUDE_DIR}/emcee)
include_directories(${INCLUDE_DIR}/pious)
include_directories(${INCLUDE_DIR}/pious_dsp_lib)

include(PiousFiles)
Prepend(PIOUS_SOURCE_FILES "${SRC_DIR}/pious" ${PIOUS_SOURCE_FILES})
include(PiousDspLibFiles)
Prepend(DSP_LIB_SOURCE_FILES "${SRC_DIR}/pious_dsp_lib" ${DSP_LIB_SOURCE_FILES})
include(EmceeFiles)
Prepend(EMCEE_SOURCE_FILES "${SRC_DIR}/emcee" ${EMCEE_SOURCE_FILES})


add_executable(runBasicPiousTests
        ${PIOUS_SOURCE_FILES}
        ${EMCEE_SOURCE_FILES}
        ${DSP_LIB_SOURCE_FILES}
        count_calls.hpp
        class_method_notifier.hpp
        test_device_spec.cpp
        test_id.cpp
        test_main.cpp
        test_map.cpp
        test_masked_cell_vector.cpp
        test_new.cpp
        test_pious_db.cpp
        test_rack.cpp
        test_shared_ptr.cpp
        test_string.cpp
        test_unique_ptr.cpp
        test_var_rms.cpp
        test_vector.cpp
        test_weak_count.cpp
        test_weak_ptr.cpp)

target_link_libraries(runBasicPiousTests gtest)
target_link_libraries(runBasicPiousTests gmock gmock_main)
