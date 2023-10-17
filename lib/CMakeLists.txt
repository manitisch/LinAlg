add_library(LinAlg)
target_sources(LinAlg 
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        src/matrix.cppm
)
