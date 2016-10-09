project(pious)

include_directories(${INCLUDE_DIR}/pious)

set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES}
        ${PIOUS_INCLUDE_FILES})


set(SOURCE_FILES
        device.cpp
        device_spec.cpp
        port_spec.cpp
        reference_spec.cpp)

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_DIR}/api/pious_device.h)