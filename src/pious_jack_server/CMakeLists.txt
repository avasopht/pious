project(pious_jack_server)

find_package(JACK)


include_directories(${Boost_INCLUDE_DIR})

if (JACK_FOUND)
    include_directories(${JACK_INCLUDE_DIRS})
    add_executable(pious_main pious_jack_main.cpp)
    target_link_libraries(pious_main ${JACK_LIBRARIES} emcee pious pious_dsp_lib)
else ()
    # empty build target.
    add_executable(pious_main pious_main.cpp)
    target_link_libraries(pious_main emcee pious pious_dsp_lib)
endif ()