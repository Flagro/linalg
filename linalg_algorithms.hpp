#ifndef LINALG_ALGORITHMS_HPP_
#define LINALG_ALGORITHMS_HPP_

#include <vector>
#include <string>

#include "linalg_containers.hpp"

namespace fglib {
enum class bfs_mode {
    BFS_FAST = 0,
    BFS_SLOW = 1
};

template<class T>
SparseVector<T> bfs(CSRMatrix<T>& matr, size_t start_node, bfs_mode mode);

extern template SparseVector<int> bfs(CSRMatrix<int>&, size_t start_node, bfs_mode);
extern template SparseVector<long> bfs(CSRMatrix<long>&, size_t start_node, bfs_mode);
extern template SparseVector<long long> bfs(CSRMatrix<long long>&, size_t start_node, bfs_mode);
extern template SparseVector<float> bfs(CSRMatrix<float>&, size_t start_node, bfs_mode);
extern template SparseVector<double> bfs(CSRMatrix<double>&, size_t start_node, bfs_mode);

} // fglib

#endif  // LINALG_ALGORITHMS_HPP_
