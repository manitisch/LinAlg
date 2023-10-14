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

    Matrix() {
        data_.fill(T{});
    }

    Matrix(std::initializer_list<std::initializer_list<T>> values) {
        if(Rows != values.size() || Columns != values.begin()->size()) {
            throw std::invalid_argument("Size of initializer list does not match matrix dimensions.");
        }

        size_t row = 0;
        for (const auto& rows : values) {
            size_t column = 0;
            for  (const auto& value : rows) {
                data_[Columns*row + column] = value;
                ++column;
            }
            ++row;
        }
    }

    T& operator()(const size_t row, const size_t column) {
        return data_[Columns*row + column];
    }

    RowIterator rwiseBegin(const size_t row) {
        if (Rows <= row) {
            throw std::invalid_argument("Row " + std::to_string(row) + " outside range.");
        }

        return data_.begin() + (row * Columns);
    }

    RowIterator rwiseEnd(const size_t row) {
        if (Rows <= row) {
            throw std::invalid_argument("Row " + std::to_string(row) + " outside range.");
        }

        return data_.begin() + Columns + (row * Columns);
    }

    ColumnIterator cwiseBegin(const size_t column) {
        if (Columns <= column) {
            throw std::invalid_argument("Column " + std::to_string(column) + " outside range.");
        }

        return ColumnIterator{data_.begin() + column};
    }

    ColumnIterator cwiseEnd(const size_t column) {
        if (Columns <= column) {
            throw std::invalid_argument("Column " + std::to_string(column) + " outside range.");
        }

        return ColumnIterator{data_.end() + column};
    }

    const std::tuple<const size_t, const size_t> shape() {
        return {Rows, Columns};
    }

  private:
    std::array<T, Columns*Rows> data_;

    static_assert(std::is_scalar<T>(), "Only scalar types are allowed.");
    static_assert(0 < Rows, "Number of rows has to be greater than 0.");
    static_assert(0 < Columns, "Number of columns has to be greater than 0.");
    static_assert(std::forward_iterator<RowIterator>);
    static_assert(std::forward_iterator<ColumnIterator>);
};
} // namespace linalg

#endif // LINALG_MATRIX_H