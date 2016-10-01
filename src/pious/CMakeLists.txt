set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES}
        ${PIOUS_INCLUDE_FILES})


set(SOURCE_FILES
        id.cpp
        util.cpp )

add_library(pious STATIC ${SOURCE_FILES} ${INCLUDE_FILES})