FUNCTION(Prepend var prefix)
    SET(listvar "")
    FOREACH(f ${ARGN})
        LIST(APPEND listvar "${prefix}/${f}")
    ENDFOREACH()
    SET(${var} "${listvar}" PARENT_SCOPE)
ENDFUNCTION()

set(EMCEE_INCLUDE_FILES
        array.hpp
        deleter.hpp
        destructor.hpp
        memory.hpp
        memory_dependent.hpp
        memory_setter.hpp
        new.hpp
        new_allocation_block.hpp
        reference_counter.hpp
        shared_count.hpp
        shared_ptr.hpp
        string.hpp
        unique_ptr.hpp
        util.hpp
        vector.hpp
        weak_count.hpp
        )

set(PIOUS_INCLUDE_FILES
        add_connection.hpp
        add_connection_port.hpp
        add_connection_port_dest.hpp
        add_device.hpp
        connection_spec.hpp
        device_spec.hpp
        id.hpp
        port.hpp
        port_spec.hpp
        process.hpp
        reference_spec.hpp
        scope.hpp
        )

Prepend(EMCEE_INCLUDE_FILES "${INCLUDE_DIR}/emcee" ${EMCEE_INCLUDE_FILES})
Prepend(PIOUS_INCLUDE_FILES "${INCLUDE_DIR}/pious" ${PIOUS_INCLUDE_FILES})


find_package(Boost 1.55 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
else()
    message( FATAL_ERROR "Boost required.")
endif()

add_subdirectory(pious)
add_subdirectory(emcee)