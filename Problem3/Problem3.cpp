/*
Author: <Yaru Niu> 
Class: ECE6122 
Last Date Modified: <2019-09-20>
Description: Solution to Problem 3 of Homework 2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> recursion(int, int, int, int**);
// Main
int main(){
    fstream input;
    int number;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int rows;
    int **triangle;
       string filename;
       cout << "Please input the file name: ";
        // Get the filename
       getline(cin, filename);
    // Read the file, and store the data of the triangle into a dynamic 2D array
    const char* filepath = filename.c_str();
    input.open(filepath, ios::in);
    if (!input){
        cout << "Unable to open file";
    }
    while(input >> number){
        if (flag1 == 0){
            rows = number;
            triangle = new int*[rows];
            for (int i = 0; i < rows; ++i){
                triangle[i] = new int[i + 1];
            }
            flag1 = flag1 + 1;
        }
        else{
            triangle[flag2][flag3] = number;
            if (flag2 == flag3){
                flag3 = 0;
                flag2 = flag2 + 1;
            }
            else{
                flag3 = flag3 + 1;
            }
        }
    }
    input.close();
    vector<int> result = recursion(0, 0, rows, triangle);
    // Get the maximumu sum and the corresponding path recursively using recursion
    ofstream output;
    output.open("output3.txt");
    output << result.back();
    cout << result.back() << endl;
    for (int i = 0; i < result.size() - 1; ++i){
    	cout << result[i] << " ";
    }
}
// The fucction for recursively getting the maximum sum from each point, and also extracting the path
// Parameters: the (row - 1) of the starting point from the top, the (column - 1) of the starting point from the top, number of rows of the triangle, the 2D array representing the triangle
// Return: a vector including the path from the bottom to the top and the maximum sum
vector<int> recursion(int i, int j, int row, int** triangle){
    // The function will find the path from bottom to the top of the triangle
    if (i < row - 1){
        vector<int> result;
        vector<int> result1 = recursion(i+1, j, row, triangle);
        vector<int> result2 = recursion(i+1, j+1, row, triangle);
        // The sum is stored in the last position of the vector
        int max1 = result1.back();
        int max2 = result2.back();
        // Get the new point in the maximum sum path and update the sum
        if (max1 >= max2){
            result = result1;
            result.pop_back();
            result.push_back(triangle[i][j]);
            result.push_back(max1 + triangle[i][j]);
        }
        else{
            result = result2;
            result.pop_back();
            result.push_back(triangle[i][j]);
            result.push_back(max2 + triangle[i][j]);
        }
        return result;
    }
    else{
        // The vector at the bottom
        vector<int> result;
        result.push_back(triangle[i][j]);
        result.push_back(triangle[i][j]);
        return result;
    }

}