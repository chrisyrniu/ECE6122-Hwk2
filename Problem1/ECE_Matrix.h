/*
Author: <Yaru Niu> 
Class: ECE6122 
Last Date Modified: <2019-09-20>
Description: Solution to Problem 1 of Homework 2: the header file
*/

#pragma once
#include <iostream>

using namespace std;
// Class ECE_Matrix: Impelement a series of operation of 2D arrays (matrix)
class ECE_Matrix
{
    double **matrix;
    int row;
    int column;
public:
    // Default constructor
	ECE_Matrix () {};
    // Constructor (dimension * dimension)
	ECE_Matrix (int, double);
    // Constructor (dimension1 * dimension2)
	ECE_Matrix (int, int, double);
    // Constructor (from the file)
	ECE_Matrix (const char*);
    // Copy Constructor 
	ECE_Matrix (const ECE_Matrix&);
    // Assignment
    ECE_Matrix& operator=(const ECE_Matrix&);
    // Addition assignment
    ECE_Matrix& operator+=(const ECE_Matrix&);
    // Minus assignment
    ECE_Matrix& operator-=(const ECE_Matrix&);
    // Matrix + number
    ECE_Matrix operator+(const double&) const;
    // Matrix - number
    ECE_Matrix operator-(const double&) const;
    // Matrix * number
    ECE_Matrix operator*(const double&) const;
    // Matrix / number
    ECE_Matrix operator/(const double&) const;
    // Matrix + matrix
    ECE_Matrix operator+(const ECE_Matrix&) const;
    // Matrix - matrix
    ECE_Matrix operator-(const ECE_Matrix&) const;
    // Matrix's transpose
    ECE_Matrix transpose() const;
    // Friend function: number + matrix
    friend ECE_Matrix operator+(double, const ECE_Matrix&);
    // Friend function: number - matrix
    friend ECE_Matrix operator-(double, const ECE_Matrix&);
    // Friend function: number * matrix
    friend ECE_Matrix operator*(double, const ECE_Matrix&);
    // Friend function: number / matrix
    friend ECE_Matrix operator/(double, const ECE_Matrix&);
    // Friend function: stream insertion
	friend ostream& operator<<(ostream&, const ECE_Matrix&);
};