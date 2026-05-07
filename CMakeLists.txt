cmake_minimum_required(VERSION 3.16)

project(sensor_interrupt_sim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(sensor_lib
    src/InterruptController.cpp
    src/SensorDriver.cpp
    src/SensorSimulator.cpp
)

add_executable(sensor_sim
    src/main.cpp
)

target_link_libraries(sensor_sim sensor_lib)

add_executable(sensor_tests
    tests/cpp_tests.cpp
)

target_link_libraries(sensor_tests sensor_lib)