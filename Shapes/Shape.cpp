// #include "Material.h"
#include "Shape.h"
#include "Matrix.h"
#include "Color.h"

Shape::Shape():transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)), material{Material()}{};
Shape::Shape(Material mat):transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)), material{mat}{};

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
  this->material.color = color;
}
void Shape::setColor(float r, float g, float b){
  this->material.color = Color{r,g,b,};
}
Color Shape::getColor() const{
  return this->material.color;
}

Material Shape::getMaterial(){
  return material;
}

void Shape::setMaterial(Material m){
  material = m;
}
