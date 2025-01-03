#include "Matrix.h"
#include "Tuple.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include<algorithm>

float Matrix::get(size_t x, size_t y) const{
    return matrix[y + x*size];
}

void Matrix::set(size_t x, size_t y, float value) {
    matrix[y + x * size] = value; 
}

Matrix Matrix::scalarMultiply(float scalar) const{

    Matrix copy = *this;

    std::for_each(copy.matrix.begin(), copy.matrix.end(), [scalar](float& x){
        x *= scalar;
    });

    return copy;
}

bool Matrix::equal(Matrix const& otherMatrix) const{
    if(otherMatrix.size != size) {
        return false;
    }

    for(size_t x = 0; x < size; ++x){
        for(size_t y = 0; y < size; ++y){
            if(!FloatsEqual(get(x, y), otherMatrix.get(x, y))){
                return false;
            }
        }   
    }

    return true;
}

Matrix Matrix::matrixMultiply(Matrix const& otherMatrix) const{
    // All Matrices are squared in this program
    if(size != otherMatrix.size){
        throw std::invalid_argument("matrices tried to multiply matrices of different sizes");
    }

    Matrix newMatrix = Matrix(size);

    for(size_t x = 0; x < size; ++x){
        for(size_t y = 0; y < size; ++y){
            float acc = 0.0f;
            for(size_t k = 0; k < size; ++k){
                acc += this->get(x, k) * otherMatrix.get(k, y);
            }

            newMatrix.set(x, y, acc);
        }
    }

    return newMatrix;
}

Matrix Matrix::transpose() const{
  Matrix temp = Matrix(size);

  for(size_t y = 0; y < size; ++y){
    for(size_t x = 0; x < size; ++x){
      temp.set(x, y, get(y,x));
    }
  }

  return temp;
}

 Matrix Matrix::subMatrix(size_t row, size_t column) const{

    if(size <= 2){
        throw std::invalid_argument("matrix too small to subMatrix");
    }

    Matrix tempMatrix = Matrix(size - 1);

    size_t newRow = 0;

    for(size_t y = 0; y < size; ++y){
        if(y == row){
            continue;
        }else{
            size_t newColumn = 0;

            for(size_t x = 0; x < size; ++x){
                if(x == column){
                    continue;
                }else{
                    tempMatrix.set(newRow, newColumn, get(y, x));
                    newColumn++;
                }
            }
        }

        newRow++;
    }

    return tempMatrix;
 }

float Matrix::determinate() const {
  if(size == 2){
    return get(0,0)*get(1,1) - get(0,1)*get(1,0);
  }else{
    float acc = 0;
    for(size_t y = 0; y < size; ++y){
      acc += cofactor(0, y) * get(0, y);
    }

    return acc;
  }
}

float Matrix::minor(size_t row, size_t column) const{
  Matrix temp = subMatrix(row, column);
  return temp.determinate();
}

float Matrix::cofactor(size_t row, size_t column) const {
  if((row+column)%2 == 0){
    return minor(row, column);
  }else{
    return -1 * minor(row, column);
  }
}

// Matrix Matrix::identityMatrix(size_t size){

// }

std::ostream& operator<<(std::ostream &os, const Matrix& m){

    // if current % size = 0 new line
    for(size_t x = 0; x < m.size; ++x){
        for(size_t y = 0; y < m.size; ++y){
            float val = m.get(x, y);
            os << m.get(x, y) << " ";
        }

        os << "\n";
    }

    return os;
}







