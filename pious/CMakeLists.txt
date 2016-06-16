set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pious/main.cpp)

add_executable(exe ${PROJECT_SOURCE_DIR}/${SOURCE_FILES})
