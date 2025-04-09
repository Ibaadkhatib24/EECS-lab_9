#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// templated Matrix class that supports int or double types
template <typename T>
class Matrix
{
private:
    vector<vector<T>> elements; // matrix data
    int size;                   // matrix dimension

public:
    Matrix(int n) : size(n), elements(n, vector<T>(n)) {}

    // load matrix data from a file stream
    void loadFromFile(ifstream &fileStream)
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (!(fileStream >> elements[row][col]))
                {
                    cerr << "error: not enough or invalid data in file" << endl;
                    return;
                }
            }
        }
    }

    // display the matrix
    void display() const
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                cout << setw(8) << elements[row][col];
            }
            cout << endl;
        }
        cout << endl;
    }

    // add two matrices with operator overloading
    Matrix operator+(const Matrix &other) const
    {
        Matrix result(size);
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                result.elements[row][col] = elements[row][col] + other.elements[row][col];
            }
        }
        return result;
    }

    // multiply two matrices with operator overloading
    Matrix operator*(const Matrix &other) const
    {
        Matrix result(size);
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                result.elements[row][col] = 0;
                for (int k = 0; k < size; k++)
                {
                    result.elements[row][col] += elements[row][k] * other.elements[k][col];
                }
            }
        }
        return result;
    }

    // calculate sum of main and secondary diagonals
    T calculateDiagonalSum() const
    {
        T diagonalSum = 0;
        for (int i = 0; i < size; i++)
        {
            diagonalSum += elements[i][i]; // main diagonal
            if (i != size - 1 - i)
            {
                diagonalSum += elements[i][size - 1 - i]; // secondary diagonal
            }
        }
        return diagonalSum;
    }

    // swap two rows if indices are valid
    void swapRows(int firstRow, int secondRow)
    {
        if (firstRow >= 0 && firstRow < size && secondRow >= 0 && secondRow < size)
        {
            swap(elements[firstRow], elements[secondRow]);
        }
        else
        {
            cout << "error: invalid row indices for swapping" << endl;
        }
    }

    // swap two columns if indices are valid
    void swapColumns(int col1, int col2)
    {
        if (col1 >= 0 && col1 < size && col2 >= 0 && col2 < size)
        {
            for (int row = 0; row < size; row++)
            {
                swap(elements[row][col1], elements[row][col2]);
            }
        }
        else
        {
            cout << "error: invalid column indices for swapping" << endl;
        }
    }

    // update a specific matrix element if indices are valid
    void updateElement(int row, int col, T newValue)
    {
        if (row >= 0 && row < size && col >= 0 && col < size)
        {
            elements[row][col] = newValue;
        }
        else
        {
            cout << "error: invalid indices for update" << endl;
        }
    }
};

int main()
{
    ifstream inputFile("matrix-data.txt");
    if (!inputFile)
    {
        cerr << "error: unable to open matrix-data.txt" << endl;
        return 1;
    }

    int matrixSize, typeFlag;
    inputFile >> matrixSize >> typeFlag;

    if (typeFlag == 0)
    {
        Matrix<int> matrix1(matrixSize), matrix2(matrixSize);

        // load and display the first matrix
        matrix1.loadFromFile(inputFile);
        cout << "matrix 1:" << endl;
        matrix1.display();

        // load and display the second matrix
        matrix2.loadFromFile(inputFile);
        cout << "matrix 2:" << endl;
        matrix2.display();

        // add matrices and display the result
        Matrix<int> sumMatrix = matrix1 + matrix2;
        cout << "sum of matrix 1 and matrix 2:" << endl;
        sumMatrix.display();

        // multiply matrices and display the result
        Matrix<int> productMatrix = matrix1 * matrix2;
        cout << "product of matrix 1 and matrix 2:" << endl;
        productMatrix.display();

        // display the sum of diagonals of the first matrix
        cout << "diagonal sum of matrix 1: " << matrix1.calculateDiagonalSum() << endl;

        // swap rows and display the modified matrix
        matrix1.swapRows(0, 2);
        cout << "matrix 1 after swapping row 0 with row 2:" << endl;
        matrix1.display();

        // swap columns and display the matrix
        matrix1.swapColumns(0, 2);
        cout << "matrix 1 after swapping column 0 with column 2:" << endl;
        matrix1.display();

        // update an element and display the matrix
        matrix1.updateElement(1, 1, 99);
        cout << "matrix 1 after updating element (1, 1) to 99:" << endl;
        matrix1.display();
    }
    else if (typeFlag == 1)
    {
        Matrix<double> matrix1(matrixSize), matrix2(matrixSize);

        // load and display the first matrix
        matrix1.loadFromFile(inputFile);
        cout << "matrix 1:" << endl;
        matrix1.display();

        // load and display the second matrix
        matrix2.loadFromFile(inputFile);
        cout << "matrix 2:" << endl;
        matrix2.display();

        // add matrices and display the result
        Matrix<double> sumMatrix = matrix1 + matrix2;
        cout << "sum of matrix 1 and matrix 2:" << endl;
        sumMatrix.display();

        // multiply matrices and display the result
        Matrix<double> productMatrix = matrix1 * matrix2;
        cout << "product of matrix 1 and matrix 2:" << endl;
        productMatrix.display();

        // display the sum of diagonals of the first matrix
        cout << "diagonal sum of matrix 1: " << matrix1.calculateDiagonalSum() << endl;

        // swap rows and display the modified matrix
        matrix1.swapRows(0, 2);
        cout << "matrix 1 after swapping row 0 with row 2:" << endl;
        matrix1.display();

        // swap columns and display the matrix
        matrix1.swapColumns(0, 2);
        cout << "matrix 1 after swapping column 0 with column 2:" << endl;
        matrix1.display();

        // update an element and display the matrix
        matrix1.updateElement(1, 1, 99.99);
        cout << "matrix 1 after updating element (1, 1) to 99.99:" << endl;
        matrix1.display();
    }
    else
    {
        cerr << "error: unknown matrix type flag (must be 0 or 1)" << endl;
        return 1;
    }

    return 0;
}
