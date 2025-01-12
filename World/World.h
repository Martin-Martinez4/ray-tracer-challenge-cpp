#ifndef WORLD_WORLD_H_
#define WORLD_WORLD_H_

#include "Intersection.h"
#include "Shape.h"
#include "Light.h"
#include <memory>
#include <vector>

struct World{
  World(std::vector<std::shared_ptr<Shape>> shapes, Light light):shapes{std::move(shapes)}, light{light}{};
  
  std::vector<std::shared_ptr<Shape>> shapes;
  Light light;
};

World createDefaultWorld(); 

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world);

Color shadeHit(World world, Computations comps);

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world);

Color colorAt(Ray ray, World world, int reflectionsLeft);

#endif // !WORLD_WORLD_H_
