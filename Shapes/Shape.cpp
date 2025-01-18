// #include "Material.h"
#include "Shape.h"
#include "Matrix.h"
#include "Color.h"
#include "Ray.h"

Shape::Shape():transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)), material{Material()}{};
Shape::Shape(Material mat):transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)), material{mat}{};

Matrix Shape::getTransform(){
  return transform;
}
void Shape::setTransform(Matrix  transform){
  Matrix t = (transform) * (this->transform);
  this->transform = t;
  this->inverseTransform = t.inverse();
}
void Shape::setTransforms(std::vector<Matrix> transforms){
  Matrix transformation = Matrix::identityMatrix(4);

  size_t size = transforms.size();
  for(size_t t = 0; t < size; ++t){
    transformation = transforms[t] * transformation;
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

Color Shape::patternAtShape(Tuple worldPoint){
  Tuple objectPoint = tupleMultiply(getInverseTransform(), worldPoint);
  Tuple patternPoint = tupleMultiply(getMaterial().pattern->getInverseTransform(), objectPoint);
  return getMaterial().pattern->patternAt(patternPoint);
}

std::shared_ptr<Intersections> Shape::intersect(Ray ray){
  return localIntersect(ray.transform(getInverseTransform()));
}
