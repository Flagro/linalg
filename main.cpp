#include "omp.h"
#include <iostream>
#include <cstddef>

#include "linalg_containers.hpp"
#include "linalg_operations.hpp"
#include "linalg_algorithms.hpp"

typedef double value_type;

int main(int argc, char *argv[]){
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    
    size_t n = std::stoi(argv[1]);
    double density = std::stod(argv[2]);

    fglib::CSRMatrix<value_type> matr(n, density);
    /*
    std::cout << "Generated matrix:" << std::endl << "rows: ";
    for (auto el : matr.rows) {
        std::cout << el << " ";
    }
    std::cout << std::endl << "cols: ";
    for (auto el : matr.cols) {
        std::cout << el << " ";
    }
    std::cout << std::endl << "vals: ";
    for (auto el : matr.vals) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    */
    fglib::SparseVector<value_type> vec(n, density);
    std::cout << "Everything generated, running cold calls" << std::endl;
    for (int i = 0; i < 10; ++i) {
        fglib::spmspv_fast(matr, vec); // cold calls
    }
    std::cout << "cold calls done" << std::endl;
    omp_set_num_threads(4);
    double t1 = omp_get_wtime();
    //auto result = fglib::bfs(matr, 0, fglib::bfs_mode::BFS_FAST);
    for (int i = 0; i < 1000000; ++i) {
        fglib::spmspv_fast(matr, vec);
    }
    double t2 = omp_get_wtime();
    for (int i = 0; i < 1000000; ++i) {
        fglib::spmspv_slow(matr, vec);
    }
    double t3 = omp_get_wtime();
    std::cout << t2 - t1 << " " << t3 - t2 << std::endl;
    return 0;
}
