module;

import Matrix;

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

    T& operator()(const size_t depth, const size_t row, const size_t column) {
        return data_[depth](row, column);
    }

  private:
    std::vector<Matrix<T, Rows, Columns>> data_;

    static_assert(std::forward_iterator<Iterator>);
};

} // namespace linalg
