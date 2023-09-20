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
    std::cout << "Start simple matrix mulitplication... " << std::endl;

    auto begin = std::chrono::high_resolution_clock::now();
    auto C = matmul::simple(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Elapsed time = " << elapsedTime << std::endl;

    // with dot product multiplication
    std::cout << "Start matrix mulitplication with dot product... " << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    C = matmul::withDotProduct(A, B);
    end = std::chrono::high_resolution_clock::now();

    elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Elapsed time = " << elapsedTime  << std::endl;
    

    return 0;
}