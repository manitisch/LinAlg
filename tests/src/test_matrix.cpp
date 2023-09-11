#include <iostream>

#include "matrix.h"

int main() {
    std::cout << "test main" << std::endl;

    auto matrix = linalg::Matrix<float, 3, 4>({{1 ,2, 3, 4},
                                               {1, 2, 3, 4},
                                               {1, 2 ,3, 4}});
    return 0;
}