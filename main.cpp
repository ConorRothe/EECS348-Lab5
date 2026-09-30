/*
Name: Conor Rothe
Course: EECS 348
Lab 5 - C++ Programming
Description: Performs various matrix operations including addition,
multiplication, diagonal sums, row/column swaps, and updating elements.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Displays a matrix with aligned columns
void printMatrix(const vector<vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
}

// Reads two matrices from a file
bool readMatrices(const string& filename,
                  vector<vector<int>>& matrix1,
                  vector<vector<int>>& matrix2)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Could not open file." << endl;
        return false;
    }

    int N;
    file >> N;

    if (N <= 0)
    {
        cout << "Error: Invalid matrix size." << endl;
        return false;
    }

    matrix1.resize(N, vector<int>(N));
    matrix2.resize(N, vector<int>(N));

    // Read first matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!(file >> matrix1[i][j]))
            {
                cout << "Error reading first matrix." << endl;
                return false;
            }
        }
    }

    // Read second matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!(file >> matrix2[i][j]))
            {
                cout << "Error reading second matrix." << endl;
                return false;
            }
        }
    }

    file.close();
    return true;
}

// Adds two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& matrix1,
                                const vector<vector<int>>& matrix2)
{
    int N = matrix1.size();

    vector<vector<int>> result(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return result;
}

// Multiplies two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1,
                                     const vector<vector<int>>& matrix2)
{
    int N = matrix1.size();

    vector<vector<int>> result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Finds the main and secondary diagonal sums
void diagonalSums(const vector<vector<int>>& matrix)
{
    int N = matrix.size();

    int mainDiagonal = 0;
    int secondaryDiagonal = 0;

    for (int i = 0; i < N; i++)
    {
        mainDiagonal += matrix[i][i];
        secondaryDiagonal += matrix[i][N - 1 - i];
    }

    cout << "Main diagonal sum: " << mainDiagonal << endl;
    cout << "Secondary diagonal sum: " << secondaryDiagonal << endl;
}

// Swaps two rows
void swapRows(vector<vector<int>>& matrix, int row1, int row2)
{
    int N = matrix.size();

    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N)
    {
        cout << "Invalid row indices." << endl;
        return;
    }

    swap(matrix[row1], matrix[row2]);

    cout << "Matrix after swapping rows " << row1
         << " and " << row2 << ":" << endl;

    printMatrix(matrix);
}

// Swaps two columns
void swapColumns(vector<vector<int>>& matrix, int col1, int col2)
{
    int N = matrix.size();

    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N)
    {
        cout << "Invalid column indices." << endl;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        swap(matrix[i][col1], matrix[i][col2]);
    }

    cout << "Matrix after swapping columns " << col1
         << " and " << col2 << ":" << endl;

    printMatrix(matrix);
}

// Changes one element in a matrix
void updateElement(vector<vector<int>>& matrix,
                   int row,
                   int col,
                   int newValue)
{
    int N = matrix.size();

    if (row < 0 || row >= N || col < 0 || col >= N)
    {
        cout << "Invalid row or column index." << endl;
        return;
    }

    matrix[row][col] = newValue;

    cout << "Matrix after updating element at ("
         << row << ", " << col << "):" << endl;

    printMatrix(matrix);
}

int main()
{
    string filename;

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;

    cout << "Enter input file name: ";
    cin >> filename;

    // Requirement 1: Read matrices from file
    if (!readMatrices(filename, matrix1, matrix2))
    {
        return 1;
    }

    cout << endl;

    cout << "Matrix 1:" << endl;
    printMatrix(matrix1);

    cout << endl;

    cout << "Matrix 2:" << endl;
    printMatrix(matrix2);

    // Requirement 2: Add matrices
    cout << endl;
    cout << "Matrix Addition:" << endl;

    vector<vector<int>> sum = addMatrices(matrix1, matrix2);
    printMatrix(sum);

    // Requirement 3: Multiply matrices
    cout << endl;
    cout << "Matrix Multiplication:" << endl;

    vector<vector<int>> product = multiplyMatrices(matrix1, matrix2);
    printMatrix(product);

    // Requirement 4: Diagonal sums
    cout << endl;
    cout << "Diagonal Sums of Matrix 1:" << endl;

    diagonalSums(matrix1);

    // Requirement 5: Swap rows
    int row1;
    int row2;

    cout << endl;
    cout << "Enter two row indices to swap: ";
    cin >> row1 >> row2;

    swapRows(matrix1, row1, row2);

    // Requirement 6: Swap columns
    int col1;
    int col2;

    cout << endl;
    cout << "Enter two column indices to swap: ";
    cin >> col1 >> col2;

    swapColumns(matrix1, col1, col2);

    // Requirement 7: Update matrix element
    int row;
    int col;
    int newValue;

    cout << endl;
    cout << "Enter row index, column index, and new value: ";
    cin >> row >> col >> newValue;

    updateElement(matrix1, row, col, newValue);

    return 0;
}