//
// Created by Pavel Kral on 08/05/2021.
//

#ifndef CPP_SEM_PNGOUTPUTPROCESSOR_H
#define CPP_SEM_PNGOUTPUTPROCESSOR_H

#include <string>
#include "BaseOutputProcessor.h"
#include "../matrix/Matrix.h"
#include "../pattern_matcher/BasePatternMatcher.h"
#include <map>

using namespace std;

/**
 * Class responsible for rendering PNG images
 */
class PNGOutputProcessor: public BaseOutputProcessor{
public:
/**
 * Initialize output processor
 * @param output_directory where to render images
 * @param color_id mapping of IDs to RGB colors
 */
    PNGOutputProcessor(string & output_directory, const map<int, RGBColor> & color_id);

/**
 * Copy constructor
 * @param original
 */
    PNGOutputProcessor(const PNGOutputProcessor & original);

    PNGOutputProcessor() = default;

/**
 * Stores given matrix to a PNG file
 * @param matrix to store
 * @param patterns if present, is used to colorize pixels
 * @return true if rendering has been successful
 */
    bool process_matrix(Matrix<bool> *matrix, Matrix<int> * patterns) override;

/**
 * Assigment operator
 * @param original
 * @return
 */
    PNGOutputProcessor & operator = (const PNGOutputProcessor & original);
private:
    size_t frame_number = 0;
    string output_directory;
    map<int, RGBColor> color_id;
/**
 * Get color for a given numeric ID
 * @param id of color to be found
 * @return instance of RGBColor
 */
    RGBColor get_color_by_id(int id) const;
};


#endif //CPP_SEM_PNGOUTPUTPROCESSOR_H
