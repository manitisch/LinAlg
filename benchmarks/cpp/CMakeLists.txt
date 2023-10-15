add_executable(LibMatrix src/lib_matrix.cpp)
target_link_libraries(LibMatrix PRIVATE LinAlg)

set_target_properties(LibMatrix PROPERTIES LINK_FLAGS -Wl,--stack,100000000)
