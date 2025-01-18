
#include "Pattern.h"
#include "Color.h"
#include "Tuple.h"

Pattern::Pattern(Color color1, Color color2):color1{color1}, color2{color2}, transform{Matrix::identityMatrix(4)}, inverseTransform{Matrix::identityMatrix(4)}{};

Pattern::Pattern(Color color1):Pattern(color1, Color(0,0,0)){};
Pattern::Pattern():Pattern(Color(0,0,0), Color(1,1,1)){};

Color Pattern::getColor1(){
  return color1;
}

Color Pattern::getColor2(){
  return color2;
}

Matrix Pattern::getTransform(){
  return transform;
}
void Pattern::setTransform(Matrix  transform){
  Matrix t = (transform) * (this->transform);
  this->transform = t;
  this->inverseTransform = t.inverse();
}
void Pattern::setTransforms(std::vector<Matrix> transforms){
  Matrix transformation = Matrix::identityMatrix(4);

  size_t size = transforms.size();
  for(size_t t = 0; t < size; ++t){
    transformation = transforms[t] * transformation;
  }

  this->setTransform(transformation);
};

Matrix Pattern::getInverseTransform(){
  return inverseTransform;
}

Color Pattern::patternAt(Tuple point){
  return Color(point.x, point.y, point.z);
}





