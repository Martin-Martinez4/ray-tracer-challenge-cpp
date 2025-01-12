#include "World.h"
#include "Intersection.h"
#include "Ray.h"
#include "Light.h"
#include "Shape.h"
#include "Sphere.h"
#include <array>
#include <memory>

World createDefaultWorld(){
  Material mat1 = Material();
  mat1.diffuse = 0.7f;
  mat1.specular = 0.2f;
  mat1.color = Color(0.8f, 1.0f, 0.6f);

  std::shared_ptr<Shape> sphere1 (new Sphere{mat1});

  std::shared_ptr<Shape> sphere2 (new Sphere());
  sphere2->setTransform(Matrix::scale(0.5, 0.5, 0.5));

  Light light = Light(std::array<float, 3>{-10,-10,-10}, std::array<float, 3>{1,1,1});

  return World(std::vector<std::shared_ptr<Shape>>{std::move(sphere1), std::move(sphere2)}, light);
}

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world){
  return nullptr;
}

Color shadeHit(World world, Computations comps){
  
  return lighting(comps.object->getMaterial(), world.light, comps.point, comps.eyeV, comps.normalV, false);
}




