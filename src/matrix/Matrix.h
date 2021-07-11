//
// Created by Pavel Kral on 04/05/2021.
//

#ifndef CPP_SEM_MATRIX_H
#define CPP_SEM_MATRIX_H


#include <cstdio>
#include <vector>

using namespace std;

/**
 * Class used to represent 2D matrix of ints or bools
 */
template <typename T>
class Matrix {
public:
/**
 * Initialize 2D matrix
 * @param rows is number of rows in the matrix
 * @param columns is number of columns in the matrix
 */
    Matrix(size_t rows, size_t columns);
    ~Matrix();
    Matrix * clone();
/**
 * Set value in the matrix
 * @param value we want to set in the matrix
 * @param row of the value
 * @param column column of the value
 */
    void set(T value, size_t row, size_t column);
/**
 * Get the value from the matrix
 * @param row of the value
 * @param column of the value
 * @return value in given location
 */
    T get(size_t row, size_t column) const;
#ifdef DEBUG
    void check_input(size_t row, size_t column) const;
    void print() const;
#endif
/**
 * Return width of the matrix
 * @return width of the matrix
 */
    size_t get_width() const;
/**
 * Return height of the matrix
 * @return height of the matrix
 */
    size_t get_height() const;
/**
 * Check if given position is in the matrix
 * @param row to check
 * @param column to check
 * @return true if given position is in the matrix
 */
    bool is_not_inside_matrix(size_t row, size_t column) const;
/**
 * Copy the matrix with its content
 * @return Copy of the current matrix
 */
    void clear();
/**
 * Assigment operator which copies the matrix
 * @param original
 * @return
 */
    Matrix<T> & operator = (const Matrix<T> & original);
private:
/**
 * Get value from the matrix
 * @param row of the value to get
 * @param column of the value to get
 * @return value at the given place
 */
    T at(size_t row, size_t column) const;
    size_t rows;
    size_t columns;
    vector<vector<T>> values;
};


#endif //CPP_SEM_MATRIX_H
