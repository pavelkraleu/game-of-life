//
// Created by Pavel Kral on 08/05/2021.
//

#include "PNGOutputProcessor.h"
#include <iostream>
#include "png.h"

bool PNGOutputProcessor::process_matrix(Matrix<bool> *matrix, Matrix<int> * patterns) {
    string file_name = output_directory + "/" + to_string(frame_number) + ".png";
    FILE *fp = fopen(file_name.c_str(), "wb");
    if (!fp){
        cerr << "Unable to write to a file " << file_name << endl;
        return false;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, fp);

    png_jmpbuf(png_ptr);

    png_set_IHDR(png_ptr, info_ptr, (int)matrix->get_width(), (int)matrix->get_height(),
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);
    png_jmpbuf(png_ptr);

    png_bytep * row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * matrix->get_height());

    for (size_t r=0; r < matrix->get_height(); r++) {
        row_pointers[r] = (png_bytep) malloc(png_get_rowbytes(png_ptr, info_ptr));
        png_bytep row = row_pointers[r];

        for (size_t c=0; c < matrix->get_width(); c++) {
            png_bytep ptr = &(row[c * 3]);

            if(patterns && patterns->get(r, c) != 0){
                RGBColor color = get_color_by_id(patterns->get(r, c));
                ptr[0] = color.get_red();
                ptr[1] = color.get_green();
                ptr[2] = color.get_blue();

            } else {
                unsigned char pixel_value = matrix->get(r, c) * 255;
                ptr[0] = pixel_value;
                ptr[1] = pixel_value;
                ptr[2] = pixel_value;
            }
        }
    }

    if (setjmp(png_jmpbuf(png_ptr))){
        cerr << "Error during writing bytes" << endl;
        return false;
    }

    png_write_image(png_ptr, row_pointers);


    if (setjmp(png_jmpbuf(png_ptr))){
        cerr << "Error during end of write" << endl;
        return false;
    }

    png_write_end(png_ptr, nullptr);

    for (size_t y=0; y<matrix->get_height(); y++){
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    frame_number++;
    cout << "Image saved to " << file_name << endl;
    return true;
}

PNGOutputProcessor::PNGOutputProcessor(string & output_directory, const map<int, RGBColor> & color_id): output_directory(output_directory), color_id(color_id) {}

RGBColor PNGOutputProcessor::get_color_by_id(int id) const {
    return color_id.at(id);
}

PNGOutputProcessor::PNGOutputProcessor(const PNGOutputProcessor &original): frame_number(original.frame_number), output_directory(original.output_directory), color_id(original.color_id) {}

PNGOutputProcessor &PNGOutputProcessor::operator=(const PNGOutputProcessor &original) {
    if (this == &original){
        return *this;
    }

    frame_number = original.frame_number;
    output_directory = original.output_directory;
    color_id = original.color_id;

    return *this;
}
