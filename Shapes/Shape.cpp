#include "Shape.h"
#include "Matrix.h"
#include "Color.h"

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

void Shape::setColor(Color color){
  this->color = color;
}
void Shape::setColor(float r, float g, float b){
  this->color = Color{r,g,b,};
}
Color Shape::getColor() const{
  return color;
}
