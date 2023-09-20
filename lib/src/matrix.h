#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#include <array>
#include <iterator>
#include <stdexcept>
#include <tuple>
	
namespace linalg {
    
template<typename T, size_t Rows, size_t Cols>
class Matrix {
  public:
    using RowIterator = std::array<T, Cols>::iterator;

    class ColumnIterator {
      public:
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;
    
        ColumnIterator();
        ColumnIterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const { /*return *ptr_;*/ }
        pointer operator->() { /*return ptr_; */}
        ColumnIterator& operator++() { /*ptr_++; return *this;*/ }  
        ColumnIterator operator++(int) {/*ColumnIterator tmp = *this; ++(*this); return tmp;*/ }
        friend bool operator== (const ColumnIterator& a, const ColumnIterator& b) { /*return a.ptr_ == b.ptr_; */}
        //friend bool operator!= (const ColumnIterator& a, const ColumnIterator& b) { /*return a.ptr_ != b.ptr_; */} // not needed

      private:
        pointer ptr_;
        
    };

    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> values);

    T& operator()(const size_t row, const size_t col);

    RowIterator rwiseBegin(const size_t row);
    RowIterator rwiseEnd(const size_t row);
    ColumnIterator cwiseBegin(const size_t col);
    ColumnIterator cwiseEnd(const size_t col);

    std::array<T, Cols> getRow(const size_t row);
    std::array<T, Rows> getCol(const size_t col);
    const std::tuple<const size_t, const size_t> shape();

  private:
    std::array<std::array<T, Cols>, Rows> data_;

    static_assert(std::forward_iterator<RowIterator>);
    static_assert(std::forward_iterator<ColumnIterator>);
    ColumnIterator columnIterator = ColumnIterator(nullptr);
};

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::Matrix() {
    data_.fill({});
};

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::Matrix(std::initializer_list<std::initializer_list<T>> values) {
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

template<typename T, size_t Rows, size_t Cols>
T& Matrix<T, Rows, Cols>::operator()(const size_t row, const size_t col) {
    // TODO check bounds
    return data_[row][col];
};

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::RowIterator Matrix<T, Rows, Cols>::rwiseBegin(const size_t row) {
    // TODO check bounds
    return data_[row].begin();
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::RowIterator Matrix<T, Rows, Cols>::rwiseEnd(const size_t row) {
    // TODO check bounds
    return data_[row].end();
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::ColumnIterator Matrix<T, Rows, Cols>::cwiseBegin(const size_t col) {
    // TODO
}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::ColumnIterator Matrix<T, Rows, Cols>::cwiseEnd(const size_t col) {
    // TODO
}

template<typename T, size_t Rows, size_t Cols>
std::array<T, Cols> Matrix<T, Rows, Cols>::getRow(const size_t row) {
    return data_[row];
}

template<typename T, size_t Rows, size_t Cols>
std::array<T, Rows> Matrix<T, Rows, Cols>::getCol(const size_t col) {
    std::array<T, Rows> column{};

    for (size_t i = 0; i < Rows; i++) {
        column[i] = data_[i][col];
    }

    return column;
}

template<typename T, size_t Rows, size_t Cols>
const std::tuple<const size_t, const size_t> Matrix<T, Rows, Cols>::shape() {
    return {Rows, Cols};
}

} // namespace linalg

#endif // LINALG_MATRIX_H