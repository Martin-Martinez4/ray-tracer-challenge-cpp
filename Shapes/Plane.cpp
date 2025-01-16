
#include "Floats.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"
#include <cmath>
#include "Plane.h"


std::shared_ptr<Intersections> Plane::localIntersect(Ray ray){
  if(std::fabs(ray.direction.y) < EPSILON){
    return std::shared_ptr<Intersections>{};
  }
  std::shared_ptr<Intersections>inters (new Intersections);
  inters->add(Intersection{(-ray.origin.y / ray.direction.y), this});
  return inters;
}

Tuple Plane::normalAt(Tuple const & worldPoint, Intersection const* intersection){
  return vector(0, 1, 0);
}
