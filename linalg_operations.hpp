#ifndef LINALG_OPERATIONS_HPP_
#define LINALG_OPERATIONS_HPP_

#include "linalg_containers.hpp"

namespace fglib {
enum class operation_mode {
    OP_FAST = 0,
    OP_SLOW = 1
};

template<class T>
SparseVector<T> spmspv(CSRMatrix<T>& matrix, SparseVector<T>& vector, operation_mode mode) {
    if (mode == operation_mode::OP_FAST) {
        return spmspv_fast(matrix, vector);
    } else {
        return spmspv_slow(matrix, vector);
    }
}

template<class T>
SparseVector<T> spmspv_fast(CSRMatrix<T>& matrix, SparseVector<T>& vector);

template<class T>
SparseVector<T> spmspv_slow(CSRMatrix<T>& matrix, SparseVector<T>& vector);

extern template SparseVector<int> spmspv_fast(CSRMatrix<int>&, SparseVector<int>&);
extern template SparseVector<long> spmspv_fast(CSRMatrix<long>&, SparseVector<long>&);
extern template SparseVector<long long> spmspv_fast(CSRMatrix<long long>&, SparseVector<long long>&);
extern template SparseVector<float> spmspv_fast(CSRMatrix<float>&, SparseVector<float>&);
extern template SparseVector<double> spmspv_fast(CSRMatrix<double>&, SparseVector<double>&);

extern template SparseVector<int> spmspv_slow(CSRMatrix<int>&, SparseVector<int>&);
extern template SparseVector<long> spmspv_slow(CSRMatrix<long>&, SparseVector<long>&);
extern template SparseVector<long long> spmspv_slow(CSRMatrix<long long>&, SparseVector<long long>&);
extern template SparseVector<float> spmspv_slow(CSRMatrix<float>&, SparseVector<float>&);
extern template SparseVector<double> spmspv_slow(CSRMatrix<double>&, SparseVector<double>&);
} // fglib

#endif  // LINALG_OPERATIONS_HPP_
