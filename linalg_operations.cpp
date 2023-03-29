#include "omp.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstddef>

#include "linalg_containers.hpp"
#include "linalg_operations.hpp"

namespace fglib {
template<class T>
SparseVector<T> spmspv_fast(CSRMatrix<T>& matr, SparseVector<T>& vec) {
    const auto n = matr.n;
    std::vector<T> result(n);

    #pragma omp parallel
    {
        #pragma omp for
        for (size_t i = 0; i < n; ++i) {
            result[i] = 0;
        }

        #pragma omp for
        for (size_t i = 0; i < vec.idx.size(); ++i) {
            size_t ind = vec.idx[i];
            T vec_val = vec.vals[i];

            size_t row_start = matr.rows[ind];
            size_t row_end = matr.rows[ind + 1];
            
            for (size_t j = row_start; j < row_end; ++j) {
                size_t dest_ind = matr.cols[j];
                T matr_val = matr.vals[j];

                #pragma omp atomic
                result[dest_ind] += matr_val * vec_val;
            }
        }
    }

    return SparseVector(result);
}

template<class T>
SparseVector<T> spmspv_slow(CSRMatrix<T>& matr, SparseVector<T>& vec) {
    const auto n = matr.n;
    std::vector<T> result(n);

    
    #pragma omp parallel for
    for (size_t i = 0; i < n; ++i) {
        result[i] = 0;
    }

    #pragma omp parallel for
    for (size_t i = 0; i < vec.idx.size(); ++i) {
        size_t ind = vec.idx[i];
        T vec_val = vec.vals[i];

        size_t row_start = matr.rows[ind];
        size_t row_end = matr.rows[ind + 1];
        
        for (size_t j = row_start; j < row_end; ++j) {
            size_t dest_ind = matr.cols[j];
            T matr_val = matr.vals[j];

            #pragma omp atomic
            result[dest_ind] += matr_val * vec_val;
        }
    }

    return SparseVector(result);
}

template SparseVector<int> spmspv_fast(CSRMatrix<int>&, SparseVector<int>&);
template SparseVector<long> spmspv_fast(CSRMatrix<long>&, SparseVector<long>&);
template SparseVector<long long> spmspv_fast(CSRMatrix<long long>&, SparseVector<long long>&);
template SparseVector<float> spmspv_fast(CSRMatrix<float>&, SparseVector<float>&);
template SparseVector<double> spmspv_fast(CSRMatrix<double>&, SparseVector<double>&);

template SparseVector<int> spmspv_slow(CSRMatrix<int>&, SparseVector<int>&);
template SparseVector<long> spmspv_slow(CSRMatrix<long>&, SparseVector<long>&);
template SparseVector<long long> spmspv_slow(CSRMatrix<long long>&, SparseVector<long long>&);
template SparseVector<float> spmspv_slow(CSRMatrix<float>&, SparseVector<float>&);
template SparseVector<double> spmspv_slow(CSRMatrix<double>&, SparseVector<double>&);

} // fglib
