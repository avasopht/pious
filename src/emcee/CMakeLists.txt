project(emcee)

set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES}
        ${PIOUS_INCLUDE_FILES})

set(SOURCE_FILES
        memory.cpp
        memory_dependent.cpp
        new.cpp
        new_allocation_block.cpp
        reference_counter.cpp
        shared_count.cpp
        string.cpp)


add_library(emcee STATIC ${SOURCE_FILES} ${INCLUDE_FILES})