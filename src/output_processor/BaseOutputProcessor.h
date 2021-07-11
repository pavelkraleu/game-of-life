//
// Created by Pavel Kral on 08/05/2021.
//

#ifndef CPP_SEM_BASEOUTPUTPROCESSOR_H
#define CPP_SEM_BASEOUTPUTPROCESSOR_H

#include "../matrix/Matrix.h"

/**
 * Base class for rendering output images
 */
class BaseOutputProcessor {
public:
    BaseOutputProcessor() = default;
    virtual bool process_matrix(Matrix<bool> * matrix, Matrix<int> * patterns) = 0;
};

#endif //CPP_SEM_BASEOUTPUTPROCESSOR_H
