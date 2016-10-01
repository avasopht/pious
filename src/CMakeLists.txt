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
        new_allocation_block_calculation.hpp
        unique_ptr.hpp
        util.hpp
        vector.hpp)

set(PIOUS_INCLUDE_FILES
        connection.hpp
        device.hpp
        device_spec.hpp
        id.hpp
        port.hpp)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(pious)