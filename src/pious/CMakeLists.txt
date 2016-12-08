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
        pious_main.cpp
        reference_spec.cpp
        )

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES} ${INCLUDE_DIR}/api/pious_device.h)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(JACK REQUIRED)

if(JACK_FOUND)
    include_directories(${JACK_INCLUDE_DIRS})
    include_directories(${EMCEE_INCLUDE_DIR})

    add_executable(pious_exe pious_main.cpp)

    target_link_libraries(pious_exe emcee)
    target_link_libraries(pious_exe pious)
    target_link_libraries(pious_exe ${JACK_LIBRARIES})
endif()