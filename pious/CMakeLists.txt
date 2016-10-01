project(pious)

set(INCLUDE_FILES
        id.hpp
        vector.hpp
        unique_ptr.hpp
        array.hpp
        deleter.hpp
        util.hpp
        destructor.hpp
        new_allocation_block_calculation.hpp
        new_allocation_block.hpp
        memory_dependent.hpp
        memory_setter.hpp
        new.hpp
        memory.hpp
        )

set(SOURCE_FILES
        id.cpp
        memory.cpp
        memory_dependent.cpp
        memory_setter.cpp
        new.cpp
        new_allocation_block.cpp
        util.cpp )

find_package(Boost 1.55 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
else()
    message( FATAL_ERROR "Boost required.")
endif()

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES})