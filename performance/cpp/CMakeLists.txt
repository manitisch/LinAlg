add_executable(${PROJECT_NAME}_MatrixPerformance src/matrix_performance.cpp)
target_link_libraries(${PROJECT_NAME}_MatrixPerformance PRIVATE ${PROJECT_NAME}_Matrix)

set_target_properties(${PROJECT_NAME}_MatrixPerformance PROPERTIES LINK_FLAGS -Wl,--stack,100000000)
