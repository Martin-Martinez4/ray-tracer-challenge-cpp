#include "Matrix.h"
#include "Tuple.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <algorithm>
#include <cmath>

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
            if(!floatsEqual(get(x, y), otherMatrix.get(x, y))){
                return false;
            }
        }   
    }

    return true;
}

Matrix Matrix::matrixMultiply(Matrix const& otherMatrix) const{
    // All Matrixes are squared in this program
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
                    ++newColumn;
                }
            }
        }

        ++newRow;
    }

    return tempMatrix;
 }

float Matrix::determinate() const {
  if(size == 2){
    return get(0,0)*get(1,1) - get(0,1)*get(1,0);
  }else{
    float acc = 0;
    for(size_t y = 0; y < size; ++y){
      acc += get(0, y)*cofactor(0, y);
    }

    return acc;
  }
}

float Matrix::minor(size_t row, size_t column) const{
  return subMatrix(row, column).determinate();
}

float Matrix::cofactor(size_t row, size_t column) const {
  if((row+column)%2 == 0){
    return minor(row, column);
  }else{
    return -1 * minor(row, column);
  }
}
Matrix Matrix::cofactorMatrix() const{
    Matrix cofactorMatrix = Matrix(size);

    for(size_t row = 0; row < size; ++row){
        for(size_t column = 0; column< size; ++column){
            cofactorMatrix.set(row, column, cofactor(row, column));
        }   
    }

    return cofactorMatrix;
}

// very expensive operation
Matrix Matrix::inverse() const{
    float determinate = this->determinate();

    if(determinate == 0){
        throw std::invalid_argument("function is not invertable");
    }else{
        float factor = 1/ determinate;
        
        return cofactorMatrix().transpose().scalarMultiply(factor);
    }

    float factor = 1/ determinate;

}

bool Matrix::isInvertible() const{
    return determinate() != 0;
}

Matrix Matrix::identityMatrix(size_t size){
    Matrix mat = Matrix(size);

    for(size_t i = 0; i < size; ++i){
        mat.set(i, i, 1);
    }

    return mat;
}

Matrix Matrix::translation(float x, float y,float z){
    return Matrix{{1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1}};
}
Matrix Matrix::translationInverse(float x, float y,float z){
    x*= -1.0f;
    y*= -1.0f;
    z*= -1.0f;
    return Matrix{{1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1}};

}
Matrix Matrix::scale(float x, float y,float z){
    return Matrix{{x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1}};
}
Matrix Matrix::scaleInverse(float x, float y,float z){
    
    return Matrix{{1/x,0,0,0, 0,1/y,0,0, 0,0,1/z,0, 0,0,0,1}};
}
Matrix Matrix::reflectX(){
    return Matrix{{-1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}};
}
Matrix Matrix::reflectY(){
    return Matrix{{1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,0,0,1}};
}
Matrix Matrix::refelctZ(){
     return Matrix{{1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,0,0,1}};
}
Matrix Matrix::rotationAlongX(float radians){
    return Matrix{{1,0,0,0, 0,cosf(radians),-sinf(radians),0, 0,sinf(radians),cosf(radians),0, 0,0,0,1}};
}
Matrix Matrix::rotationAlongY(float radians){
    return Matrix{{cosf(radians),0,sinf(radians),0, 0,1,0,0, -sinf(radians),0,cosf(radians),0, 0,0,0,1}};
}
Matrix Matrix::rotationAlongZ(float radians){
    return Matrix{{cos(radians),-sin(radians),0,0, sin(radians),cos(radians),0,0, 0,0,1,0, 0,0,0,1}};
}
Matrix Matrix::shear(float xy, float xz, float yx, float yz, float zx, float zy){
    return Matrix{{1,xy,xz,0, yx,1,yz,0, zx,zy,1,0, 0,0,0,1}};
}

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
};

Tuple tupleMultiply(Matrix const& matrix, Tuple const& tuple){

    
    if(matrix.size != 4){
        throw std::invalid_argument("tried to tuple matrix multiply with a matrix that is not of size 4");
    }

    return Tuple{
        matrix.get(0, 0)*tuple.x + matrix.get(0, 1)*tuple.y + matrix.get(0, 2)*tuple.z + matrix.get(0, 3)*tuple.w,
		matrix.get(1, 0)*tuple.x + matrix.get(1, 1)*tuple.y + matrix.get(1, 2)*tuple.z + matrix.get(1, 3)*tuple.w,
		matrix.get(2, 0)*tuple.x + matrix.get(2, 1)*tuple.y + matrix.get(2, 2)*tuple.z + matrix.get(2, 3)*tuple.w,
		matrix.get(3, 0)*tuple.x + matrix.get(3, 1)*tuple.y + matrix.get(3, 2)*tuple.z + matrix.get(3, 3)*tuple.w,
    };
}








