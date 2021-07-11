//
// Created by Pavel Kral on 04/05/2021.
//

#ifndef CPP_SEM_BASECELLULARSOLVER_H
#define CPP_SEM_BASECELLULARSOLVER_H


#include "../matrix/Matrix.h"

/**
 * Base class of cellular automata solver
 */
class BaseCellularSolver {
public:
/**
 * Initialize cellular solver
 * @param matrix with image as initial state
 */
    explicit BaseCellularSolver(Matrix<bool> * matrix): matrix(matrix){}
/**
 * Copy constructor
 * @param original cellular solver to be copies
 */
    BaseCellularSolver(const BaseCellularSolver & original);

    virtual ~BaseCellularSolver() {
        delete matrix;
    }

    virtual void next() = 0;
/**
 * Get current state matrix
 * @return matrix with the current state
 */
    Matrix<bool> * get_matrix() const;
/**
 * Get matrix with detected patterns
 * @return matrix with patterns
 */
    Matrix<int> * get_pattern_matrix() const;

protected:
    Matrix<bool> * matrix = nullptr;
    Matrix<int> * patterns = nullptr;
    size_t step_number = 0;
};



#endif //CPP_SEM_BASECELLULARSOLVER_H
