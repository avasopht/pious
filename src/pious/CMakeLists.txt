

Prepend(EMCEE_INCLUDE_FILES "${INCLUDE_DIR}/emcee" ${EMCEE_INCLUDE_FILES})
Prepend(PIOUS_INCLUDE_FILES "${INCLUDE_DIR}/pious" ${PIOUS_INCLUDE_FILES})

set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES}
        ${PIOUS_INCLUDE_FILES})


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