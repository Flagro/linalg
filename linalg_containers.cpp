#include <cstddef>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <random>
#include <type_traits>

#include "linalg_containers.hpp"

//namespace {
double get_random_double(double lower_bound, double upper_bound) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    return unif(dev);
}

long long get_random_integer(double lower_bound, double upper_bound) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(lower_bound, upper_bound);
    return dist6(rng);
}

template <class T>
T get_random_number(T lower_bound, T upper_bound) {
    return std::rand();
    if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        return get_random_double(lower_bound, upper_bound);
    } else {
        return get_random_integer(lower_bound, upper_bound);
    }
}

size_t get_random_index(size_t container_len) {
    return std::rand() % container_len;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, container_len - 1);
    return dist6(rng);
}
//}

namespace fglib {
template <class T>
CSRMatrix<T>::CSRMatrix(size_t n_, double density_) : n(n_), density(density_) {
    static const double sparse_density_threshold = 0.1;
    bool is_sparse = (density <= sparse_density_threshold);
    nnz = n * n * density;
    size_t nz = n * n - nnz;
    bool ignore_duplicates = (nnz >= 100000000ll);
    vals = std::vector<T>(nnz);
    for (auto &el : vals) {
        el = get_random_number<T>(-100, 100);
    }
    std::set<std::pair<size_t, size_t>> generated_indices;
    size_t to_generate_count = (is_sparse ? nnz : nz);
    for (size_t i = 0; i < to_generate_count; ++i) {
        std::pair<size_t, size_t> new_index_pair;
        do {
            new_index_pair = std::pair<size_t, size_t>(get_random_index(n), get_random_index(n));
        } while (!ignore_duplicates && generated_indices.find(new_index_pair) != generated_indices.end());
        generated_indices.insert(new_index_pair);
    }

    rows = std::vector<size_t>(n + 1);
    cols = std::vector<size_t>(nnz);
    size_t cur_row = 0;
    size_t cur_col_id = 0;
    if (is_sparse) {
        for (auto &[row_id, col_id] : generated_indices) {
            while (cur_row <= row_id) {
                rows[cur_row] = cur_col_id;
                ++cur_row;
            }
            cols[cur_col_id] = col_id;
            ++cur_col_id;
        }
    } else {
        for (size_t row_id = 0; row_id < n; ++row_id) {
            for (size_t col_id = 0; col_id < n; ++col_id) {
                if (generated_indices.find({row_id, col_id}) == generated_indices.end()) {
                    while (cur_row <= row_id) {
                        rows[cur_row] = cur_col_id;
                        ++cur_row;
                    }
                    cols[cur_col_id] = col_id;
                    ++cur_col_id;
                }
            }
        }
    }

    while (cur_row <= n + 1) {
        rows[cur_row] = cur_col_id;
        ++cur_row;
    }
}

template <class T>
SparseVector<T>::SparseVector(size_t n_, double density_) : n(n_), density(density_) {
    static const double sparse_density_threshold = 0.1;
    bool is_sparse = (density <= sparse_density_threshold);
    size_t nnz = n * density;
    size_t nz = n - nnz;
    vals = std::vector<T>(nnz);

    for (auto &el : vals) {
        el = get_random_number<T>(-100, 100);
    }

    std::set<size_t> generated_indices;
    size_t to_generate_count = (is_sparse ? nnz : nz);
    for (size_t i = 0; i < to_generate_count; ++i) {
        size_t new_index;
        do {
            new_index = get_random_index(n);
        } while (generated_indices.find(new_index) != generated_indices.end());
        generated_indices.insert(new_index);
    }

    idx = std::vector<size_t>(nnz);
    size_t cur_id = 0;
    if (is_sparse) {
        for (auto id : generated_indices) {
            idx[cur_id] = id;
            ++cur_id;
        }
    } else {
        for (size_t id = 0; id < n; ++id) {
            if (generated_indices.find(id) == generated_indices.end()) {
                idx[cur_id] = id;
                ++cur_id;
            }
        }
    }
}

template<class T>
SparseVector<T>::SparseVector(const std::vector<T>& dense_vector_) : n(dense_vector_.size()) {
    idx = std::vector<size_t>();
    vals = std::vector<T>();
    for (size_t i = 0; i < n; ++i) {
        if (dense_vector_[i]) {
            idx.push_back(i);
            vals.push_back(dense_vector_[i]);
        }
    }
    density = idx.size() / n;
}

template class CSRMatrix<int>;
template class CSRMatrix<long>;
template class CSRMatrix<long long>;
template class CSRMatrix<float>;
template class CSRMatrix<double>;

template class SparseVector<int>;
template class SparseVector<long>;
template class SparseVector<long long>;
template class SparseVector<float>;
template class SparseVector<double>;

} // fglib
