# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.10)

# Name of the project
project(C-Embedded-System-Simulator VERSION 1.0)

# Set the C++ standard to C20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(C-Embedded-System-Simulator src/cpp/main.cpp)