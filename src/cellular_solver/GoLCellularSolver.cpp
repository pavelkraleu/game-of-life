//
// Created by Pavel Kral on 04/05/2021.
//

#include "GoLCellularSolver.h"

using namespace std;


GoLCellularSolver::GoLCellularSolver(Matrix<bool> *matrix, vector<BasePatternMatcher *> pattern_matchers) : BaseCellularSolver(matrix), pattern_matchers(move(pattern_matchers)) {
    patterns = new Matrix<int>(matrix->get_height(), matrix->get_width());
}

size_t GoLCellularSolver::alive_cells_around(size_t row, size_t column, size_t area, Matrix<bool> * m_copy) const {
    size_t start_column = column > area ? column - area : 0;
    size_t start_row = row > area ? row - area : 0;

    size_t stop_column = column + area;
    size_t stop_row = row + area;

    size_t alive = 0;
    for(size_t r=start_row;r<=stop_row;r++){
        for(size_t c=start_column;c<=stop_column;c++){
            bool is_current_cell = c == column && r == row;
            bool is_negative = r < 0  || c < 0;

            if(is_negative || matrix->is_not_inside_matrix(r, c) || is_current_cell){
                continue;
            }

            alive += m_copy->get(r, c);
        }
    }

    return alive;
}

void GoLCellularSolver::next() {
    run_standard_gol();
    execute_pattern_matchers();
}

GoLCellularSolver::~GoLCellularSolver() {
    delete patterns;
}

void GoLCellularSolver::run_standard_gol() {
    Matrix<bool> * m_copy = matrix->clone();

    for(size_t row=0; row < matrix->get_height(); row++){
        for(size_t column=0; column < matrix->get_width(); column++){
            size_t alive = alive_cells_around(row, column, 1, m_copy);
            bool current_state = matrix->get(row, column);

            if(current_state && (alive == 2 || alive == 3)){
                matrix->set(true, row, column);
            }
            else if(!current_state && alive == 3){
                matrix->set(true, row, column);
            } else {
                matrix->set(false, row, column);
            }
        }
    }

    delete m_copy;
}

void GoLCellularSolver::execute_pattern_matchers() {
    patterns->clear();

    for (size_t r=0; r < matrix->get_height(); r++) {
        for (size_t c = 0; c < matrix->get_width(); c++) {
            for(auto matcher: pattern_matchers){
                matcher->detect_and_process(matrix, patterns, r, c);
            }
        }
    }
}

GoLCellularSolver &GoLCellularSolver::operator=(const GoLCellularSolver &original) {
    if (this == &original){
        return *this;
    }

    delete matrix;
    delete patterns;

    matrix = original.get_matrix()->clone();
    if(original.get_pattern_matrix()){
        patterns = original.get_pattern_matrix()->clone();
    }

    return *this;
}