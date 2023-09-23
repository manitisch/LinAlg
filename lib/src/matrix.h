#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#include <array>
#include <iterator>
#include <stdexcept>
#include <tuple>
#include <type_traits>
	
namespace linalg {
    
template<typename T, size_t Rows, size_t Columns>
class Matrix {
  public:
    using RowIterator = std::array<T, Columns>::iterator;

    class ColumnIterator {
      public:
        using difference_type  = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
    
        ColumnIterator();
        ColumnIterator(pointer ptr) : ptr_(ptr) {};

        reference operator*() const {
            return *ptr_;
        };

        pointer operator->() {
            return ptr_;
        };
        
        ColumnIterator& operator++() {
            ptr_ += Columns;
            return *this;
        };

        ColumnIterator operator++(int) {
            ColumnIterator tmp = *this;
            ++(*this);
            return tmp;
        };

        friend bool operator== (const ColumnIterator& left, const ColumnIterator& right) {
            return left.ptr_ == right.ptr_;
        };

        
        friend bool operator!= (const ColumnIterator& left, const ColumnIterator& right) {
            return left.ptr_ != right.ptr_;
        };
        
      private:
        pointer ptr_;
    };

    Matrix();
    Matrix(std::initializer_list<std::initializer_list<T>> values);

    T& operator()(const size_t row, const size_t column);

    RowIterator rwiseBegin(const size_t row);
    RowIterator rwiseEnd(const size_t row);
    ColumnIterator cwiseBegin(const size_t column);
    ColumnIterator cwiseEnd(const size_t column);

    std::array<T, Columns> getRow(const size_t row);
    std::array<T, Rows> getCol(const size_t column);
    const std::tuple<const size_t, const size_t> shape();

  private:
    std::array<std::array<T, Columns>, Rows> data_;

    static_assert(std::is_scalar<T>(), "Only scalar types are allowed.");
    static_assert(0 < Rows, "Number of rows has to be greater than 0.");
    static_assert(0 < Columns, "Number of columns has to be greater than 0.");
    static_assert(std::forward_iterator<RowIterator>);
    static_assert(std::forward_iterator<ColumnIterator>);
};


template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::Matrix() {
    data_.fill({});
};

template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::Matrix(std::initializer_list<std::initializer_list<T>> values) {
    if(Rows != values.size() || Columns != values.begin()->size()) {
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

template<typename T, size_t Rows, size_t Columns>
T& Matrix<T, Rows, Columns>::operator()(const size_t row, const size_t column) {
    // TODO check bounds
    return data_[row][column];
};

template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::RowIterator Matrix<T, Rows, Columns>::rwiseBegin(const size_t row) {
    if (Rows <= row) {
        throw std::invalid_argument("Row " + std::to_string(row) + " outside range.");
    }

    return data_[row].begin();
}

template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::RowIterator Matrix<T, Rows, Columns>::rwiseEnd(const size_t row) {
    if (Rows <= row) {
        throw std::invalid_argument("Row " + std::to_string(row) + " outside range.");
    }

    return data_[row].end();
}

template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::ColumnIterator Matrix<T, Rows, Columns>::cwiseBegin(const size_t column) {
    if (Columns <= column) {
        throw std::invalid_argument("Column " + std::to_string(column) + " outside range.");
    }

    return ColumnIterator{&data_[0][column]};
}

template<typename T, size_t Rows, size_t Columns>
Matrix<T, Rows, Columns>::ColumnIterator Matrix<T, Rows, Columns>::cwiseEnd(const size_t column) {
    if (Columns <= column) {
        throw std::invalid_argument("Column " + std::to_string(column) + " outside range.");
    }

    return ColumnIterator{&data_[Rows][column]};
}

template<typename T, size_t Rows, size_t Columns>
std::array<T, Columns> Matrix<T, Rows, Columns>::getRow(const size_t row) {
    return data_[row];
}

template<typename T, size_t Rows, size_t Columns>
std::array<T, Rows> Matrix<T, Rows, Columns>::getCol(const size_t column) {
    std::array<T, Rows> tmp_column{};

    for (size_t i = 0; i < Rows; i++) {
        tmp_column[i] = data_[i][column];
    }

    return tmp_column;
}

template<typename T, size_t Rows, size_t Columns>
const std::tuple<const size_t, const size_t> Matrix<T, Rows, Columns>::shape() {
    return {Rows, Columns};
}

} // namespace linalg

#endif // LINALG_MATRIX_H