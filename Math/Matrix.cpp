#include "Matrix.h"
#include "Tuple.h"
#include <stdexcept>
#include <iostream>
#include <ostream>

float Matrix::get(size_t x, size_t y) const{
    return matrix[x + y*size];
}

void Matrix::set(size_t x, size_t y, float value) {
    matrix[x + y * size] = value; 
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







