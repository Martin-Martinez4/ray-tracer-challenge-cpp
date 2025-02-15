#ifndef SHAPES_INTERSECTION_H_
#define SHAPES_INTERSECTION_H_

#include "Floats.h"
#include "Tuple.h"
#include <memory>
#include <ostream>
#include <vector>

class Shape;
struct Ray;
class Intersections;

struct Intersection{
  float t;
  Shape* s;

  bool operator==(Intersection const& other) const {
    return (t == other.t && s == other.s);
  }

  friend std::ostream& operator<<(std::ostream &os, const Intersection& i);
};

struct IntersectionUV: public Intersection{
  float u;
  float v;

  bool operator==(Intersection const& other) const {
    return (t == other.t && s == other.s);
  }
};

class Intersections {
public: 
  Intersections():inters{std::vector<Intersection>{}}{};
  Intersections(std::vector<Intersection> inters):inters{std::move(inters)}{};

  void add(Intersection value);
  Intersection get(size_t i) const;
  size_t size() const;

  Intersection getLowestPositive();
  Intersection* hit();

  void rayShapeIntersect(Ray ray, std::shared_ptr<Shape> shape);

  bool equal(Intersections const& other) const;

  bool operator==(Intersections const& other) const {
    return equal(other);
  }

  friend std::ostream& operator<<(std::ostream &os, const Intersections& is);
  

private:
  std::vector<Intersection> inters;

};

struct Computations {
  Computations(Ray ray, Intersection intersection, std::shared_ptr<Intersections> xs = std::shared_ptr<Intersections>(new Intersections()));
  Computations(float t, Shape* object, Tuple point, Tuple eyeV, Tuple normalV, bool inside): t{t}, object{object}, point{point}, eyeV{eyeV}, normalV(normalV), inside{inside}{};

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
  
  bool operator==(Computations const & other) const{
    return (
      floatsEqual(t, other.t) &&
      object == other.object &&
      point == other.point &&
      eyeV == other.eyeV &&
      normalV == other.normalV &&
      inside == other.inside
    );
  }

   
  friend std::ostream& operator<<(std::ostream &os, const Computations& c);

};

Computations prepareComputations(Intersection intersection, Ray ray);


#endif // !SHAPES_INTERSECTION_H_

