#include "matrix.h"
#include <iostream>
#include <iomanip>

#include <cstdlib>
#include <ctime>

using namespace std;

// ------------------------------------------------------------------
// Standard CTor:
// @param dimension: takes a dimension for the size of the matrix
// @param initVal : initial value for all entries in the matrix,
//                  if set to -1, random values will be used
// ------------------------------------------------------------------
template<class T>
Matrix<T>::Matrix(size_t dimension, T initVal)
{
    mDimension = dimension;

    mMatrix = new T*[mDimension];
    for(size_t i=0; i<mDimension; ++i)
        mMatrix[i] = new T[mDimension];

    if (initVal == -1) {
        for(size_t i=0; i<mDimension; ++i) {
            for (size_t j=0; j<mDimension; ++j) {

                mMatrix[i][j] = std::rand() % 100 + 0.123;
            }
        }
    }
    else {
        for(size_t i=0; i<mDimension; ++i) {
            for (size_t j=0; j<mDimension; ++j) {
                mMatrix[i][j] = initVal;
            }
        }
    }
}

// ----------------------------------------------------------------0--
// Second CTor:
// @param dimension: takes a dimension for the size of the matrix
// @param initVal : a 2D array can be passed to the CTor for intialization
// ------------------------------------------------------------------
template<class T>
Matrix<T>::Matrix(size_t dimension, T * initMatrix)
{
    mDimension = dimension;
    mMatrix = initMatrix;
}

// ------------------------------------------------------------------
// Standard Dtor:
// destroys the object and frees memory
// ------------------------------------------------------------------
template<class T>
Matrix<T>::~Matrix() {
    for (size_t i = 0; i < mDimension ; ++i){
        delete [] mMatrix[i];
    }
    delete mMatrix; mMatrix = NULL;
}

// ------------------------------------------------------------------
// Print:
// prints all matrix values to the console
// ------------------------------------------------------------------
template<class T>
void Matrix<T>::print() {
    cout << endl;
    for(size_t i=0; i<mDimension; ++i) {
        cout << " | ";
        for (size_t j=0; j<mDimension; ++j) {
            cout << setw(8) << mMatrix[i][j];
        }
        cout << " | " << endl;
    }
}

// ------------------------------------------------------------------
// add:
// @param m: Matrix that should be added to the current matrix
// returns a new matrix with the result of the addition
// ------------------------------------------------------------------
template<class T>
Matrix<T> * Matrix<T>::add(Matrix<T> * m)
{

    if (m->getDimension() != mDimension)
        return NULL;

    Matrix<T> * result = new Matrix<T>(mDimension, 0);

    for(size_t i=0; i<mDimension; ++i) {
        for (size_t j=0; j<mDimension; ++j) {
            result->setValue(mMatrix[i][j] + m->getValue(i,j), i, j);
        }
    }

    return result;
}


// ------------------------------------------------------------------
// getDimension
// returns the dimension of the matrix
// ------------------------------------------------------------------
template<class T>
size_t Matrix<T>::getDimension() const
{
    return mDimension;
}

// ------------------------------------------------------------------
// setValue
// sets a given value to the specified position in the matrix
// ------------------------------------------------------------------
template<class T>
void Matrix<T>::setValue(T val, size_t i, size_t j)
{
    if (i<mDimension && j<mDimension)
        mMatrix[i][j] = val;
}


// ------------------------------------------------------------------
// getValue
// returns the value at a given position in the matrix
// ------------------------------------------------------------------
template<class T>
T Matrix<T>::getValue(size_t i, size_t j)
{
    if (i<mDimension && j<mDimension)
        return mMatrix[i][j];
}


