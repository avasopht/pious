set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        device_spec.cpp
        main.cpp
        )

include_directories(${MY_SOURCE_DIR}/pious)

add_executable(exe ${SOURCE_FILES})
