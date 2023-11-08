import Tensor;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


TEST_CASE("Construction") {
    SUBCASE("Size of initalization list") {
        CHECK_THROWS(linalg::Tensor<float, 1, 1>{{{1 ,1}, {2, 3, 4}}});  
    }

    SUBCASE("Basic intialization") {
        linalg::Tensor<int, 3, 4> T{42};

        const auto[depth, rows, columns] = T.shape();
        CHECK(0 == depth);
        CHECK(3 == rows);
        CHECK(4 == columns);

        const size_t elem_count = 4;

        for (size_t d = 0; d < elem_count; d++) {
            T.append({{1, 1, 1, 1},
                      {2 ,2 ,2, 2},
                      {3, 3, 3, 3}});
        }

        CHECK(std::get<0>(T.shape()) == elem_count);
    }

    SUBCASE("Initialization list") {
        linalg::Tensor<int, 2, 3> T{{{{1 ,2, 3},
                                      {4, 5, 6}},
                                     {{1 ,2, 3},
                                      {4, 5, 6}}}};

        const auto[depth, rows, columns] = T.shape();
       
        CHECK(2 == depth);

        for (size_t d = 0; d < depth; d++) {
            CHECK(1 == T(d, 0, 0));
            CHECK(2 == T(d, 0, 1));
            CHECK(3 == T(d, 0, 2));
            CHECK(4 == T(d, 1, 0));
            CHECK(5 == T(d, 1, 1));
            CHECK(6 == T(d, 1, 2));
        }
    }
}

TEST_CASE("Multiplication") {
    SUBCASE("Mismatch of shapes") {
        linalg::Tensor<double, 2, 2> A{};
        linalg::Tensor<double, 2, 2> B{};

        A.append({{1, 1},
                  {1, 1}});

        CHECK_THROWS(A*B); 
    }
    
    SUBCASE("Shape and result") {
        linalg::Tensor<int, 2, 3> A{{{-1, 4, 2},
                                     {-9, 0, 5}},
                                    {{-1, 4, 2},
                                     {-9, 0, 5}}};

        linalg::Tensor<int, 3, 4> B{{{ 6,  7,  1,  8},
                                     { 0, -2, -5, -5},
                                     {-3,  6,  1,  3}},
                                    {{ 6,  7,  1,  8},
                                     { 0, -2, -5, -5},
                                     {-3,  6,  1,  3}}};

        auto C = A*B;
        const auto[depth, rows, columns] = C.shape();

        CHECK(2 == depth);
        CHECK(2 == rows);
        CHECK(4 == columns);

        for (size_t d = 0; d < depth; d++) {
            CHECK(-12 == C(d, 0,0));
            CHECK( -3 == C(d, 0,1));
            CHECK(-19 == C(d, 0,2));
            CHECK(-22 == C(d, 0,3));
            CHECK(-69 == C(d, 1,0));
            CHECK(-33 == C(d, 1,1));
            CHECK( -4 == C(d, 1,2));
            CHECK(-57 == C(d, 1,3));
        }    
    }
}
