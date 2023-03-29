#include <vector>
#include <string>

#include "linalg_containers.hpp"
#include "linalg_operations.hpp"
#include "linalg_algorithms.hpp"

namespace fglib {
template<class T>
SparseVector<T> bfs(CSRMatrix<T>& matr, size_t start_node, bfs_mode mode) {
    const auto n = matr.n;
    std::vector<T> result(n, 0);

    std::vector<T> f1(n, 0);
    f1[start_node] = 1;
    std::vector<T> f2(n);

    T succ = 0.f;
    size_t unvisited = n;

    for (size_t i = 1; i <= n; ++i) {
        /*
        unvisited -= static_cast<int>(succ);
        assign<T, T, T>(result, &f1, GrB_NULL, iter, GrB_ALL, n, desc);
        desc->toggle(GrB_MASK);
        vxm<T, T, T, T>(&f2, v, GrB_NULL, LogicalOrAndSemiring<T>(), &f1, A, GrB_DESC_SC);
        desc->toggle(GrB_MASK);

        f2.swap(&f1);
        reduce<T, T>(&succ, GrB_NULL, PlusMonoid<T>(), &f1, desc);
        /* to be clear with the experiment
        if (succ == 0) {
            break;
        }
        */
    }
    
    return SparseVector(result);
}

template SparseVector<int> bfs(CSRMatrix<int>&, size_t start_node, bfs_mode);
template SparseVector<long> bfs(CSRMatrix<long>&, size_t start_node, bfs_mode);
template SparseVector<long long> bfs(CSRMatrix<long long>&, size_t start_node, bfs_mode);
template SparseVector<float> bfs(CSRMatrix<float>&, size_t start_node, bfs_mode);
template SparseVector<double> bfs(CSRMatrix<double>&, size_t start_node, bfs_mode);

} // fglib
