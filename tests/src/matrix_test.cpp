#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "matrix.h"

TEST_CASE("simple test") {
    linalg::Matrix<float, 2, 3> A{{{1 ,2, 3},
                                   {4, 5, 6}}};

    CHECK(1 == A(0, 0));
    CHECK(2 == A(0, 1));
    CHECK(3 == A(0, 2));
    CHECK(4 == A(1, 0));
    CHECK(5 == A(1, 1));
    CHECK(6 == A(1, 2));
}

TEST_CASE("wrong size of initializer lists") {
    CHECK_THROWS(linalg::Matrix<float, 1, 1>{{{1 ,1}, {2, 3}}});  
}