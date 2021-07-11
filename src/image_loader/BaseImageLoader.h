//
// Created by Pavel Kral on 04/05/2021.
//
#include <string>
#include <utility>
#include "../matrix/Matrix.h"

#ifndef CPP_SEM_BASEIMAGELOADER_H
#define CPP_SEM_BASEIMAGELOADER_H

using namespace std;

/**
 * Base class for loading data from Images
 */
class BaseImageLoader {
public:
/**
 * Initialize image loader
 * @param file_path path to the image
 */
    explicit BaseImageLoader(string  file_path): file_path(move(file_path)){};

    virtual bool load() = 0;
    virtual Matrix<bool> * get_matrix() = 0;

protected:
    size_t height = 0;
    size_t width = 0;
    string file_path;
    size_t const RGB_TO_BW_THRESHOLD = 100;
};


#endif //CPP_SEM_BASEIMAGELOADER_H
