
#ifndef MATH_TUPLE_H_
#define MATH_TUPLE_H_

#include "Floats.h"
#include "ostream"

struct Tuple;

Tuple point(float x, float y, float z);
Tuple vector(float x, float y, float z);

bool isPoint(Tuple const& tuple);
bool isVector(Tuple const& tuple);

Tuple normalize(Tuple& tuple);

struct Tuple {

  Tuple(float x, float y, float z):Tuple::Tuple(x, y, z, 0){};
  Tuple(float x, float y, float z, float w):x(x), y(y), z(z), w(w){}

  float x;
  float y;
  float z;
  float w;


  float dot(Tuple const& tuple) const;
  Tuple cross(Tuple const& tuple) const;

  Tuple addTuple(Tuple tuple) const;
  Tuple addScalar(float f) const;

  Tuple subtractTuple(Tuple tuple) const;
  Tuple subtractScalar(float f) const;

  Tuple multiplyScalar(float f) const;
  Tuple divideScalar(float f) const;
  
  Tuple negate() const;

  float magnitude();

  bool equal(Tuple const& tuple);

  Tuple reflect(Tuple const& normal) const; 

  bool operator==(Tuple const& other) const{
    return (
      FloatsEqual(x, other.x) && 
      FloatsEqual(y, other.y) && 
      FloatsEqual(z, other.z) && 
      FloatsEqual(w, other.w)
    );
  }

  Tuple operator-(){
    return Tuple{-x, -y, -z, -w};
  }
  /*

  Tuple operator-(Tuple const& tuple){
    return Tuple{x - tuple.x , y - tuple.y, z - tuple.z, w - tuple.w};
  }
  Tuple operator-(float f){
    return Tuple{x + f, y + f, z + f, w + f};
  }


  Tuple operator+(Tuple const& tuple) {
      return Tuple{x + tuple.x , y + tuple.y, z + tuple.z, w + tuple.w};
  }
  Tuple operator+(float f){
    return Tuple{x + f, y + f, z + f, w + f};
  }

  Tuple operator*(Tuple const& tuple){
    return Cross(*this, tuple);
  }
  Tuple operator*(float f){
    return Tuple{x*f, y*f, z*f, w*f};
  }

  Tuple operator/(float f){
  return Tuple{x/f, y/f, z/f, w/f};
    
  }
  */

  friend std::ostream& operator<<(std::ostream &os, const Tuple& p);

};


#endif


