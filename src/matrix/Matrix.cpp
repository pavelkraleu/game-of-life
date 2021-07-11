//
// Created by Pavel Kral on 04/05/2021.
//

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Matrix.h"

using namespace std;

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) :rows(rows), columns(columns), values(rows, vector<T>(columns)) {}

template <typename T>
Matrix<T>::~Matrix() = default;

template <typename T>
T Matrix<T>::at(size_t row, size_t column) const {
    return values[row][column];
}

template <typename T>
void Matrix<T>::clear() {
    values = vector<vector<T>>(rows, vector<T>(columns));
}

template <typename T>
void Matrix<T>::set(T value, size_t row, size_t column) {
#ifdef DEBUG
    check_input(row, column);
#endif
    values[row][column] = value;
}

template <typename T>
T Matrix<T>::get(size_t row, size_t column) const {
#ifdef DEBUG
    check_input(row, column);
#endif
    return at(row, column);
}

#ifdef DEBUG
/**
 * Helper function to check if we are accessing valid location in the matrix
 * @tparam T
 * @param row we are trying to access
 * @param column we are trying to access
 */
template <typename T>
void Matrix<T>::check_input(size_t row, size_t column) const {
    if(row >= rows || row < 0){
        throw out_of_range("Supplied row is out of range");
    }
    if(column >= columns || column < 0){
        throw out_of_range("Supplied column is out of range");
    }
}

template <typename T>
void Matrix<T>::print() const {
    int out_width = 2;

    for (size_t c=0; c < columns; c++){
        cout << string(out_width+1, '-');
    }
    cout << endl;

    for (size_t r=0; r < rows; r++){
        for (size_t c=0; c < columns; c++){
            cout << (c > 0 ? " ": "") << setw(out_width);
            cout << get(r, c);
        }
        cout << endl;
    }

    for (size_t c=0; c < columns; c++){
        cout << string(out_width+1, '-');
    }
    cout << endl;
}

#endif

template <typename T>
size_t Matrix<T>::get_width() const {
    return columns;
}

template <typename T>
size_t Matrix<T>::get_height() const {
    return rows;
}

template <typename T>
Matrix<T> *Matrix<T>::clone() {
    auto * copy = new Matrix(rows, columns);
    for (size_t r=0; r < rows; r++) {
        for (size_t c = 0; c < columns; c++) {
            T value = get(r, c);
            copy->set(value, r, c);
        }
    }
    return copy;
}

template<typename T>
bool Matrix<T>::is_not_inside_matrix(size_t row, size_t column) const {
    bool is_not_inside_matrix_min = row < 0 || column < 0;
    bool is_not_inside_matrix_max = row+1 > get_height() || column+1 >get_width();

    return is_not_inside_matrix_min || is_not_inside_matrix_max;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &original) {
    if (this == &original){
        return *this;
    }

    rows = original.rows;
    columns = original.columns;

    this->clear();

    for (size_t r=0; r < rows; r++) {
        for (size_t c = 0; c < columns; c++) {
            T value = original.get(r, c);
            set(value, r, c);
        }
    }

    return *this;
}

template class Matrix<bool>;
template class Matrix<int>;
