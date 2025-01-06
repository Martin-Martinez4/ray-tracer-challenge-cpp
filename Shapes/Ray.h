#ifndef SHAPES_RAY_H_
#define SHAPES_RAY_H_

#include "Intersection.h"
#include "Matrix.h"
#include "Tuple.h"
#include "Sphere.h"
#include <array>

struct Ray{
  Ray():origin{point(0,0,0)}, direction{point(0,0,0)}{}
  Ray(std::array<float, 3>origin, std::array<float, 3>direction):origin{point(origin[0], origin[1], origin[3])}, direction{point(direction[0], direction[1], direction[2])}{};

  Tuple origin;
  Tuple direction;

  Tuple position(float f) const;
  Ray translate(float x, float y, float z) const;
  Ray scale(float x, float y, float z) const;
  Ray transform(Matrix matrix) const;
  bool equal(Ray const& other) const;
};

Intersections* raySphereIntersect(Ray const& ray, Sphere const& sphere);

#endif // !SHAPES_RAY_H_
