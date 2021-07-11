//
// Created by Pavel Kral on 14/05/2021.
//

#include "ColorizePatternMatcher.h"

ColorizePatternMatcher::ColorizePatternMatcher(int id, const vector<string> & patternPaths) : BasePatternMatcher(id, patternPaths) {}

void ColorizePatternMatcher::process_found_pattern(Matrix<bool> *pattern, Matrix<int> *pattern_positions, Matrix<bool> *matrix, size_t row, size_t column) {
    copy_id_to_pattern_matrix(id, pattern, pattern_positions, row, column);
}
