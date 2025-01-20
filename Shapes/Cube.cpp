
#include "Floats.h"
#include "Intersection.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuple.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include "Cube.h"
  
std::array<float, 2> Cube::checkAxis(float origin, float direction){
  float tMinNum = (-1 - origin);
  float tMaxNum = (1 - origin);
  
  float tMin;
  float tMax;

  if(fabs(direction) >= EPSILON){
    tMin = tMinNum / direction;
    tMax = tMaxNum / direction;
  }else{
    tMin = std::numeric_limits<float>::infinity() * tMinNum;
    tMax = std::numeric_limits<float>::infinity() * tMaxNum;
  }

  if(tMin > tMax){
    return {tMax, tMin};
  }else{
    return {tMin, tMax};
  }
}

std::shared_ptr<Intersections> Cube::localIntersect(Ray ray){
  auto xt = checkAxis(ray.origin.x, ray.direction.x);
  float xtMin = xt[0];
  float xtMax = xt[1];

  auto yt = checkAxis(ray.origin.y, ray.direction.y);
  float ytMin = yt[0];
  float ytMax = yt[1];
  
  auto zt = checkAxis(ray.origin.z, ray.direction.z);
  float ztMin = zt[0];
  float ztMax = zt[1];

  float tMin = std::fmax(xtMin, std::fmax(ytMin, ztMin));
  float tMax = std::fmin(xtMax, std::fmin(ytMax, ztMax));
  
  std::shared_ptr<Intersections>inters (new Intersections{});

  if(tMin > tMax){
    return inters;
  }

  inters->add({tMin, this});
  inters->add({tMax, this});

  return inters;
}

Tuple Cube::normalAt(Tuple const& worldPoint, Intersection const* intersection){

  Tuple local = tupleMultiply(getInverseTransform(), worldPoint);
  
  float absX = std::fabs(local.x);
  float absY = std::fabs(local.y);
  float absZ = std::fabs(local.z);

  float maxC = std::fmax(absX, std::fmax(absY, absZ));

  if(floatsEqual(maxC, absX)){
    return vector(local.x, 0, 0);
  }else if(floatsEqual(maxC, absY)){
    return vector(0, local.y, 0);
  }else{
    return vector(0, 0, local.z);
  }

};
Tuple Cube::normalAt(Tuple const& worldPoint){
  return normalAt(worldPoint, nullptr);
}
