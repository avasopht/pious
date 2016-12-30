project(pious_jack_server)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(JACK)

include_directories(${INCLUDE_DIR}/pious)
include_directories(${INCLUDE_DIR}/api)

if(JACK_FOUND)
    include_directories(${JACK_INCLUDE_DIRS})
    add_executable(pious_exe pious_jack_main.cpp)
    target_link_libraries(pious_exe ${JACK_LIBRARIES})
else()
    # empty build target.
    add_executable(pious_exe pious_main.cpp)
    target_link_libraries(pious_exe pious)
    target_link_libraries(pious_exe emcee)
endif()