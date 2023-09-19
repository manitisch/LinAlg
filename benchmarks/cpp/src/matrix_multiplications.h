#include <algorithm>

#include "matrix.h"

namespace matmul {

    template<typename T, size_t N, size_t L, size_t M, size_t P>
    linalg::Matrix<T, N, L> simple(linalg::Matrix<T, N, M>& A, linalg::Matrix<T, P, L>& B) {
        linalg::Matrix<T, N, L> C{};
        
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                for (size_t k = 0; k < L; k++) {
                    C(i, k) += A(i, j) * B(j, k);
                }
            }
        }

        return C;
    }

    template<typename T, size_t N, size_t L, size_t M, size_t P>
    linalg::Matrix<T, N, L> parallel(linalg::Matrix<T, N, M>& A, linalg::Matrix<T, P, L>& B) {
        linalg::Matrix<T, N, L> C{};

        // TODO implement

        return C;
    }


} // namespace matmul
