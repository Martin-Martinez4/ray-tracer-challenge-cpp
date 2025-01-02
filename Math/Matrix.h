
#ifndef MATH_MATRIX_H_
#define MATH_MATRIX_H_

// More functional approach?

#include <vector>
#include <ostream>
#include <algorithm>
#include <functional>
#include <array>

/*
  A long vector, 
*/
class Matrix {
public:
  Matrix(size_t size):size{size}, matrix{std::vector<float>(size*size, 0)}{}
  Matrix(std::array<float, 4> arr):size{2}, matrix(std::begin(arr), std::end(arr)){}
  Matrix(std::array<float, 9> arr):size{3}, matrix(std::begin(arr), std::end(arr)){}
  Matrix(std::array<float, 16> arr):size{4}, matrix(std::begin(arr), std::end(arr)){}
  
  size_t size;

  float get(size_t x, size_t y) const;
  void set(size_t x, size_t y, float value) ;
  bool equal(Matrix const& otherMatrix) const;
  Matrix scalarMultiply(float scalar) const;

  Matrix matrixMultiply(Matrix const& otherMatrix) const;

  static Matrix identityMatrix(size_t size);

  Matrix& operator=(const Matrix & other){
    if(this != &other){
       size = other.size;
       matrix = other.matrix;
    }

    return *this;
  }

  friend std::ostream& operator<<(std::ostream &os, const Matrix& m);


private:
  std::vector<float> matrix;

};



#endif



