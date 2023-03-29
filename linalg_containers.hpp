#ifndef LINALG_CONTAINERS_HPP_
#define LINALG_CONTAINERS_HPP_

#include <cstddef>
#include <vector>

namespace fglib {
template <class T>
class CSRMatrix {
public:
    size_t n;
    size_t nnz;
    double density;
    std::vector<size_t> rows;
    std::vector<size_t> cols;
    std::vector<T> vals;

    CSRMatrix(size_t n_, double density_);
};

template <class T>
class SparseVector {
public:
    size_t n;
    double density;
    std::vector<size_t> idx;
    std::vector<T> vals;

    SparseVector(size_t n_, double density_);

    SparseVector(const std::vector<T>& dense_vector_);
};

extern template class CSRMatrix<int>;
extern template class CSRMatrix<long>;
extern template class CSRMatrix<long long>;
extern template class CSRMatrix<float>;
extern template class CSRMatrix<double>;

extern template class SparseVector<int>;
extern template class SparseVector<long>;
extern template class SparseVector<long long>;
extern template class SparseVector<float>;
extern template class SparseVector<double>;

} // fglib

#endif  // LINALG_CONTAINERS_HPP_
