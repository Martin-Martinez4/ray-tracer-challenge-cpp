#ifndef SHAPES_INTERSECTION_H_
#define SHAPES_INTERSECTION_H_

#include "Tuple.h"
#include <algorithm>
#include <array>
#include <vector>

class Shape;

struct Intersection{
  float t;
  Shape* s;
};

struct IntersectionUV: public Intersection{
  float u;
  float v;
};

struct computations {
  float t;
  Shape* object;
  Tuple point;
  Tuple eyeV;
  Tuple normalV;
  Tuple overPoint;
  Tuple underPoint;
  Tuple reflectV;
  bool inside;
  float n1;
  float n2;

};

class Intersections {
public: 
  Intersections():inters{std::vector<Intersection>()}{};
  Intersections(std::vector<Intersection> inters):inters{std::move(inters)}{};

  void add(Intersection value);
  Intersection get(size_t i) const;
  size_t size() const;

  Intersection getLowestPositive();
  Intersection* hit();

  bool equal(Intersections const& other) const;

  bool operator==(Intersections const& other) const {
    return equal(other);
  }

  

private:
  std::vector<Intersection> inters;

};



#endif // !SHAPES_INTERSECTION_H_

