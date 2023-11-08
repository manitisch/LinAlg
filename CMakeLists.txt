cmake_minimum_required(VERSION 3.28.0)

project(LinAlg LANGUAGES CXX VERSION 0.1)

# enable modules
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

# subdirectories
add_subdirectory(performance/cpp)
add_subdirectory(lib)
add_subdirectory(tests)
