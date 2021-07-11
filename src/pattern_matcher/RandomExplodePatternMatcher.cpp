//
// Created by Pavel Kral on 15/05/2021.
//

#include "RandomExplodePatternMatcher.h"

void RandomExplodePatternMatcher::process_found_pattern(Matrix<bool> *pattern, Matrix<int> *pattern_positions, Matrix<bool> *matrix, size_t row, size_t column) {
    bool should_explode = get_random_true(probability_explode);
    if (!should_explode) {
        return;
    }

    Matrix<bool> *random_matrix = get_random_matrix(pattern->get_height(), pattern->get_width());

    copy_id_to_pattern_matrix(id, random_matrix, pattern_positions, row, column);
    copy_matrix_to_matrix(random_matrix, matrix, row, column);

    delete random_matrix;
}

RandomExplodePatternMatcher::RandomExplodePatternMatcher(int id, int probability, vector<string> & pattern_paths) : BasePatternMatcher(id, pattern_paths), probability_explode(probability) {}

Matrix<bool> *RandomExplodePatternMatcher::get_random_matrix(size_t rows, size_t columns) {
    auto *matrix = new Matrix<bool>(rows, columns);

    for (size_t r = 0; r < matrix->get_height(); r++) {
        for (size_t c = 0; c < matrix->get_width(); c++) {
            bool random_value = rand() % 2 == 0;

            matrix->set(random_value, r, c);
        }
    }

    return matrix;
}

bool RandomExplodePatternMatcher::get_random_true(size_t probability_pct) {
    size_t random_number = rand() % 100 + 1;
    return random_number <= probability_pct;
}
