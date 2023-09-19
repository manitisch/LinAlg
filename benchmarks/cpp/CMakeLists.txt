add_executable(Benchmarks src/benchmarks.cpp)
target_link_libraries(Benchmarks PRIVATE LinAlg)

set_target_properties(Benchmarks PROPERTIES LINK_FLAGS -Wl,--stack,100000000)
