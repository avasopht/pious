project(emcee VERSION 0.0.1)

set(SOURCE_FILES
        array.hpp
        deleter.hpp
        destructor.hpp
        emcee.hpp
        literal.cpp
        literal.hpp
        map.hpp
        masked_cell_vector.hpp
        memory_dependent.cpp
        memory_dependent.hpp
        memory_setter.hpp
        new.cpp
        new.hpp
        new_allocation_block.cpp
        new_allocation_block.hpp
        object.cpp
        object.hpp
        platform.cpp
        platform.hpp
        pow2.cpp
        pow2.hpp
        readme.md
        reference_counter.cpp
        reference_counter.hpp
        set.hpp
        shared_count.cpp
        shared_count.hpp
        shared_ptr.hpp
        string.cpp
        string.hpp
        unique_ptr.hpp
        util.cpp
        util.hpp
        vector.hpp
        weak_count.cpp
        weak_count.hpp
        weak_ptr.hpp)

get_headers(INCLUDE_FILES ${SOURCE_FILES})

add_library(emcee SHARED STATIC ${SOURCE_FILES})
install(TARGETS emcee DESTINATION ${PIOUS_INSTALL_LIB_DIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${PIOUS_INSTALL_INCLUDE_DIR}/emcee)