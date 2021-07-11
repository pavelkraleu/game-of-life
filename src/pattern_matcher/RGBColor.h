//
// Created by Pavel Kral on 16/05/2021.
//

#ifndef CPP_SEM_RGBCOLOR_H
#define CPP_SEM_RGBCOLOR_H


class RGBColor {
public:
    RGBColor(unsigned char red, unsigned char green, unsigned char blue);
    RGBColor(const RGBColor & original);

    unsigned char get_red() const;
    unsigned char get_green() const;
    unsigned char get_blue() const;

private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};


#endif //CPP_SEM_RGBCOLOR_H
