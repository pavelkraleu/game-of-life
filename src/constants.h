//
// Created by Pavel Kral on 24/05/2021.
//

#include "pattern_matcher/RGBColor.h"


#ifndef CPP_SEM_CONST_H
#define CPP_SEM_CONST_H

int const GLIDER_ID_A = 1;
int const GLIDER_ID_B = 2;
int const GLIDER_ID_C = 3;
int const GLIDER_ID_D = 4;
int const STAR_SMALL_ID = 5;
int const STAR_BIG_ID = 6;

const RGBColor GLIDER_COLOR_A = RGBColor(0, 255, 153);
const RGBColor GLIDER_COLOR_B = RGBColor(102, 255, 255);
const RGBColor GLIDER_COLOR_C = RGBColor(153, 153, 255);
const RGBColor GLIDER_COLOR_D = RGBColor(0, 255, 0);
const RGBColor STAR_SMALL_COLOR = RGBColor(255, 204, 0);
const RGBColor STAR_BIG_COLOR = RGBColor(255, 0, 0);

const map<int, RGBColor> COLOR_ID {
        {GLIDER_ID_A, GLIDER_COLOR_A},
        {GLIDER_ID_B, GLIDER_COLOR_B},
        {GLIDER_ID_C, GLIDER_COLOR_C},
        {GLIDER_ID_D, GLIDER_COLOR_D},
        {STAR_SMALL_ID, STAR_SMALL_COLOR},
        {STAR_BIG_ID, STAR_BIG_COLOR},
};

enum SolverType {standard, custom};

#endif