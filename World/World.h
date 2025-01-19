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

  void addShape(std::shared_ptr<Shape> shape_p);
  
  std::vector<std::shared_ptr<Shape>> shapes;
  Light light;
};

World createDefaultWorld(); 

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world);

bool isShadowed(World world, Tuple point);
Color shadeHit(World world, Computations comps, int reflectionsLeft);

float schlick(Computations computations);

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world); 

Color colorAt(Ray ray, World world, int reflectionsLeft);

Color reflectedColor(World world, Computations computations, int reflectionsLeft);
Color refractedColor(World world, Computations computations, int reflectionsLeft);

Canvas render(Camera camera, World world);
Canvas renderPixel(Camera camera, World world, size_t x, size_t y);

#endif // !WORLD_WORLD_H_
