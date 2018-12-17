cmake_minimum_required(VERSION 3.1)
project(pious_api)

set(SOURCE_FILES
    db.h
    pious_api.h
    pious_device.h
    pious_device_instance.h
    pious_port_instance.h
    pious_rack.h
    pious_spec.h
    pious_sys.h)

install(FILES ${SOURCE_FILES} DESTINATION ${PIOUS_INSTALL_INCLUDE_DIR}/api)