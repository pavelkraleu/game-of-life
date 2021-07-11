//
// Created by Pavel Kral on 14/05/2021.
//

#ifndef CPP_SEM_COLORIZEPATTERNMATCHER_H
#define CPP_SEM_COLORIZEPATTERNMATCHER_H


#include "BasePatternMatcher.h"
#include "RGBColor.h"

/**
 * Class for coloring certain known patterns
 */
class ColorizePatternMatcher: public BasePatternMatcher {
public:
    ColorizePatternMatcher(int id, const vector<string> &patternPaths);

private:
/**
 * Copy ID to the pattern matrix which is used for rendering
 * @param pattern which has been detected
 * @param pattern_positions matrix where to copy the ID
 * @param matrix with cellular automata
 * @param row where to start copy
 * @param column where to start copy
 */
    void process_found_pattern(Matrix<bool> *pattern, Matrix<int> *pattern_positions, Matrix<bool> *matrix, size_t row, size_t column) override;
};


#endif //CPP_SEM_COLORIZEPATTERNMATCHER_H
