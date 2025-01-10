
#include "Matrix.h"
#include "Tuple.h"
#include "Sphere.h"

Tuple Sphere::normalAt(Tuple worldPoint) {
  
  Tuple objectPoint = tupleMultiply(getInverseTransform(), worldPoint);
  Tuple objectNormal = objectPoint.subtractTuple(point(0,0,0));
  Tuple worldNormal = tupleMultiply(getInverseTransform().transpose(), objectNormal);
  worldNormal.w = 0;
  // Tuple wp = worldPoint.subtractTuple(point(0,0,0));
  return normalize(worldNormal);
}


