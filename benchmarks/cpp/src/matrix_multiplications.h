#include "matrix.h"

namespace matmul {
    // NxM times PxL => 
    template<typename T, size_t N, size_t L, size_t M, size_t P>
    linalg::Matrix<T, N, L> simple(linalg::Matrix<T, N, M>& a, linalg::Matrix<T, P, L>& b) {
        auto c = linalg::Matrix<T, N, L>{};
        
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                for (size_t k = 0; k < L; k++) {
                    c(i, k) += a(i, j)*b(j, k);
                }
            }
        }

        return c;
    }
}
