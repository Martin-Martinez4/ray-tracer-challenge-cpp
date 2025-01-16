
#include "Matrix.h"
#include "Tuple.h"
#include "Ray.h"
#include "Sphere.h"
#include <cmath>

Tuple Sphere::normalAt(Tuple const & worldPoint, Intersection const* intersection) {
  
  Tuple objectPoint = tupleMultiply(getInverseTransform(), worldPoint);
  Tuple objectNormal = objectPoint - point(0,0,0);
  Tuple worldNormal = tupleMultiply(getInverseTransform().transpose(), objectNormal);
  worldNormal.w = 0;
  // Tuple wp = worldPoint.subtractTuple(point(0,0,0));
  return normalize(worldNormal);
}

Tuple Sphere::normalAt(Tuple const& worldPoint){
  return normalAt(worldPoint, nullptr);
}

std::shared_ptr<Intersections> Sphere::localIntersect(Ray ray){
  
  Tuple sphereToRay = ray.origin - point(0, 0, 0);

  float a = ray.direction.dot(ray.direction);
  float b = 2 * ray.direction.dot(sphereToRay);
  float c = sphereToRay.dot(sphereToRay) - 1;

  float discriminant = (b * b) - (4 * a * c);
    
  auto intersections = std::shared_ptr<Intersections> (new Intersections());

  if(discriminant >= 0){
    float d1 = (-b - sqrtf(discriminant)) / (2 * a);
		float d2 = (-b + sqrtf(discriminant)) / (2 * a);

    if(floatsEqual(d1, d2)){
      (*intersections).add(Intersection{d1, this});
    }else{

      (*intersections).add(Intersection{d1, this});
      (*intersections).add(Intersection{d2, this});
    }
  }
  return intersections;
}




