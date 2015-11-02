#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "matrix.h"
#include "matrix.cpp"

using namespace std;
using namespace std::chrono;

// ------------------------------------------------------------------
// Kernel for multithreaded matrix multiplication
// @param index1 : horizontal index in matrix, iterate until index1 + dimension/2
// @param index2 : vertical index in matrix, iterate until index2 + dimension/2
// @param m1     : first matrix
// @param m2     : second matrix
// @param result : result matrix
// ------------------------------------------------------------------
template<class T>
void threadFunc(float index1, float index2, size_t nr_threads, Matrix<T> * m1, Matrix<T> * m2, Matrix<T> * result) {

    size_t division_factor = size_t(sqrt(nr_threads));
    index1 = index1*m1->getDimension();
    index2 = index2*m2->getDimension();

    for (size_t i=index1; i < index1 + m1->getDimension()/division_factor; ++i) {
        for (size_t j=index2; j < index2 + m1->getDimension()/division_factor; ++j) {
            int sum = 0;
            for (size_t k=0; k<m1->getDimension(); ++k) {
                sum +=+ m1->getValue(i,k) * m2->getValue(k,j);
            }
            result->setValue(sum, i, j);
        }
    }
}


// ------------------------------------------------------------------
// Single threaded matrix multiplication
// @param m1 : first matrix
// @param m2 : second matrix
// @param result: result matrix
// takes 2 matrices and multiplies them in one iteration
// ------------------------------------------------------------------
template<class T>
Matrix<T> * multiplyMatrixSingleThreaded(Matrix<T> * m1, Matrix<T> * m2) {

    Matrix<T> * result = new Matrix<T>(m1->getDimension(), 0.0);

    for (size_t i=0; i<m1->getDimension(); ++i) {
        for (size_t j=0; j<m1->getDimension(); ++j) {
            int sum = 0;
            for (size_t k=0; k<m1->getDimension(); ++k) {
                sum +=+ m1->getValue(i,k) * m2->getValue(k,j);
            }
            result->setValue(sum, i, j);
        }
    }

    return result;
}

// ------------------------------------------------------------------
// Multi threaded matrix multiplication
// @param m1 : first matrix
// @param m2 : second matrix
// @param result: result matrix
// takes 2 matrices and splits them into 4 threads, each thread receives
// a block for calculation.
// ------------------------------------------------------------------
template<class T>
Matrix<T> * multiplyMatrixMultiThreaded(Matrix<T> * m1, Matrix<T> * m2, size_t nr_threads) {

    Matrix<T> * result = new Matrix<T>(m1->getDimension(), 0.0);

    size_t division_factor = size_t(sqrt(nr_threads));

    vector<thread> threads;

    for (double i=0; i<1.0; i+=1.0/division_factor) {
        for (double j=0; j<1.0; j+=1.0/division_factor) {
            threads.push_back(std::thread(threadFunc<T>, i, j, nr_threads, m1, m2, result));
        }
    }

    for (size_t i=0; i<threads.size(); ++i) {
        threads[i].join();
    }

    return result;
}

// -----------------------------------------------------------------
// calls the multiply matrix function and measures the timing
// @param m1 : first matrix
// @param m2 : second matrix
// ------------------------------------------------------------------
template<class T>
void measureMultiplicationST(Matrix<T> * m1, Matrix<T> * m2) {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Matrix<double> * result = multiplyMatrixSingleThreaded(m1, m2);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "elapsed time in microseconds for single threaded: " << duration << endl;
    delete result; result = NULL;
}

// -----------------------------------------------------------------
// calls the multiply matrix function and measures the timing
// @param m1 : first matrix
// @param m2 : second matrix
// ------------------------------------------------------------------
template<class T>
void measureMultiplicationMT(Matrix<T> * m1, Matrix<T> * m2, size_t nr_threads) {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    Matrix<double> * result = multiplyMatrixMultiThreaded(m1, m2, nr_threads);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << "elapsed time in microseconds for multi threaded:  " << duration << endl;
    delete result; result = NULL;
}



int main()
{
    // initialize random seed for matrix initialization
    std::srand(std::time(0));

    // create 2 test matrices
    const int DIMENSION = 1024;
    const int VAL = -1;
    const size_t NR_THREADS_1 = 4;
    const size_t NR_THREADS_2 = 16;

    Matrix<double> * matrix1 = new Matrix<double>(DIMENSION, VAL);
    Matrix<double> * matrix2 = new Matrix<double>(DIMENSION, VAL);
    matrix1->print();
    matrix2->print();

    cout << "Matrix Multiplication test: " << endl;
    cout << "dimension : " << DIMENSION << endl;

    // run a ST and a MT test
    measureMultiplicationST(matrix1, matrix2);
    measureMultiplicationMT(matrix1, matrix2, NR_THREADS_1);
    measureMultiplicationMT(matrix1, matrix2, NR_THREADS_2);


    // free memory
    delete matrix1; matrix1 = NULL;
    delete matrix2; matrix2 = NULL;

    cout << "end..." << endl;

    return 0;
}

