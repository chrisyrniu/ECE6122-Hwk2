/*
Author: <Yaru Niu> 
Class: ECE6122 
Last Date Modified: <2019-09-20>
Description: Solution to Problem 2 of Homework 2
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Main
int main(){
    fstream input;
    int number;
    int flag1 = 0;
    int flag2 = 0;
    int rows;
    int columns;
    int **matrix;
    string filename;
    cout << "Please input the file name: ";
    // Get the filename
    getline(cin, filename);
    // Read the file, and store the data into a dynamic 2D array
	const char* filepath = filename.c_str();
    input.open(filepath, ios::in);
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
            matrix = new int*[rows];
            for (int i = 0; i < rows; ++i){
                matrix[i] = new int[columns];
            }
        }
        else{
            matrix[flag2/columns][flag2%columns] = number;
            flag2 = flag2 + 1;
        }

    }
    input.close();	
    // Find the largest product
    int max_value = -2147483648;
    for (int i = 0; i < rows; ++i){
    	for (int j = 0; j < columns; ++j){
            // Go through each number in the matrix
    		int down = -2147483648;
    		int right = -2147483648;
    		int diag1 = -2147483648;
    		int diag2 = -2147483648;
    		if (i + 3 < rows){
                // The product in the downside dirction
    			down = matrix[i][j] * matrix[i+1][j] * matrix[i+2][j] *matrix[i+3][j];
    			if (down > max_value){
    				max_value = down;
    			}
    		}
    		if (j + 3 < columns){
                // The product in the rightside direction
    			right = matrix[i][j] * matrix[i][j+1] * matrix[i][j+2] * matrix[i][j+3];
    			if (right > max_value){
    				max_value = right;
    			}
    		}
    		if ((i + 3 < rows) && (j + 3 < columns)){
                // The product in one of the diagonals
    			diag1 = matrix[i][j] * matrix[i+1][j+1] * matrix[i+2][j+2] * matrix[i+3][j+3];
    			if (diag1 > max_value){
    				max_value = diag1;
    			}
    		}
    		if ((i + 3 < rows) && (j - 3 >= 0)){
                // The product in the other diagonal
    			diag2 = matrix[i][j] * matrix[i+1][j-1] * matrix[i+2][j-2] * matrix[i+3][j-3];
    			if (diag2 > max_value){
    				max_value = diag2;
    			}
    		}
    	}
    }
    // Output the largest product in a txt file
    ofstream output;
    output.open("output2.txt");
    output << max_value;
    cout << max_value << endl;
}
    