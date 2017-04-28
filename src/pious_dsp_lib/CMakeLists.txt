project(pious_dsp_lib VERSION 0.0.1)

include_directories(${INCLUDE_DIR}/emcee)
include_directories(${INCLUDE_DIR}/pious)
include_directories(${INCLUDE_DIR}/pious_dsp_lib)

set(INCLUDE_FILES
        ${PIOUS_DSP_LIB_INCLUDE_FILES})

include(PiousDspLibFiles)
set(SOURCE_FILES ${DSP_LIB_SOURCE_FILES})

add_library(pious_dsp_lib STATIC ${SOURCE_FILES} ${INCLUDE_FILES})