#include "Tuple.h"
#include "Floats.h"
#include <cmath>

Tuple point(float x, float y, float z){
  return Tuple(x, y, z, 1);
}
Tuple vector(float x, float y, float z){
  return Tuple(x, y, z, 0);
}

bool isPoint(Tuple const& tuple){
  return tuple.w == 1;
}
bool isVector(Tuple const& tuple){
  return tuple.w == 0;
}

Tuple normalize(Tuple& tuple){
  float m = tuple.magnitude();

  return Tuple{
    tuple.x/m,
    tuple.y/m,
    tuple.z/m,
    tuple.w/m
  };
}

float Tuple::dot(Tuple const& tuple) const {
  return x*tuple.x + y*tuple.y + z*tuple.z + w+tuple.w;
}
Tuple Tuple::cross(Tuple const& tuple) const{
  return vector(
    y*tuple.z-z*tuple.y,
    z*tuple.x-x*tuple.z,
    x*tuple.y-y*tuple.x
  ); 
}

Tuple Tuple::addTuple(Tuple tuple) const{
  return Tuple{x+tuple.x, y+tuple.y, z+tuple.z, w+tuple.w};
}
Tuple Tuple::addScalar(float f) const{
  return Tuple{x+f, y+f, z+f, w+f};
}

Tuple Tuple::subtractTuple(Tuple tuple) const{
  return Tuple{x-tuple.x, y-tuple.y, z-tuple.z, w-tuple.w};
}
Tuple Tuple::subtractScalar(float f) const{
  return Tuple{x-f, y-f, z-f, w-f};
}

Tuple Tuple::multiplyScalar(float f) const {
  return Tuple{x*f, y*f, z*f, w*f};
}
Tuple Tuple::divideScalar(float f) const {

  return Tuple{x/f, y/f, z/f, w/f};
}

Tuple Tuple::negate() const{
  return Tuple{-x, -y, -z, -w};
}

float Tuple::magnitude(){
  return sqrtf((x*x) + (y*y) + (z*z) + (w*w));
}

bool Tuple::equal(Tuple const& tuple){
  return (
    FloatsEqual(x, tuple.x) && 
    FloatsEqual(y, tuple.y) && 
    FloatsEqual(z, tuple.z) && 
    FloatsEqual(w, tuple.w)
  );
}

Tuple Tuple::reflect(Tuple const& normal) const {
  return this->subtractTuple(
    normal.multiplyScalar(normal.dot(*this) * 2)
  );
}

std::ostream& operator<<(std::ostream &os, const Tuple& tuple){
    return os << "Tuple: { x: " << tuple.x << ", y: " << tuple.y << ", z: " << tuple.z << ", w: " << tuple.w << " }";
}




