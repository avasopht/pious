set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        id.cpp id.hpp
        os.hpp
        device_spec.hpp device_spec.cpp
        vector.hpp
        string.cpp string.hpp scoped_ptr.hpp device.cpp device.hpp port.cpp port.hpp connection.cpp connection.hpp)

include_directories(${MY_SOURCE_DIR}/pious)

add_executable(exe ${SOURCE_FILES})
