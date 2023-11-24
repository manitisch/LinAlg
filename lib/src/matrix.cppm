module;

#include <array>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <tuple>
#include <type_traits>
	
export module Matrix;

export namespace linalg {
    
template<typename T, size_t Rows, size_t Columns>
requires std::is_scalar_v<T> && (0 < Rows) && (0 < Columns)
class Matrix {
  public:
    using Iterator = std::array<T, Rows*Columns>::iterator;
    using ConstIterator = std::array<T, Rows*Columns>::const_iterator;
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

    const T& operator()(const size_t row, const size_t column) const {
        return data_[Columns*row + column];
    }

    template<size_t Rows2, size_t Columns2>
    requires (Columns == Rows2)
    friend Matrix<T, Rows, Columns2> operator*(const Matrix<T, Rows, Columns>& A, const Matrix<T, Rows2, Columns2>& B) {        
        Matrix<T, Rows, Columns2> C{};

        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = 0; j < Columns; j++) {
                for (size_t k = 0; k < Columns2; k++) {
                    C(i, k) += A(i, j) * B(j, k);
                }
            }
        }

        return C;
    }

    Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& B) {
        Matrix<T, Rows, Columns> C{};
        for (size_t i = 0; i < Rows; i++) {
            for (size_t j = 0; j < Columns; j++) {
                C(i, j) = this->operator()(i, j) + B(i, j);
            }
        }
        
        return C;
    };

    Iterator begin() {
        return data_.begin();
    }

    Iterator end() {
        return data_.end();
    }

    ConstIterator cbegin() const {
        return data_.cbegin();
    }

    ConstIterator cend() const {
        return data_.cend();
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

    const std::tuple<const size_t, const size_t> shape() const {
        return {Rows, Columns};
    }

  private:
    std::array<T, Rows*Columns> data_;

    static_assert(std::forward_iterator<RowIterator>);
    static_assert(std::forward_iterator<ColumnIterator>);
};
} // namespace linalg
