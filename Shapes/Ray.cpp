
#include "Ray.h"
#include "Matrix.h"
#include "Tuple.h"
#include <array>


Tuple Ray::position(float f) const{
  return origin.addTuple(direction.multiplyScalar(f));
}

Ray Ray::translate(float x, float y, float z) const{
  Tuple newPoint =tupleMultiply(Matrix::identityMatrix(4), origin);
  return Ray{{newPoint.x, newPoint.y, newPoint.z}, {direction.x, direction.y, direction.z}}; 
}

Ray Ray::scale(float x, float y, float z) const{
  Tuple newOrigin = tupleMultiply(Matrix::identityMatrix(4), origin);
  Tuple newDirection = tupleMultiply(Matrix::identityMatrix(4), origin);
  return Ray{{newOrigin.x, newOrigin.y, newOrigin.z}, {newDirection.x, newDirection.y, newDirection.z}};
}

Ray Ray::transform(Matrix matrix) const{
  Tuple newOrigin = tupleMultiply(matrix, origin);
  Tuple newDirection = tupleMultiply(matrix, direction);
  return Ray{{newOrigin.x, newOrigin.y, newOrigin.z}, {newDirection.x, newDirection.y, newDirection.z}}; 
}

bool Ray::equal(Ray const& other) const{
  return (
    origin == other.origin &&
    direction == other.direction
  );
}

Intersections* raySphereIntersect(Ray const& ray, Sphere const& sphere){
  Tuple sphereToRay = ray.origin.subtractTuple(point(0, 0, 0));

  float a = ray.direction.dot(ray.direction);
  float b = 2 * ray.direction.dot(sphereToRay);
  float c = sphereToRay.dot(sphereToRay) - 1;

  float discriminant = (b * b) - (4 * a * c);
    
  Intersections* intersections = new Intersections;

  if(discriminant < 0){
    return intersections;
  }
}


