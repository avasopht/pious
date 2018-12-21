project(pious_dsp_lib)

set(SOURCE_FILES
    var_rms.hpp
    var_rms.cpp
)

get_headers(INCLUDE_FILES ${SOURCE_FILES})

add_library(pious_dsp_lib SHARED STATIC ${SOURCE_FILES})
target_link_libraries(pious_dsp_lib pious emcee)
install(TARGETS pious_dsp_lib DESTINATION ${PIOUS_INSTALL_LIB_DIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${PIOUS_INSTALL_INCLUDE_DIR}/pious_dsp_lib)