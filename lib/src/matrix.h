#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#include <array>
#include <stdexcept>
	

namespace linalg {
    
template<typename T, size_t Rows, size_t Cols>
class Matrix {
  public:
    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> values);

    T get_elem(const size_t row, const size_t col);

  private:
    std::array<std::array<T, Cols>, Rows> data_;
};

template<typename T, size_t Cols, size_t Rows>
Matrix<T, Cols, Rows>::Matrix() {
    data_.fill({});
};

template<typename T, size_t Cols, size_t Rows>
Matrix<T, Cols, Rows>::Matrix(std::initializer_list<std::initializer_list<T>> values) {
    if(Rows != values.size() || Cols != values.begin()->size()) {
        throw std::invalid_argument("Size of initializer list does not match matrix dimensions.");
    }

    // TODO maybe with iterator or for_each?
    size_t row = 0;
    for (const auto& rows : values) {
        size_t col = 0;
        for  (const auto& value : rows) {
            data_[row][col] = value;
            ++col;
        }
        ++row;
    }
};

} // namespace linalg

#endif // LINALG_MATRIX_H