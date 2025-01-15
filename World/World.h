#ifndef WORLD_WORLD_H_
#define WORLD_WORLD_H_


#include "Intersection.h"
#include "Shape.h"
#include "Light.h"
#include "Canvas.h"
#include "Camera.h"
#include <memory>
#include <vector>

struct World{
  World(std::vector<std::shared_ptr<Shape>> shapes, Light light):shapes{std::move(shapes)}, light{light}{};
  
  std::vector<std::shared_ptr<Shape>> shapes;
  Light light;
};

World createDefaultWorld(); 

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world);

bool isShadowed(World world, Tuple point);
Color shadeHit(World world, Computations comps);

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world); 

Color colorAt(Ray ray, World world, int reflectionsLeft);

Canvas render(Camera camera, World world);

#endif // !WORLD_WORLD_H_
