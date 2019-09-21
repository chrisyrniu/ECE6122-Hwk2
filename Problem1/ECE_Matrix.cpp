/*
Author: <Yaru Niu> 
Class: ECE6122 
Last Date Modified: <2019-09-20>
Description: Solution to Problem 1 of Homework 2: the implementation file
*/

#include "ECE_Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;
// Constructor 
// Parameters: size: dimension * dimension, value of the element
ECE_Matrix::ECE_Matrix (int dimension, double value){
    row = dimension;
    column = dimension;
	matrix = new double*[dimension];
	for (int i = 0; i < dimension; ++i){
		matrix[i] = new double[dimension];
	}
	for (int j = 0; j < dimension; ++j){
	    for (int k = 0; k < dimension; ++k){
	        matrix[j][k] = value;
        }
    }
}
// Constructor
// Paramenters: size: dimension1 * dimension2, value of the element
ECE_Matrix::ECE_Matrix (int dimension1, int dimension2, double value){
    row = dimension1;
    column = dimension2;
    matrix = new double*[dimension1];
    for (int i = 0; i < dimension1; ++i){
        matrix[i] = new double[dimension2];
    }
    for (int j = 0; j < dimension1; ++j){
        for (int k = 0; k < dimension2; ++k){
            matrix[j][k] = value;
        }
    }
}
// Constructor using a file as an inpur
ECE_Matrix::ECE_Matrix(const char* filename){
    fstream input;
    double number;
    int flag1 = 0;
    int flag2 = 0;
    int rows;
    int columns;
    // Store the data into a dynamic 2D array
    input.open(filename, ios::in);
    if (!input){
        cout << "Unable to open file";
    }
    while(input >> number){
        if (flag1 == 0){
            rows = number;
            flag1 = flag1 + 1;
        }
        else if (flag1 == 1){
            columns = number;
            flag1 = flag1 + 1;
            matrix = new double*[rows];
            for (int i = 0; i < rows; ++i){
                matrix[i] = new double[columns];
            }
        }
        else{
            matrix[flag2/columns][flag2%columns] = number;
            flag2 = flag2 + 1;
        }
        row = rows;
        column = columns;
    }
    input.close();
}
// Copy construcor
ECE_Matrix::ECE_Matrix(const ECE_Matrix& ece_matrix):
row(ece_matrix.row),
column(ece_matrix.column)
{
    // Deep copy
    matrix = new double*[row];
    for (int i = 0; i < row; ++i){
        matrix[i] = new double[column];
    }
    for (int j = 0; j < row; ++j){
        for (int k = 0; k < column; ++k){
            matrix[j][k] = ece_matrix.matrix[j][k];
        }
    }
}
// Assignment operator
ECE_Matrix& ECE_Matrix::operator=(const ECE_Matrix& ece_matrix){
    if (this == &ece_matrix){
        return *this;
    }
    row = ece_matrix.row;
    column = ece_matrix.column;
    delete [] matrix;
    matrix = new double*[row];
    for (int i = 0; i < row; ++i){
        matrix[i] = new double[column];
    }
    for (int j = 0; j < row; ++j){
        for (int k = 0; k < column; ++k){
            matrix[j][k] = ece_matrix.matrix[j][k];
        }
    }
    return *this;
}
// Addition assignment operator
ECE_Matrix& ECE_Matrix::operator+=(const ECE_Matrix& ece_matrix){
    const ECE_Matrix flag = *this + ece_matrix;
    row = flag.row;
    column = flag.column;
    matrix = new double*[row];
    for (int i = 0; i < row; ++i){
        matrix[i] = new double[column];
    }
    for (int j = 0; j < row; ++j){
        for (int k = 0; k < column; ++k){
            matrix[j][k] = flag.matrix[j][k];
        }
    }
    return *this;
}
// Minus assignment operator
ECE_Matrix& ECE_Matrix::operator-=(const ECE_Matrix& ece_matrix){
    const ECE_Matrix flag = *this - ece_matrix;
    row = flag.row;
    column = flag.column;
    matrix = new double*[row];
    for (int i = 0; i < row; ++i){
        matrix[i] = new double[column];
    }
    for (int j = 0; j < row; ++j){
        for (int k = 0; k < column; ++k){
            matrix[j][k] = flag.matrix[j][k];
        }
    }
    return *this;
}
// Addition operator (matrix + number)
ECE_Matrix ECE_Matrix::operator+(const double& number) const{
    ECE_Matrix ece_matrix(*this);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            ece_matrix.matrix[i][j] += number;
        }
    }
    return ece_matrix;
}
// Minus operator (matrix - number)
ECE_Matrix ECE_Matrix::operator-(const double& number) const{
    ECE_Matrix ece_matrix(*this);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            ece_matrix.matrix[i][j] -= number;
        }
    }
    return ece_matrix;
}
// Multiplication operator (matrix * number)
ECE_Matrix ECE_Matrix::operator*(const double& number) const{
    ECE_Matrix ece_matrix(*this);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            ece_matrix.matrix[i][j] *= number;
        }
    }
    return ece_matrix;
}
// Division operator (matrix / number)
ECE_Matrix ECE_Matrix::operator/(const double& number) const{
    // Divided by zero
    if (number == 0){
        ECE_Matrix ece_matrix(*this);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                ece_matrix.matrix[i][j] = 0;
            }
        }
        return ece_matrix;
    }
    ECE_Matrix ece_matrix(*this);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            ece_matrix.matrix[i][j] /= number;
        }
    }
    return ece_matrix;
}
// Addition operator (matrix + matrix)
ECE_Matrix ECE_Matrix::operator+(const ECE_Matrix& ece_matrix) const{
    int new_row, new_column;
    double **new_matrix;
    new_row = max(row, ece_matrix.row);
    new_column = max(column, ece_matrix.column);
    new_matrix = new double*[new_row];
    for (int i = 0; i < new_row; ++i){
        new_matrix[i] = new double[new_column];
    }
    for (int j = 0; j < new_row; ++j){
        for (int k = 0; k < new_column; ++k){
            // Four situations depending on the size of two marices
            if ((j <= min(row, ece_matrix.row) - 1) && (k <= min(column, ece_matrix.column) - 1)){
                new_matrix[j][k] = matrix[j][k] + ece_matrix.matrix[j][k];
            }
            else if ((j <= min(row, ece_matrix.row) - 1) && (k > min(column, ece_matrix.column) - 1)){
                if (column > ece_matrix.column){
                    new_matrix[j][k] = matrix[j][k];
                }
                else{
                    new_matrix[j][k] = ece_matrix.matrix[j][k];
                }
            }
            else if ((j > min(row, ece_matrix.row) - 1) && (k <= min(column, ece_matrix.column) - 1)){
                if (row > ece_matrix.row){
                    new_matrix[j][k] = matrix[j][k];
                }
                else{
                    new_matrix[j][k] = ece_matrix.matrix[j][k];
                }
            }
            else{
                if (row > ece_matrix.row && column > ece_matrix.column){
                    new_matrix[j][k] = matrix[j][k];
                }
                else if (row < ece_matrix.row && column < ece_matrix.column){
                    new_matrix[j][k] = ece_matrix.matrix[j][k];
                }
                else{
                    new_matrix[j][k] = 0;
                }
            }
        }
    }
    ECE_Matrix new_ece_matrix(*this);
    new_ece_matrix.row = new_row;
    new_ece_matrix.column = new_column;
    new_ece_matrix.matrix = new_matrix;
    return new_ece_matrix;
}
// Minus operator (matrix - matrix)
ECE_Matrix ECE_Matrix::operator-(const ECE_Matrix& ece_matrix) const{
    int new_row, new_column;
    double **new_matrix;
    new_row = max(row, ece_matrix.row);
    new_column = max(column, ece_matrix.column);
    new_matrix = new double*[new_row];
    for (int i = 0; i < new_row; ++i){
        new_matrix[i] = new double[new_column];
    }
    for (int j = 0; j < new_row; ++j){
        for (int k = 0; k < new_column; ++k){
            // Four situations depending on the size of two marices
            if ((j <= min(row, ece_matrix.row) - 1) && (k <= min(column, ece_matrix.column) - 1)){
                new_matrix[j][k] = matrix[j][k] - ece_matrix.matrix[j][k];
            }
            else if ((j <= min(row, ece_matrix.row) - 1) && (k > min(column, ece_matrix.column) - 1)){
                if (column > ece_matrix.column){
                    new_matrix[j][k] = matrix[j][k];
                }
                else{
                    new_matrix[j][k] = -ece_matrix.matrix[j][k];
                }
            }
            else if ((j > min(row, ece_matrix.row) - 1) && (k <= min(column, ece_matrix.column) - 1)){
                if (row > ece_matrix.row){
                    new_matrix[j][k] = matrix[j][k];
                }
                else{
                    new_matrix[j][k] = -ece_matrix.matrix[j][k];
                }
            }
            else{
                if (row > ece_matrix.row && column > ece_matrix.column){
                    new_matrix[j][k] = matrix[j][k];
                }
                else if (row < ece_matrix.row && column < ece_matrix.column){
                    new_matrix[j][k] = -ece_matrix.matrix[j][k];
                }
                else{
                    new_matrix[j][k] = 0;
                }
            }
        }
    }
    ECE_Matrix new_ece_matrix(*this);
    new_ece_matrix.row = new_row;
    new_ece_matrix.column = new_column;
    new_ece_matrix.matrix = new_matrix;
    return new_ece_matrix;
}
// Get matrix's transpose 
ECE_Matrix ECE_Matrix::transpose() const{
    ECE_Matrix new_ece_matrix(column, row, 0);
    for (int i = 0; i < column; ++i){
        for (int j = 0; j < row; ++j){
            new_ece_matrix.matrix[i][j] = matrix[j][i];
        }
    }
    return new_ece_matrix;
}
// Friend function: addition operator (number + matrix)
ECE_Matrix operator+(double number, const ECE_Matrix& ece_matrix) {
    ECE_Matrix new_ece_matrix(ece_matrix);
    for (int i = 0; i < new_ece_matrix.row; ++i) {
        for (int j = 0; j < new_ece_matrix.column; ++j) {
            new_ece_matrix.matrix[i][j] += number;
        }
    }
    return new_ece_matrix;
}
// Friend function: minus operator (number - matrix)
ECE_Matrix operator-(double number, const ECE_Matrix& ece_matrix) {
    ECE_Matrix new_ece_matrix(ece_matrix);
    for (int i = 0; i < new_ece_matrix.row; ++i) {
        for (int j = 0; j < new_ece_matrix.column; ++j) {
            new_ece_matrix.matrix[i][j] = number -  new_ece_matrix.matrix[i][j];
        }
    }
    return new_ece_matrix;
}
// Friend function: multiplicatiom operator (number * matrix)
ECE_Matrix operator*(double number, const ECE_Matrix& ece_matrix) {
    ECE_Matrix new_ece_matrix(ece_matrix);
    for (int i = 0; i < new_ece_matrix.row; ++i) {
        for (int j = 0; j < new_ece_matrix.column; ++j) {
            new_ece_matrix.matrix[i][j] *= number;
        }
    }
    return new_ece_matrix;
}
// Friend function: division operator (number / matrix)
ECE_Matrix operator/(double number, const ECE_Matrix& ece_matrix) {
    ECE_Matrix new_ece_matrix(ece_matrix);
    for (int i = 0; i < new_ece_matrix.row; ++i) {
        for (int j = 0; j < new_ece_matrix.column; ++j) {
            // If the number divided by zero, the element keeps to be zero
            if (new_ece_matrix.matrix[i][j] != 0){
                new_ece_matrix.matrix[i][j] = number / new_ece_matrix.matrix[i][j];
            }
        }
    }
    return new_ece_matrix;
}
// Stream insertion operator
ostream& operator<< (ostream& os, const ECE_Matrix& ece_matrix){
    for (int i = 0; i < ece_matrix.row; ++i){
        for (int j = 0; j < ece_matrix.column; ++j){
            os.precision(3);
            os << scientific << ece_matrix.matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

