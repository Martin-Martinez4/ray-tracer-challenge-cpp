#include "World.h"
#include "Ray.h"
#include "Sphere.h"
#include <array>
#include <cstddef>
#include <iostream>
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

Color shadeHit(World world, Computations comps){
  
  return lighting(comps.object->getMaterial(), world.light, comps.point, comps.eyeV, comps.normalV, false);
}

std::shared_ptr<Intersections> rayWorldIntersect(Ray ray, World world){
  std::shared_ptr<Intersections> inters(new Intersections());

  for(size_t i = 0; i < world.shapes.size(); ++i){
    inters->rayShapeIntersect(ray, world.shapes[i]);
  }

  return inters;
}

Color colorAt(Ray ray, World world, int reflectionsLeft){
  std::shared_ptr<Intersections> inters = rayWorldIntersect(ray, world);
  
  Intersection* intersection = inters->hit();

  if(intersection == nullptr){
    return Color(0,0,0);
  }else{
    return shadeHit(world, Computations(ray, *intersection));
  }

}

Canvas render(Camera camera, World world){
  // h = horizontal, v = vertical
  Canvas image = Canvas(camera.hSize, camera.vSize);
  
  for(size_t y = 0; y < camera.vSize-1; ++y){
    for(size_t x = 0; x < camera.hSize-1; ++x){
      Ray ray = camera.rayForPixel(x, y);
      Color c = colorAt(ray, world, 1);
      image.setPixel(x, y, c);
    }
  }

  return image;
}



