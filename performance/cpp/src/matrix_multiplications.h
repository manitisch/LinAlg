#ifndef MATMUL_MATRIX_MULTIPLICATIONS_H
#define MATMUL_MATRIX_MULTIPLICATIONS_H

#include <algorithm>
#include <execution>
#include <numeric>
#include <vector>

#include "matrix.h"

namespace matmul {

    template<typename T, size_t Rows1, size_t Cols1, size_t Rows2, size_t Cols2>
    linalg::Matrix<T, Rows1, Cols2> simple(linalg::Matrix<T, Rows1, Cols1>& A, linalg::Matrix<T, Rows2, Cols2>& B) {
        linalg::Matrix<T, Rows1, Cols2> C{};
        
        for (size_t i = 0; i < Rows1; i++) {
            for (size_t j = 0; j < Cols1; j++) {
                for (size_t k = 0; k < Cols2; k++) {
                    C(i, k) += A(i, j) * B(j, k);
                }
            }
        }

        return C;
    }

    template<typename T, size_t Rows1, size_t Cols1, size_t Rows2, size_t Cols2>
    linalg::Matrix<T, Rows1, Cols2> withDotProduct(linalg::Matrix<T, Rows1, Cols1>& A, linalg::Matrix<T, Rows2, Cols2>& B) {
        linalg::Matrix<T, Rows1, Cols2> C{};

        for (size_t i = 0; i < Rows1; i++) {
            for (size_t j = 0; j < Cols2; j++) {
                C(i, j) = std::inner_product(A.rwiseBegin(i), A.rwiseEnd(i), B.cwiseBegin(j), 0.0f);
            }
        }
        return C;
    }

    struct Submatrix {
        const size_t rstart;
        const size_t rend;
        const size_t cstart;
        const size_t cend;
    };

    template<typename T, size_t Rows1, size_t Cols1, size_t Rows2, size_t Cols2>
    linalg::Matrix<T, Rows1, Cols2> parallel(linalg::Matrix<T, Rows1, Cols1>& A, linalg::Matrix<T, Rows2, Cols2>& B) {
        linalg::Matrix<T, Rows1, Cols2> C{};
    
        std::vector<Submatrix> idx{};    
        idx.push_back({0, Rows1, 0, Cols2 / 2});
        idx.push_back({0, Rows1, Cols2 / 2, Cols2});
        //idx.push_back({Rows1 / 2, Rows1, 0, Cols2 / 2});
        //idx.push_back({Rows1 / 2, Rows1, Cols2 / 2, Cols2});

        auto multiplicator = [&A, &B, &C](const Submatrix& idx) {
            for (size_t i = idx.rstart; i < idx.rend; i++) {
                for (size_t j = 0; j < Cols1; j++) {
                    for (size_t k = idx.cstart; k < idx.cend; k++) {
                        C(i, k) += A(i, j) + B(j, k);
                }
                }
            }
        };

        std::for_each(std::execution::par_unseq, idx.begin(), idx.end(), multiplicator);

        return C;    
    }

} // namespace matmul

#endif // MATMUL_MATRIX_MULTIPLICATIONS_H