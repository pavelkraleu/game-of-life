//
// Created by Pavel Kral on 13/05/2021.
//

#ifndef CPP_SEM_BASEPATTERNMATCHER_H
#define CPP_SEM_BASEPATTERNMATCHER_H


#include "../matrix/Matrix.h"
#include "RGBColor.h"
#include <string>

/**
 * Base class for searching for patterns in 2D matrix
 */
class BasePatternMatcher {
public:
/**
 * Load all patterns from supplied paths
 * @param id of given pattern
 * @param pattern_paths paths to patterns representing current matcher
 */
    BasePatternMatcher(int id, const vector<string> & pattern_paths);
    BasePatternMatcher(const BasePatternMatcher & original);
/**
 * Run the matcher on given matrix
 * @param matrix in which to find patterns
 * @param pattern_positions matrix holding ids of detected patterns
 * @param start_row position in the matrix where to search for the pattern
 * @param start_column position in the matrix where to search for the pattern
 */
    void detect_and_process(Matrix<bool> *matrix, Matrix<int> *pattern_positions, size_t start_row, size_t start_column);
    int get_id() const;

    virtual ~BasePatternMatcher();

/**
 * Assigment operator
 * @param original
 * @return
 */
    BasePatternMatcher & operator = (const BasePatternMatcher & original);

private:
/**
 * Check pattern at given position is present in the matrix at given position
 * @param pattern to find
 * @param matrix where to find the pattern
 * @param start_row position in the matrix where to search
 * @param start_column  position in the matrix where to search
 * @return true if pattern is present in the matrix
 */
    static bool pattern_is_in_matrix(Matrix<bool> * pattern, Matrix<bool> *matrix, size_t start_row, size_t start_column);

    virtual void process_found_pattern(Matrix<bool> *pattern, Matrix<int> *pattern_positions, Matrix<bool> *matrix, size_t row, size_t column) = 0;

/**
 * Load patterns from supplied paths to have them ready for later use
 */
    void load_pattern_paths();
    vector<Matrix<bool> *> patterns;
    vector<string> pattern_paths;
protected:
/**
 * Copy given ID to pattern position matrix at corresponding positions from detected pattern
 * @param copy_id ID to be copied
 * @param copy_pattern detected pattern
 * @param pattern_positions matrix where to copy ID
 * @param start_row position where to start copy
 * @param start_column position where to start copy
 */
    static void copy_id_to_pattern_matrix(int copy_id, Matrix<bool> *copy_pattern, Matrix<int> *pattern_positions, size_t start_row, size_t start_column) ;
/**
 * Copy one bool matrix to another
 * @param copy_pattern matrix to be copied
 * @param matrix destination matrix
 * @param start_row destination position
 * @param start_column destination position
 */
    static void copy_matrix_to_matrix(Matrix<bool> *copy_pattern, Matrix<bool> *matrix, size_t start_row, size_t start_column) ;

    int id;
};


#endif //CPP_SEM_BASEPATTERNMATCHER_H
