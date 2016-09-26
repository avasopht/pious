project(pious)

set(SOURCE_FILES
        id.cpp id.hpp
        os.hpp
        #device_spec.hpp device_spec.cpp
        vector.hpp
        string.hpp string.cpp
        unique_ptr.hpp
        #device.cpp device.hpp
        #port.cpp port.hpp
        #connection.cpp connection.hpp
        deleter.hpp
        array.hpp
        os_setter.hpp os_setter.cpp os_memory.hpp os_memory.cpp os.cpp os_dependent.hpp os_op.hpp)

include_directories(${MY_SOURCE_DIR}/pious)

include_directories(/boost_1_55_0)

add_library(pious STATIC ${SOURCE_FILES})