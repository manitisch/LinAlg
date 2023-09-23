#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "matrix.h"

TEST_CASE("Instantiation") {
    CHECK_THROWS(linalg::Matrix<float, 1, 1>{{{1 ,1}, {2, 3}}});  

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



TEST_CASE("Iterator") {
    static constexpr size_t rows = 2;
    static constexpr size_t columns = 3;

    linalg::Matrix<int, rows, columns> A{{{0 ,1, 2},
                                          {1, 2, 3}}};

    SUBCASE("Ranges") {
        CHECK_THROWS(A.rwiseBegin(rows));
        CHECK_THROWS(A.cwiseBegin(columns));
    }

    SUBCASE("Access rows") {
        auto row_iterator = A.rwiseBegin(0);
    
        for (int i = 0; i < columns; i++) {
            CHECK(*row_iterator == i);
            std::advance(row_iterator, 1);
        }   

        row_iterator = A.rwiseBegin(1);

        for (int i = 1; i < columns + 1; i++) {
            CHECK(*row_iterator == i);
            std::advance(row_iterator, 1);
        }
    }

    SUBCASE("Access columns") {
        auto column_iterator = A.cwiseBegin(0);

        for (int i = 0; i < rows; i++) {
            CHECK(*column_iterator == i);
            std::advance(column_iterator, 1);
        }

        column_iterator = A.cwiseBegin(1);

        for (int i = 1; i < rows + 1; i++) {
            CHECK(*column_iterator == i);
            std::advance(column_iterator, 1);
        }

        column_iterator = A.cwiseBegin(2);

        for (int i = 2; i < rows + 2; i++) {
            CHECK(*column_iterator == i);
            std::advance(column_iterator, 1);
        } 
    }

    SUBCASE("Distance from begin to end") {     
        CHECK(std::distance(A.rwiseBegin(0), A.rwiseEnd(0)) == columns);
        CHECK(std::distance(A.cwiseBegin(0), A.cwiseEnd(0)) == rows);
    }   
}