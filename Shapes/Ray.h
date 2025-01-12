#ifndef SHAPES_RAY_H_
#define SHAPES_RAY_H_

#include "Intersection.h"
#include "Matrix.h"
#include "Tuple.h"
#include "Sphere.h"
#include <array>
#include <memory>

struct Ray{
  Ray():origin{point(0,0,0)}, direction{point(0,0,0)}{}
  Ray(std::array<float, 3>origin, std::array<float, 3>direction):origin{point(origin[0], origin[1], origin[2])}, direction{vector(direction[0], direction[1], direction[2])}{};
  Ray(Tuple origin, Tuple direction):origin(point(origin.x, origin.y, origin.z)), direction{vector(direction.x, direction.y, direction.z)}{};

  Tuple origin;
  Tuple direction;

  Tuple position(float f) const;
  Ray translate(float x, float y, float z) const;
  Ray scale(float x, float y, float z) const;
  Ray transform(Matrix matrix) const;
  bool equal(Ray const& other) const;
};

std::shared_ptr<Intersections> raySphereIntersect(Ray const& ray, Sphere* sphere);

#endif // !SHAPES_RAY_H_
