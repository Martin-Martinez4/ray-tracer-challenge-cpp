#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_

#include "Material.h"
#include "Matrix.h"
#include "Color.h"
#include <iostream>
#include <memory>
#include "Intersection.h"

struct Ray;
struct Material;

class Shape {
public:
  Shape();
  Shape(Material mat);

  Matrix getTransform();
  void setTransform(Matrix transform);
  void setTransforms(std::vector<Matrix> transforms);

  Matrix getInverseTransform();
  
  void setColor(Color color);
  void setColor(float r, float g, float b);
  Color getColor() const;

  Material getMaterial();
  void setMaterial(Material m);

  Color patternAtShape(Tuple worldPoint);

  std::shared_ptr<Intersections> intersect(Ray ray);
  virtual std::shared_ptr<Intersections> localIntersect(Ray ray) = 0;
  virtual Tuple normalAt(Tuple const & worldPoint, Intersection const* intersection) = 0;

private:
  Matrix transform;
  Matrix inverseTransform;
  Ray* savedRay;
  Material material;
};

#endif
