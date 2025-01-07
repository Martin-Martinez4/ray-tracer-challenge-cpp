#include "Shape.h"
#include "Matrix.h"
#include "Color.h"

Matrix Shape::getTransforms(){
  return transform;
}
void Shape::setTransform(Matrix const& transform){
  this->transform = transform.matrixMultiply(this->transform);
  this->inverseTransform = this->transform.inverse();
}
void Shape::setTransforms(std::vector<Matrix> transforms){
  Matrix transformation = identityMatrix4x4;

  size_t size = transforms.size();
  for(size_t t = 0; t < size; ++t){
    transformation = transforms[t].matrixMultiply(transformation);
  }

  this->setTransform(transformation);
};


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
