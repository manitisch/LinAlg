#ifndef MATMUL_MATRIX_MULTIPLICATIONS_H
#define MATMUL_MATRIX_MULTIPLICATIONS_H

#include <algorithm>
#include <numeric>

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
                C(i, j) = std::inner_product(A.rwiseBegin(i), A.rwiseEnd(i), B.cwiseBegin(j), 0);
            }
        }
        return C;
    }


} // namespace matmul

#endif // MATMUL_MATRIX_MULTIPLICATIONS_H