
#include "Ray.h"
#include "Matrix.h"
#include "Tuple.h"
#include <array>
#include <memory>
#include <cmath>
#include <iostream>


Tuple Ray::position(float f) const{
  return origin.addTuple(direction.multiplyScalar(f));
}

Ray Ray::translate(float x, float y, float z) const{
  Tuple newPoint =tupleMultiply(Matrix::identityMatrix(4), origin);
  return Ray{newPoint, direction}; 
}

Ray Ray::scale(float x, float y, float z) const{
  Tuple newOrigin = tupleMultiply(Matrix::identityMatrix(4), origin);
  Tuple newDirection = tupleMultiply(Matrix::identityMatrix(4), origin);
  return Ray{newOrigin, newDirection};
}

Ray Ray::transform(Matrix matrix) const{
  Tuple newOrigin = tupleMultiply(matrix, origin);
  Tuple newDirection = tupleMultiply(matrix, direction);
  return Ray{newOrigin, newDirection}; 
}

bool Ray::equal(Ray const& other) const{
  return (
    origin == other.origin &&
    direction == other.direction
  );
}

std::shared_ptr<Intersections> raySphereIntersect(Ray const& ray, Sphere* sphere){
  Ray r = ray.transform(sphere->getInverseTransform());
  
  Tuple sphereToRay = r.origin.subtractTuple(point(0, 0, 0));

  float a = r.direction.dot(r.direction);
  float b = 2 * r.direction.dot(sphereToRay);
  float c = sphereToRay.dot(sphereToRay) - 1;

  float discriminant = (b * b) - (4 * a * c);
    
  auto intersections = std::shared_ptr<Intersections> (new Intersections());

  if(discriminant >= 0){
    float d1 = (-b - sqrtf(discriminant)) / (2 * a);
		float d2 = (-b + sqrtf(discriminant)) / (2 * a);

    if(floatsEqual(d1, d2)){
      (*intersections).add(Intersection{d1, sphere});
    }else{

      (*intersections).add(Intersection{d1, sphere});
      (*intersections).add(Intersection{d2, sphere});
    }
  }
  return intersections;
}

std::ostream& operator<<(std::ostream &os, const Ray& r){
    return os << "origin: " << r.origin << " " << "direction: " << r.direction;
}


