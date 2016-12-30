project(pious)

include_directories(${INCLUDE_DIR}/pious)

set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES}
        ${PIOUS_INCLUDE_FILES})


set(SOURCE_FILES
        add_connection.cpp
        add_connection_port.cpp
        add_connection_port_dest.cpp
        add_device.cpp
        connection_spec.cpp
        device_spec.cpp
        id.cpp
        reference_spec.cpp
        )

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_DIR}/api/pious_device.h ${INCLUDE_DIR}/api/pious_spec.h)