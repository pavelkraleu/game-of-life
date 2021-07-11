//
// Created by Pavel Kral on 04/05/2021.
//

#include "PNGImageLoader.h"
#include <iostream>

bool PNGImageLoader::load() {
    FILE *fp = fopen(file_path.c_str(), "rb+");

    if(!fp){
        return false;
    }

    unsigned char header[8];
    fread(header, 1, 8, fp);

    // Inspired by https://gist.github.com/niw/5963798

    if(png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, 8)){
        cerr << "File " << file_path <<  " is not PNG" << endl;
        return false;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr){
        cerr << "Unable to load image " << file_path << endl;
        return false;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        cerr << "Unable to load image " << file_path << endl;
        return false;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int color_type = png_get_color_type(png_ptr, info_ptr);

    int bit_depth  = png_get_bit_depth(png_ptr, info_ptr);
    if(bit_depth == 16)
        png_set_strip_16(png_ptr);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);

    if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);


    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);

    png_read_update_info(png_ptr, info_ptr);

    row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (size_t y=0; y<height; y++) {
        row_pointers[y] = (png_bytep) malloc(png_get_rowbytes(png_ptr,info_ptr));
        png_read_row(png_ptr, row_pointers[y], nullptr);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);

    return true;
}

Matrix<bool> * PNGImageLoader::get_matrix() {
    if(!row_pointers){
        throw invalid_argument("Image has not been loaded by method load()");
    }

    auto * matrix = new Matrix<bool>(height, width);

    for (size_t y=0; y<height; y++) {
        png_bytep row = row_pointers[y];
        for (size_t x=0; x<width; x++) {
            png_bytep ptr = &(row[x*4]);

            int red = ptr[0];
            int green = ptr[1];
            int blue = ptr[2];

            size_t bw_value = (red + green + blue) / 3;
            bool is_white = bw_value >= RGB_TO_BW_THRESHOLD;

            matrix->set(is_white, y, x);

#ifdef DEBUG
            printf("Pixel at position [ %d - %d ] has RGBA values: %-3d - %-3d - %-3d - %-3d\n", x, y, red, green, blue, alpha);
#endif
        }
    }

    for (size_t y=0; y<height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    return matrix;
}

PNGImageLoader::PNGImageLoader(const PNGImageLoader &original): BaseImageLoader(original.file_path) {}

PNGImageLoader &PNGImageLoader::operator=(const PNGImageLoader &original) {
    if (this == &original){
        return *this;
    }

    file_path = original.file_path;

    return *this;
}