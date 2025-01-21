
#include "Cone.h"
#include "Floats.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"
#include <cmath>

bool Cone::checkCap(Ray ray, float t, float y){
  float x = ray.origin.x + t * ray.direction.x;
  float z = ray.origin.z + t * ray.direction.z;

  return (powf(x, 2.0f) + powf(z, 2.0f)) <= 2.0f;
}

void Cone::intersectCaps(Ray ray, std::shared_ptr<Intersections> intersections){
  if(!closed || fabs(ray.direction.y) < EPSILON){
    return;
  }

  float t = (minimum - ray.origin.y) / ray.direction.y;
  if(checkCap(ray, t, fabs(minimum))){
    intersections->add(Intersection{t, this});
  }

  t = (maximum - ray.origin.y) / ray.direction.y;
  if(checkCap(ray, t, fabs(maximum))){
    intersections->add(Intersection{t, this});
  }
}

std::shared_ptr<Intersections> Cone::localIntersect(Ray ray){
  float a = powf(ray.direction.x, 2) - powf(ray.direction.y, 2) + powf(ray.direction.z, 2);
  float b = 2 * ((ray.origin.x * ray.direction.x) - (ray.origin.y * ray.direction.y) + (ray.origin.z * ray.direction.z)); 
  float c = powf(ray.origin.x, 2) - powf(ray.origin.y, 2) + powf(ray.origin.z, 2);
  
  std::shared_ptr<Intersections> intersections (new Intersections());

  if(fabs(a) < EPSILON && fabs(b) < EPSILON){
    return std::shared_ptr<Intersections> (new Intersections());
  }
  if(fabs(a) < EPSILON){

    float t = -c / (b * 2.0f);
    intersections->add(Intersection{t, this});
  }

  float disc = powf(b, 2.0f) - (4 * a * c);
  if(fabs(disc) < 0.0){
    return std::shared_ptr<Intersections> (new Intersections());
  }

  float t0 = (-b - sqrtf(disc)) / (2 * a);
  float t1 = (-b + sqrtf(disc)) / (2 * a);
  if (t0 > t1) {
    std::swap(t0, t1);
  }

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

Tuple Cone::normalAt(Tuple const& worldPoint, Intersection const* intersection){
  return normalAt(worldPoint);
}
Tuple Cone::normalAt(Tuple const& worldPoint){

  Tuple localPoint = tupleMultiply(getInverseTransform(), worldPoint);

  float dist = pow(localPoint.x, 2.0) + pow(localPoint.z, 2.0);

  if(dist <= powf(maximum, 2.0f) && localPoint.y >= (maximum - EPSILON)){
    return vector(0, 1, 0);
  }else if(dist <= powf(minimum, 2.0f) && localPoint.y <= minimum + EPSILON){
    return vector(0, -1, 0);
  }else{

    float y;
    if(localPoint.y > 0){
      y = -sqrtf(dist);
    }else{
      y = sqrtf(dist);
    }
    return vector(localPoint.x, y, localPoint.z);
  }
}
