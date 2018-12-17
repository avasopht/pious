project(pious)

set(SOURCE_FILES
    add_connection.hpp
    add_connection_port.hpp
    add_connection_port_dest.hpp
    add_device.hpp
    connection_spec.hpp
    db.hpp
    device_spec.hpp
    id.hpp
    instance_factory.hpp
    port.hpp
    port_spec.hpp
    process.hpp
    reference_spec.hpp
    scope.hpp
    spec_finder.hpp
    spec_to_devices.hpp
    add_connection.cpp
    add_connection_port.cpp
    add_connection_port_dest.cpp
    add_device.cpp
    connection_spec.cpp
    db.cpp
    device_path_extractor.cpp
    device_path_search.cpp
    device_spec.cpp
    dsp_planner.cpp
    id.cpp
    pious_device_instance.cpp
    port.cpp
    port_spec.cpp
    rack.cpp
    reference_spec.cpp
    signal_channel.cpp
    signal_hold_channel.cpp
    spec_finder.cpp
    spec_to_instance.cpp
)


add_library(pious SHARED STATIC ${SOURCE_FILES})
install(TARGETS pious DESTINATION ${PIOUS_INSTALL_LIB_DIR})
get_headers(INCLUDE_FILES ${SOURCE_FILES})
install(FILES ${INCLUDE_FILES} DESTINATION ${PIOUS_INSTALL_INCLUDE_DIR}/pious)