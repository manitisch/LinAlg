import Matrix;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"



TEST_CASE("Construction") {
    SUBCASE("Size of initalization list") {
        CHECK_THROWS(linalg::Matrix<float, 1, 1>{{{1 ,1}, {2, 3}}});  
    }

    SUBCASE("Zero initialization") {
        linalg::Matrix<float, 2, 2> A{};

        CHECK(doctest::Approx(0) == A(0, 0));
        CHECK(doctest::Approx(0) == A(0, 1));
        CHECK(doctest::Approx(0) == A(1, 0));
        CHECK(doctest::Approx(0) == A(1, 1));
    }

    SUBCASE("Initialization list") {
        linalg::Matrix<float, 2, 3> A{{{1 ,2, 3},
                                       {4, 5, 6}}};

        CHECK(doctest::Approx(1) == A(0, 0));
        CHECK(doctest::Approx(2) == A(0, 1));
        CHECK(doctest::Approx(3) == A(0, 2));
        CHECK(doctest::Approx(4) == A(1, 0));
        CHECK(doctest::Approx(5) == A(1, 1));
        CHECK(doctest::Approx(6) == A(1, 2));
    }
}

TEST_CASE("Multiplication") {
    linalg::Matrix<int, 2, 3> A{{-1, 4, 2},
                                {-9, 0, 5}};

    linalg::Matrix<int, 3, 4> B{{ 6,  7,  1,  8},
                                { 0, -2, -5, -5},
                                {-3,  6,  1,  3}};

    auto C = A*B;
    const auto[rows, columns] = C.shape();

    CHECK(2 == rows);
    CHECK(4 == columns);

    CHECK(-12 == C(0,0));
    CHECK( -3 == C(0,1));
    CHECK(-19 == C(0,2));
    CHECK(-22 == C(0,3));
    CHECK(-69 == C(1,0));
    CHECK(-33 == C(1,1));
    CHECK( -4 == C(1,2));
    CHECK(-57 == C(1,3));
}

TEST_CASE("Addition") {
    linalg::Matrix<int, 3, 2> A{{1, 1},
                                {1, 1},
                                {1, 1}};
    
    linalg::Matrix<int, 3, 2> B{{2, 2},
                                {2, 2},
                                {2, 2}};

    auto C = A + B;

    for (auto& c : C) {
        CHECK(3 == c);
    };
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