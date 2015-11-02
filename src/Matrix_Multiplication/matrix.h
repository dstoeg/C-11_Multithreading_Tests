#ifndef MATRIX_H
#define MATRIX_H

#include <iomanip>

template<class T>
class Matrix
{
public:
    Matrix(std::size_t dimension, T initVal = -1);
    Matrix(std::size_t dimension, T * initMatrix);
    ~Matrix();
    Matrix<T> * add(Matrix<T> * m);
    std::size_t getDimension() const;
    void setValue(T val, std::size_t i, std::size_t j);
    T getValue(std::size_t i, std::size_t j);
    void print();
    Matrix<T>& operator * (const Matrix<T>& matrix1);

private:
    T ** mMatrix;
    std::size_t mDimension;
};


#endif // MATRIX_H
