
#ifndef SHAPES_CONE_H_
#define SHAPES_CONE_H_



#include "Shape.h"
#include "Tuple.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>

struct Intersections;
struct Ray;

class Cone: public Shape{
public:
  Cone(): Shape(){};
  Cone(Material mat): Shape(mat){};
  Cone(float minimum, float maximum, bool closed = false):Shape(),minimum{minimum},maximum{maximum},closed{closed}{};
  Cone(Material mat, float minimum, float maximum, bool closed = false):Shape(mat),minimum{minimum},maximum{maximum},closed{closed}{};

  bool checkCap(Ray ray, float t, float y);
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
