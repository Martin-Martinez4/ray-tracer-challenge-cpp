#ifndef SHAPES_PLANE_H_
#define SHAPES_PLANE_H_

#include "Shape.h"
#include "Tuple.h"
#include <memory>

struct Intersections;

class Plane: public Shape{
public:
  Plane(): Shape(){};
  Plane(Material mat): Shape(mat){};
  
  std::shared_ptr<Intersections> localIntersect(Ray ray);

  Tuple normalAt(Tuple worldPoint) override;
  std::shared_ptr<Intersections> intersect(Ray ray) override;
  
private:

};


#endif // !SHAPES_SPHERE_H_