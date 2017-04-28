project(pious_jack_server)

find_package(JACK)


include_directories(${Boost_INCLUDE_DIR})

include_directories(${INCLUDE_DIR}/api)
include_directories(${INCLUDE_DIR}/emcee)
include_directories(${INCLUDE_DIR}/pious)
include_directories(${INCLUDE_DIR}/pious_dsp_lib)

include(PiousFiles)
Prepend(PIOUS_SOURCE_FILES "${SRC_DIR}/pious" ${PIOUS_SOURCE_FILES})
include(PiousDspLibFiles)
Prepend(DSP_LIB_SOURCE_FILES "${SRC_DIR}/pious_dsp_lib" ${DSP_LIB_SOURCE_FILES})
include(EmceeFiles)
Prepend(EMCEE_SOURCE_FILES "${SRC_DIR}/emcee" ${EMCEE_SOURCE_FILES})

SET(ALL_SOURCE_FILES ${PIOUS_SOURCE_FILES} ${DSP_LIB_SOURCE_FILES} ${EMCEE_SOURCE_FILES})

if (JACK_FOUND)
    include_directories(${JACK_INCLUDE_DIRS})
    add_executable(pious_exe pious_jack_main.cpp)
    target_link_libraries(pious_exe ${JACK_LIBRARIES})
else ()
    # empty build target.
    add_executable(pious_exe pious_main.cpp ${ALL_SOURCE_FILES})
endif ()