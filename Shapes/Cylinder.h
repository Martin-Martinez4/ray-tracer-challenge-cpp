#ifndef SHAPES_CYLINDER_H_
#define SHAPES_CYLINDER_H_



#include "Shape.h"
#include "Tuple.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>

struct Intersections;
struct Ray;

class Cylinder: public Shape{
public:
  Cylinder(): Shape(){};
  Cylinder(Material mat): Shape(mat){};
  Cylinder(float minimum, float maximum, bool closed = false):Shape(),minimum{minimum},maximum{maximum},closed{closed}{};
  Cylinder(Material mat, float minimum, float maximum, bool closed = false):Shape(mat),minimum{minimum},maximum{maximum},closed{closed}{};

  bool checkCap(Ray ray, float t);
  void intersectCaps(Ray ray, std::shared_ptr<Intersections> intersections);
  
  std::shared_ptr<Intersections> localIntersect(Ray ray) override;

  Tuple normalAt(Tuple const& worldPoint, Intersection const* intersection) override;
  Tuple normalAt(Tuple const& worldPoint);
  
private:
  float minimum = std::numeric_limits<float>::min();
  float maximum = std::numeric_limits<float>::max();
  bool closed = false;

};


#endif
