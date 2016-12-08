find_path(JACK_INCLUDE_DIR NAMES jack/jack.h
        DOC "The JACK include directory"
        )

find_library(JACK_LIBRARY NAMES jack
        DOC "The JACK library"
        )

# handle the QUIETLY and REQUIRED arguments and set JACK_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JACK REQUIRED_VARS JACK_LIBRARY JACK_INCLUDE_DIR)

if(JACK_FOUND)
    set(JACK_LIBRARIES ${JACK_LIBRARY})
    set(JACK_INCLUDE_DIRS ${JACK_INCLUDE_DIR})
endif()

mark_as_advanced(JACK_INCLUDE_DIR JACK_LIBRARY)
