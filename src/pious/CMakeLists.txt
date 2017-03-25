project(pious)

include_directories(${INCLUDE_DIR}/pious)

set(INCLUDE_FILES
        ${PIOUS_INCLUDE_FILES})

include(../PiousFiles.cmake)
set(SOURCE_FILES ${PIOUS_SOURCE_FILES})

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_DIR}/api/pious_device.h ${INCLUDE_DIR}/api/pious_spec.h)