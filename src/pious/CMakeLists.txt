project(pious)

include_directories(${INCLUDE_DIR}/emcee)
include_directories(${INCLUDE_DIR}/pious)

include(PiousFiles)
set(SOURCE_FILES ${PIOUS_SOURCE_FILES})

add_library(pious STATIC ${SOURCE_FILES})