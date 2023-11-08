add_library(${PROJECT_NAME}_Matrix)
target_sources(${PROJECT_NAME}_Matrix PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    src/matrix.cppm
)

add_library(${PROJECT_NAME}_Tensor)
target_sources(${PROJECT_NAME}_Tensor PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    src/tensor.cppm
)
target_link_libraries(${PROJECT_NAME}_Tensor PRIVATE ${PROJECT_NAME}_Matrix)
