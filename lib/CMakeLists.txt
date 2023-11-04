add_library(${PROJECT_NAME}_Matrix)
target_sources(${PROJECT_NAME}_Matrix 
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        src/matrix.cppm
)
