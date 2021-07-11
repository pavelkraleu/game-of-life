//
// Created by Pavel Kral on 04/05/2021.
//

#ifndef CPP_SEM_GOLCELLULARSOLVER_H
#define CPP_SEM_GOLCELLULARSOLVER_H

#include "BaseCellularSolver.h"
#include "../pattern_matcher/BasePatternMatcher.h"

/**
 * Cellular automata solver of Conway's Game of Life
 */
class GoLCellularSolver: public BaseCellularSolver{
public:
/**
 * Constructor to initialize Game of Life cellular solver
 * @param matrix image as initial state
 * @param pattern_matchers matchers to be executed after each step
 */
    GoLCellularSolver(Matrix<bool> *matrix, vector<BasePatternMatcher *> pattern_matchers);
    GoLCellularSolver() = default;

    virtual ~GoLCellularSolver();

/**
 * Assigment operator
 * @param original
 * @return
 */
    GoLCellularSolver & operator = (const GoLCellularSolver & original);

protected:
/**
 * Computes number of live cells around given cell
 * @param row of current cell
 * @param column of current cell
 * @param area in which we find live cells
 * @param m_copy Matrix in which we find number of live cells
 * @return Number of cells alive
 */
    size_t alive_cells_around(size_t row, size_t column, size_t area, Matrix<bool> * m_copy) const;
    vector<BasePatternMatcher *> pattern_matchers;
/**
 * Computes next steps in Conway's Game of Life
 */
    void run_standard_gol();
/**
 * Execute pattern matchers to modify the game state or detect patterns
 */
    void execute_pattern_matchers();
/**
 * Compute next step of the cellular automata
 */
    void next();
};


#endif //CPP_SEM_GOLCELLULARSOLVER_H
