#include <iostream>

#include "matrix_multiplications.h"

int main() {
    std::cout << "benchmarks" << std::endl;

    auto A = linalg::Matrix<int, 2, 3>{{1, 2, 3},
                                       {4, 5, 6}};

    auto B = linalg::Matrix<int, 3, 2>{{10, 11},
                                       {12, 13},
                                       {14, 15}};

    auto C = matmul::simple(A, B);

    std::cout << "Result: " << std::endl
              << C(0, 0) << " " << C(0, 1) << " " << C(0, 2) << std::endl
              << C(1, 0) << " " << C(1, 1) << " " << C(1, 2) << std::endl;

    return 0;
}