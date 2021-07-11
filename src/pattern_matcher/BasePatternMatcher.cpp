//
// Created by Pavel Kral on 13/05/2021.
//

#include "BasePatternMatcher.h"
#include "../image_loader/PNGImageLoader.h"
#include <stdexcept>
#include <iostream>

BasePatternMatcher::BasePatternMatcher(int id, const vector<string> & pattern_paths): pattern_paths(pattern_paths), id(id) {
    load_pattern_paths();
}

BasePatternMatcher::BasePatternMatcher(const BasePatternMatcher &original): pattern_paths(original.pattern_paths), id(original.id) {
    load_pattern_paths();
}

void BasePatternMatcher::detect_and_process(Matrix<bool> *matrix, Matrix<int> *pattern_positions, size_t start_row, size_t start_column) {
    for(auto pattern: patterns){
        if(!pattern_is_in_matrix(pattern, matrix, start_row, start_column)){
            continue;
        }

        process_found_pattern(pattern, pattern_positions, matrix, start_row, start_column);
    }
}

bool BasePatternMatcher::pattern_is_in_matrix(Matrix<bool> * pattern, Matrix<bool> * matrix, size_t start_row, size_t start_column) {
    for (size_t r=0; r < pattern->get_height(); r++) {
        for (size_t c = 0; c < pattern->get_width(); c++) {
            size_t row_position = start_row + r;
            size_t column_position = start_column + c;

            if(matrix->is_not_inside_matrix(row_position, column_position)){
                return false;
            }

            if(matrix->get(row_position, column_position) != pattern->get(r, c)){
                return false;
            }
        }
    }
    return true;
}

int BasePatternMatcher::get_id() const {
    return id;
}

void BasePatternMatcher::copy_id_to_pattern_matrix(int copy_id, Matrix<bool> *copy_pattern, Matrix<int> *pattern_positions, size_t start_row, size_t start_column) {
    for (size_t r=0; r < copy_pattern->get_height(); r++) {
        for (size_t c = 0; c < copy_pattern->get_width(); c++) {
            size_t row_position = start_row + r;
            size_t column_position = start_column + c;

            if(pattern_positions->is_not_inside_matrix(row_position, column_position)){
                continue;
            }

            if(copy_pattern->get(r, c)){
                pattern_positions->set(copy_id, row_position, column_position);
            }
        }
    }
}

void BasePatternMatcher::copy_matrix_to_matrix(Matrix<bool> *copy_pattern, Matrix<bool> *matrix, size_t start_row, size_t start_column) {
    for (size_t r=0; r < copy_pattern->get_height(); r++) {
        for (size_t c = 0; c < copy_pattern->get_width(); c++) {
            size_t row_position = start_row + r;
            size_t column_position = start_column + c;

            if(matrix->is_not_inside_matrix(row_position, column_position)){
                continue;
            }

            matrix->set(copy_pattern->get(r, c), row_position, column_position);
        }
    }
}

BasePatternMatcher::~BasePatternMatcher() {
    for(auto pattern: patterns){
        delete pattern;
    }
}

void BasePatternMatcher::load_pattern_paths() {
    for(auto path: pattern_paths){
        PNGImageLoader loader = PNGImageLoader(path);
        if(!loader.load()){
            cerr << "Unable to load pattern from file " << path << endl;
            cerr << "Ensure you have set PATTERNS_DIR correctly" << endl;
            throw invalid_argument("Unable to load pattern file");
        }
        Matrix<bool> * m = loader.get_matrix();
        patterns.push_back(m);

    }
}

BasePatternMatcher &BasePatternMatcher::operator=(const BasePatternMatcher &original) {
    if (this == &original){
        return *this;
    }

    for(auto & pattern: patterns){
        delete pattern;
    }

    pattern_paths = original.pattern_paths;
    load_pattern_paths();

    return *this;
}
