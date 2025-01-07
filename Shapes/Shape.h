#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_

#include "Matrix.h"
#include "Color.h"

struct Ray;

class Shape {
public:
  Shape():transform{Matrix::identityMatrix(4)}, inverseTransform(Matrix::identityMatrix(4)),color{Color{0,0,0}}{};

  Matrix getTransforms();
  void setTransform(Matrix const& transform);
  void setTransforms(std::vector<Matrix> transforms);

  Matrix getInverseTransform();
  
  void setColor(Color color);
  void setColor(float r, float g, float b);
  Color getColor() const;

  virtual Tuple normalAt(Tuple worldPoint);


private:
  Matrix transform;
  Matrix inverseTransform;
  Ray* savedRay;
  Color color;
};

#endif
