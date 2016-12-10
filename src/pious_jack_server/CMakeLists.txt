project(pious_jack_server)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(JACK)

if(JACK_FOUND)
    include_directories(${JACK_INCLUDE_DIRS})

    add_executable(pious_exe pious_jack_main.cpp)

    target_link_libraries(pious_exe ${JACK_LIBRARIES})
endif()