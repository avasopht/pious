project(pious_dsp_lib VERSION 0.0.1)

include_directories(${INCLUDE_DIR}/emcee)
include_directories(${INCLUDE_DIR}/pious)
include_directories(${INCLUDE_DIR}/pious_dsp_lib)

set(INCLUDE_FILES
        ${PIOUS_DSP_LIB_INCLUDE_FILES})

set(SOURCE_FILES
        var_rms.cpp
        )

add_library(pious_dsp_lib STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(pious_dsp_lib emcee)