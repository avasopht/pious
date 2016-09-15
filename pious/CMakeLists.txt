set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
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
        os_setter.hpp os_setter.cpp)

include_directories(${MY_SOURCE_DIR}/pious)

include_directories(/boost_1_55_0)

add_executable(exe ${SOURCE_FILES})