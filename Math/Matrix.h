
#ifndef MATH_MATRIX_H_
#define MATH_MATRIX_H_

// More functional approach?

#include <cstddef>
#include <vector>
#include <ostream>
#include "Floats.h"
#include "Tuple.h"
#include <array>
#include <algorithm>


/*
  A long vector, 
*/
class Matrix {
public:
  Matrix():size{4}, matrix{std::vector<float>(size*size, 0)}{}
  Matrix(size_t size):size{size}, matrix{std::vector<float>(size*size, 0)}{}
  Matrix(std::array<float, 4> arr):size{2}, matrix(std::begin(arr), std::end(arr)){}
  Matrix(std::array<float, 9> arr):size{3}, matrix(std::begin(arr), std::end(arr)){}
  Matrix(std::array<float, 16> arr):size{4}, matrix(std::begin(arr), std::end(arr)){}
  
  size_t size;

  float get(size_t x, size_t y) const;
  void set(size_t x, size_t y, float value);
  bool equal(Matrix const& otherMatrix) const;
  // Matrix scalarMultiply(float scalar) const;

  Matrix transpose() const;

  Matrix subMatrix(size_t row, size_t column) const;
  float determinate() const;
  float minor(size_t row, size_t column) const;
  float cofactor(size_t row, size_t column) const;
  Matrix cofactorMatrix() const;
  Matrix inverse() const;

  bool isInvertible() const;

  static Matrix identityMatrix(size_t size);
  static Matrix translate(float x, float y,float z);
  static Matrix translateInverse(float x, float y,float z);
  static Matrix scale(float x, float y,float z);
  static Matrix scaleInverse(float x, float y,float z);
  static Matrix reflectX();
  static Matrix reflectY();
  static Matrix refelctZ();
  static Matrix rotationAlongX(float radians);
  static Matrix rotationAlongY(float radians);
  static Matrix rotationAlongZ(float radians);
  static Matrix shear(float xy, float xz, float yx, float yz, float zx, float zy);
  static Matrix viewTransform(Tuple from, Tuple to, Tuple up);

  Matrix& operator=(const Matrix & other){
    if(this != &other){
       size = other.size;
       matrix = other.matrix;
    }

    return *this;
  }

  bool operator==(Matrix const& otherMatrix) const{
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

  
  Matrix operator *(float f){
     Matrix copy = *this;

    std::for_each(copy.matrix.begin(), copy.matrix.end(), [f](float& x){
        x *= f;
    });

    return copy;
  }


   Matrix operator *(const Matrix  & otherMatrix) {
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


     Matrix operator *=(const Matrix& otherMatrix){
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

  friend std::ostream& operator<<(std::ostream &os, const Matrix& m);


private:
  std::vector<float> matrix;

};

Tuple tupleMultiply(Matrix const& matrix, Tuple const& tuple);

#endif



