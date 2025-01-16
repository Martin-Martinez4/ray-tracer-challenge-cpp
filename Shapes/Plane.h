
#ifndef SHAPES_PLANE_H_
#define SHAPES_PLANE_H_

#include "Intersection.h"
#include "Shape.h"
#include "Tuple.h"
#include <memory>

struct Intersections;

class Plane: public Shape{
public:
  Plane(): Shape(){};
  Plane(Material mat): Shape(mat){};
  
  std::shared_ptr<Intersections> localIntersect(Ray ray) override;

  Tuple normalAt(Tuple const & worldPoint, Intersection const* intersection) override;


  
private:

};


#endif // !SHAPES_SPHERE_H_
