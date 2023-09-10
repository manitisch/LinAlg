cmake_minimum_required(VERSION 3.18.4)

project(LinAlg VERSION 0.1)

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# subdirectories
add_subdirectory(lib)
add_subdirectory(tests)