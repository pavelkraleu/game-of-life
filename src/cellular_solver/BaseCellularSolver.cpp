//
// Created by Pavel Kral on 12/05/2021.
//

#include "BaseCellularSolver.h"

Matrix<bool> *BaseCellularSolver::get_matrix() const {
    return matrix;
}

Matrix<int> *BaseCellularSolver::get_pattern_matrix() const {
    return patterns;
}

BaseCellularSolver::BaseCellularSolver(const BaseCellularSolver &original) {
    matrix = original.get_matrix()->clone();

    if(original.get_pattern_matrix()){
        patterns = original.get_pattern_matrix()->clone();
    }
}

