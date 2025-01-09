#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_

#include "Material.h"
#include "Matrix.h"
#include "Color.h"
#include <iostream>

struct Ray;
struct Material;

class Shape {
public:
  Shape();

  Matrix getTransforms();
  void setTransform(Matrix const& transform);
  void setTransforms(std::vector<Matrix> transforms);

  Matrix getInverseTransform();
  
  void setColor(Color color);
  void setColor(float r, float g, float b);
  Color getColor() const;

  Material getMaterial();

  virtual Tuple normalAt(Tuple worldPoint) = 0;


private:
  Matrix transform;
  Matrix inverseTransform;
  Ray* savedRay;
  Material material;
};

#endif
