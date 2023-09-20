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

    auto row0 = A.getRow(0);
    auto row1 = A.getRow(1);

    CHECK(std::array<float, 3>{1, 2, 3} == row0);
    CHECK(std::array<float, 3>{4, 5, 6} == row1);

    auto col0 = A.getCol(0);
    auto col1 = A.getCol(1);
    auto col2 = A.getCol(2);

    CHECK(std::array<float, 2>{1, 4} == col0);
    CHECK(std::array<float, 2>{2, 5} == col1);
    CHECK(std::array<float, 2>{3, 6} == col2);
}

TEST_CASE("wrong size of initializer lists") {
    CHECK_THROWS(linalg::Matrix<float, 1, 1>{{{1 ,1}, {2, 3}}});  
}