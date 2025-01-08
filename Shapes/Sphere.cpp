
#include "Matrix.h"
#include "Tuple.h"
#include "Sphere.h"

Tuple Sphere::normalAt(Tuple worldPoint) {
  Matrix invTransform = getInverseTransform();
  Tuple objectPoint = tupleMultiply(invTransform, worldPoint);
  Tuple objectNormal = objectPoint.subtractTuple(point(0,0,0));
  Tuple worldNormal = tupleMultiply(getInverseTransform().transpose(), objectNormal);
  worldNormal.z = 0;
  return normalize(worldNormal);
}


