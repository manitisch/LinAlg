#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include "matrix_multiplications.h"

const float randomFloat(const float min, const float max) {
    return min + static_cast <float>(std::rand()) / static_cast<float>(RAND_MAX) * (max - min);
}

int main() {
    std::cout << "Start simple matrix mulitplication... " << std::endl;

    const size_t size = 1024;
    linalg::Matrix<float, size, size> A{};
    linalg::Matrix<float, size, size> B{};

    for (size_t i = 0 ; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            A(i, j) = randomFloat(0, 10000);
            B(i, j) = randomFloat(0, 10000);
        }
    }

    // simple multiplication
    const auto begin = std::chrono::high_resolution_clock::now();
    auto C = matmul::simple(A, B);
    const auto end = std::chrono::high_resolution_clock::now();

    const auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Elapsed time = " << elapsedTime << " ms" << std::endl;

    // parallel multiplication
    

    return 0;
}