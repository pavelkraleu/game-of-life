//
// Created by Pavel Kral on 04/05/2021.
//

#ifndef CPP_SEM_PNGIMAGELOADER_H
#define CPP_SEM_PNGIMAGELOADER_H

#include <png.h>
#include "BaseImageLoader.h"

/**
 * Class responsible for loading data from PNG images
 */
class PNGImageLoader : public BaseImageLoader{
public:
    explicit PNGImageLoader(string &file_path) : BaseImageLoader(file_path) {}
/**
 * Load the PNG image
 * This method is able to read RGB or RGBA images
 * @return true if loading of the image has been successful or not
 */
    bool load() override;
/**
 * Method loads the image which has been previously loaded by method load()
 * Image is converted to a binary form
 * @return Matrix of bool values
 */
    Matrix<bool> * get_matrix() override;
/**
 * Copy constructor
 * It is still needed to call load() on a new copy
 * @param original
 */
    PNGImageLoader(const PNGImageLoader & original);
/**
 * Assigment operator.
 * It is still needed to call load() after the assigment.
 * @param original
 * @return
 */
    PNGImageLoader & operator = (const PNGImageLoader & original);
private:
    png_bytep * row_pointers = nullptr;
};


#endif //CPP_SEM_PNGIMAGELOADER_H
