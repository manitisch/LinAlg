module;

import Matrix;

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <ranges>
#include <tuple>
#include <vector>

export module Tensor;

export namespace linalg {

template<typename T, size_t Rows, size_t Columns>
class Tensor {
  public:
    using Iterator = std::vector<Matrix<T, Rows, Columns>>::iterator;

    Tensor(const size_t depth) {
        data_.reserve(depth);
    }

    Tensor(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values) {
        const size_t depth = values.size();
        data_.reserve(depth);

        for (const auto& val : values) {
            data_.emplace_back(val);
        }
    }

    void append(Matrix<T, Rows, Columns> element) {
        data_.emplace_back(element);
    }

    T& operator()(const size_t depth, const size_t row, const size_t column) {
        return data_[depth](row, column);
    }

    template<size_t Rows2, size_t Columns2>
    friend Tensor<T, Rows, Columns2> operator*(Tensor<T, Rows, Columns>& A, Tensor<T, Rows2, Columns2>& B) {
        if (std::get<0>(A.shape()) != std::get<0>(B.shape())) {
            throw std::invalid_argument("Shapes of tensors do not match.");   
        }
        
        Tensor<T, Rows, Columns2> C{};

        auto b = B.begin();
        auto multiply = [&b, &C](const auto& a){
            C.append(a*(*b));
            b = std::next(b);
        };
 
        std::for_each(A.begin(), A.end(), multiply); // TODO: add execution policy

        return C;
    }

    Iterator begin() {
        return data_.begin();
    }

    Iterator end() {
        return data_.end();
    }

    const std::tuple<const size_t, const size_t, const size_t> shape() const {
        const size_t depth = data_.size();
        return {depth, Rows, Columns};
    }

  private:
    std::vector<Matrix<T, Rows, Columns>> data_;

    static_assert(std::forward_iterator<Iterator>);
};

} // namespace linalg
