/*
Title: Matrix Multiplication Using OOP
Problem Statement: Implement multiplication of two matrices using a Matrix class.*/



#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class matrix
{
    int rows, cols;
    int **mat;

public:

    // Constructor
    matrix(int r, int c) : rows(r), cols(c)
    {
        if (r <= 0 || c <= 0)
            throw invalid_argument("Rows and columns must be positive.");

        mat = new int*[rows];

        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols];
    }

    // Destructor
    ~matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] mat[i];

        delete[] mat;
    }

    // Copy constructor - deep copy
    matrix(const matrix& from)
    {
        cout << "(Deep) copy constructor is called" << endl;

        rows = from.rows;
        cols = from.cols;

        mat = new int*[rows];

        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols];

        // Copy matrix values
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mat[i][j] = from.mat[i][j];
            }
        }
    }

    // Copy assignment operator - deep copy (Rule of Three).
    // Without this, "m1 = m2" would copy the pointer and cause a double delete.
    matrix& operator=(const matrix& from)
    {
        if (this == &from)  // self-assignment guard
            return *this;

        // Free old memory
        for (int i = 0; i < rows; i++)
            delete[] mat[i];
        delete[] mat;

        // Allocate and copy new memory
        rows = from.rows;
        cols = from.cols;
        mat = new int*[rows];

        for (int i = 0; i < rows; i++)
        {
            mat[i] = new int[cols];
            for (int j = 0; j < cols; j++)
                mat[i][j] = from.mat[i][j];
        }

        return *this;
    }

    // Initialize matrix
    void initialize()
    {
        cout << "Enter values of matrix row wise, separated by space and each row on new line:" << endl;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cin >> mat[i][j];
            }
        }
    }

    // Print matrix
    void print() const
    {
        cout << "Matrix:" << endl;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];

            cout << endl;
        }
    }

    // Matrix multiplication
    // m2 is taken by const reference so it is not copied needlessly
    matrix multiply(const matrix& m2) const
    {
        if (cols != m2.rows)
        {
            throw invalid_argument("Matrix multiplication is not possible.");
        }

        matrix m3(rows, m2.cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < m2.cols; j++)
            {
                m3.mat[i][j] = 0;

                // Multiply row of first matrix with column of second matrix
                for (int k = 0; k < cols; k++)
                {
                    m3.mat[i][j] += mat[i][k] * m2.mat[k][j];
                }
            }
        }

        return m3;
    }
};

int main()
{
    int r1, c1, r2, c2;

    cout << "Enter the # of rows and cols in 1st matrix: ";
    cin >> r1 >> c1;

    cout << "Enter the # of rows and cols in 2nd matrix: ";
    cin >> r2 >> c2;

    try
    {
        matrix m1(r1, c1), m2(r2, c2);

        m1.initialize();
        m1.print();

        m2.initialize();
        m2.print();

        matrix m3 = m1.multiply(m2);

        cout << "Resultant matrix:" << endl;
        m3.print();
    }
    catch (invalid_argument& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}