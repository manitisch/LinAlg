add_library(${PROJECT_NAME}_Doctest INTERFACE)
target_include_directories(${PROJECT_NAME}_Doctest INTERFACE thirparty)

add_executable(${PROJECT_NAME}_MatrixTest src/matrix_test.cpp)
target_link_libraries(${PROJECT_NAME}_MatrixTest PRIVATE ${PROJECT_NAME}_Matrix
                                                         ${PROJECT_NAME}_Doctest)

add_executable(${PROJECT_NAME}_TensorTest src/tensor_test.cpp)
target_link_libraries(${PROJECT_NAME}_TensorTest PRIVATE ${PROJECT_NAME}_Tensor
                                                         ${PROJECT_NAME}_Doctest)

add_test(${PROJECT_NAME}_MatrixTest ${PROJECT_NAME}_MatrixTest)
add_test(${PROJECT_NAME}_TensorTest ${PROJECT_NAME}_TensorTest)
