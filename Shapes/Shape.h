#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_

#include "Matrix.h"

struct Ray;

class Shape {
public:
  Shape():transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)){};

  Matrix getTransforms();
  void setTransform(Matrix const& transform);

  Matrix getInverseTransform();

private:
  Matrix transform;
  Matrix inverseTransform;
  Ray* savedRay;
};

#endif