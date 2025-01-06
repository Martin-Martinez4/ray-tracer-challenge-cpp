
#include "Sphere.h"

Matrix Sphere::getTransforms(){
  return transform;
}
void Sphere::setTransform(Matrix const& transform){
  this->transform = transform.matrixMultiply(this->transform);
  // this->inverseTransform = this->transform.inverse();
}

Matrix Sphere::getInverseTransform(){
  return inverseTransform;
}
