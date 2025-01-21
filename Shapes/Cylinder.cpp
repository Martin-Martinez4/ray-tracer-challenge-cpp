
#include "Cylinder.h"
#include "Floats.h"
#include "Intersection.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuple.h"
#include <cmath>
#include <memory>

bool Cylinder::checkCap(Ray ray, float t){
  float x = ray.origin.x + t * ray.direction.x;
  float z = ray.origin.z + t * ray.direction.z;

  return (pow(x, 2) + pow(z, 2)) <= 1.0;
}

void Cylinder::intersectCaps(Ray ray, std::shared_ptr<Intersections> intersections){
  if(!closed || fabs(ray.direction.y) <= EPSILON){
    return;
  }

  float t = (minimum - ray.origin.y) / ray.direction.y;
  if(checkCap(ray, t)){
    intersections->add(Intersection{t, this});
  }

  t = (maximum - ray.origin.y) / ray.direction.y;
  if(checkCap(ray, t)){
    intersections->add(Intersection{t, this});
  }
}

std::shared_ptr<Intersections> Cylinder::localIntersect(Ray ray){

  float a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0);
  float b = 2 * ray.origin.x * ray.direction.x +
      2 * ray.origin.z * ray.direction.z;
  float c = pow(ray.origin.x, 2.0)
      + pow(ray.origin.z, 2.0) - 1.0;
  float discriminant = pow(b, 2.0) - 4.0 * a * c;
  if (discriminant < 0) {
    return std::shared_ptr<Intersections> (new Intersections());
  }
  float disc = sqrt(discriminant);
  float t0 = (-b - disc) / (2.0 * a);
  float t1 = (-b + disc) / (2.0 * a);
  if (t0 > t1) {
    std::swap(t0, t1);
  }

  std::shared_ptr<Intersections> intersections (new Intersections());

  float y0 = ray.origin.y + t0 * ray.direction.y;
  if (minimum < y0 && y0 < maximum) {
    intersections->add(Intersection{t0, this});
  }
  float y1 = ray.origin.y + t1 * ray.direction.y;
  if (minimum < y1 && y1 < maximum) {
    intersections->add(Intersection{t1, this});
  }

  intersectCaps(ray, intersections);
  return intersections;
}

Tuple Cylinder::normalAt(Tuple const& worldPoint, Intersection const* intersection){
  return normalAt(worldPoint);
}
Tuple Cylinder::normalAt(Tuple const& worldPoint){
  Tuple localPoint = tupleMultiply(getInverseTransform(), worldPoint);

  float dist = pow(localPoint.x, 2.0) + pow(localPoint.z, 2.0);

  if(dist < 1 && localPoint.y >= maximum - EPSILON){
    return vector(0, 1, 0);
  }else if(dist < 1 && localPoint.y <= minimum + EPSILON){
    return vector(0, -1, 0);
  }else{
    return vector(localPoint.x, 0, localPoint.z);
  }
}
