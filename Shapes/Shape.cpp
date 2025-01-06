#include "Shape.h"
#include "Matrix.h"

Matrix Shape::getTransforms(){
  return transform;
}
void Shape::setTransform(Matrix const& transform){
  this->transform = transform.matrixMultiply(this->transform);
  // this->inverseTransform = this->transform.inverse();
}

Matrix Shape::getInverseTransform(){
  return inverseTransform;
}