project(pious)

set(SOURCE_FILES
        id.cpp id.hpp
        #device_spec.hpp device_spec.cpp
        vector.hpp
        string.hpp string.cpp
        unique_ptr.hpp
        #device.cpp device.hpp
        #port.cpp port.hpp
        #connection.cpp connection.hpp
        deleter.hpp
        array.hpp
        memory.hpp memory.cpp object.hpp memory_dependent.cpp memory_dependent.hpp memory_setter.hpp object.cpp memory_setter.cpp)

include_directories(${MY_SOURCE_DIR}/pious)

find_package(Boost 1.55 REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
else()
    message( FATAL_ERROR "Boost required.")
endif()

add_library(pious STATIC ${SOURCE_FILES})