//
// Created by Pavel Kral on 16/05/2021.
//

#include "RGBColor.h"

unsigned char RGBColor::get_red() const {
    return red;
}

unsigned char RGBColor::get_green() const {
    return green;
}

unsigned char RGBColor::get_blue() const {
    return blue;
}

RGBColor::RGBColor(unsigned char red, unsigned char green, unsigned char blue) : red(red), green(green), blue(blue) {}

RGBColor::RGBColor(const RGBColor &original) = default;
