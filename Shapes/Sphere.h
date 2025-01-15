#ifndef SHAPES_SPHERE_H_
#define SHAPES_SPHERE_H_

#include "Shape.h"
#include "Tuple.h"
#include <memory>

struct Intersections;

class Sphere: public Shape{
public:
  Sphere(): Shape(){};
  Sphere(Material mat): Shape(mat){};
  
  std::shared_ptr<Intersections> localIntersect(Ray ray) override;

  Tuple normalAt(Tuple worldPoint) override;
  
private:

};


#endif // !SHAPES_SPHERE_H_
