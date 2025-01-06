#ifndef SHAPES_SPHERE_H_
#define SHAPES_SPHERE_H_

#include "Matrix.h"
class Sphere{
  Sphere():transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)){};
public:

  Matrix getTransforms();
  void setTransform(Matrix const& transform);

  Matrix getInverseTransform();

private:
  Matrix transform;
  Matrix inverseTransform;
};


#endif // !SHAPES_SPHERE_H_
