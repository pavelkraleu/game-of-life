//
// Created by Pavel Kral on 15/05/2021.
//

#ifndef CPP_SEM_RANDOMEXPLODEPATTERNMATCHER_H
#define CPP_SEM_RANDOMEXPLODEPATTERNMATCHER_H


#include "BasePatternMatcher.h"

/**
 * Pattern matcher handling exploding stars
 */
class RandomExplodePatternMatcher: public BasePatternMatcher {
public:
/**
 * Initialize pattern matcher
 * @param id of the pattern
 * @param probability of explosion
 * @param pattern_paths paths to images with the pattern
 */
    RandomExplodePatternMatcher(int id, int probability, vector<string> & pattern_paths);

private:
/**
 * Let found pattern randomly explode.
 * Sets found pattern to a random state and also copies its ID to pattern position.
 * @param pattern which has been detected
 * @param pattern_positions matrix holding IDs of detected patterns
 * @param matrix holding cellular automata state
 * @param row where pattern has been detected
 * @param column where pattern has been detected
 */
    void process_found_pattern(Matrix<bool> *pattern, Matrix<int> *pattern_positions, Matrix<bool> *matrix, size_t row, size_t column) override;
/**
 * Return true at given percentage
 * @param probability_pct percentage at which should method return true
 * @return random true value
 */
    static bool get_random_true(size_t probability_pct);
/**
 * Generates matrix with random bool values
 * @param rows height of the matrix
 * @param columns width of the matrix
 * @return random matrix
 */
    static Matrix<bool> * get_random_matrix(size_t rows, size_t columns);
    int probability_explode;
};


#endif //CPP_SEM_RANDOMEXPLODEPATTERNMATCHER_H
