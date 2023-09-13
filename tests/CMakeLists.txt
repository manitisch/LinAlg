add_library(Doctest INTERFACE)
target_include_directories(Doctest INTERFACE thirparty)

add_executable(MatrixTest src/matrix_test.cpp)
target_link_libraries(MatrixTest PRIVATE LinAlg Doctest)

add_executable(MatrixMultiplicationsTest src/matrix_test.cpp)
target_link_libraries(MatrixMultiplicationsTest PRIVATE LinAlg Doctest)
