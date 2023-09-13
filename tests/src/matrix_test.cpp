#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "matrix.h"

TEST_CASE("simple test") {
    auto matrix = linalg::Matrix<float, 2, 3>{{{1 ,2, 3},
                                               {4, 5, 6}}};

    CHECK(1 == matrix(0, 0));
    CHECK(2 == matrix(0, 1));
    CHECK(3 == matrix(0, 2));
    CHECK(4 == matrix(1, 0));
    CHECK(5 == matrix(1, 1));
    CHECK(6 == matrix(1, 2));
}

TEST_CASE("wrong size of initializer lists") {
    CHECK_THROWS(linalg::Matrix<float, 1, 1>{{{1 ,1}, {2, 3}}});  
}