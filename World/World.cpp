#include "World.h"
#include "Floats.h"
#include "Ray.h"
#include "Sphere.h"
#include <array>
#include <cstddef>
#include "Tuple.h"
#include <iostream>
#include <memory>
#include <cmath>

void World::addShape(std::shared_ptr<Shape> shape_p){
 shapes.push_back(shape_p); 
}
World createDefaultWorld(){
  Material mat1 = Material();
  mat1.diffuse = 0.7f;
  mat1.specular = 0.2f;
  mat1.color = Color(0.8f, 1.0f, 0.6f);

  std::shared_ptr<Shape> sphere1 (new Sphere{mat1});

  std::shared_ptr<Shape> sphere2 (new Sphere());
  sphere2->setTransform(Matrix::scale(0.5, 0.5, 0.5));

  Light light = Light(std::array<float, 3>{-10, 10,-10}, std::array<float, 3>{1,1,1});

  return World(std::vector<std::shared_ptr<Shape>>{std::move(sphere1), std::move(sphere2)}, light);
}

bool isShadowed(World world, Tuple point){
  Tuple v = world.light.position - point;
  float distance = v.magnitude();
  Tuple direction = normalize(v);

  Ray r = Ray{point, direction};

  std::shared_ptr<Intersections> xs = rayWorldIntersect(r, world);

  Intersection* h = xs->hit();

  if(h != nullptr && h->t < distance){
    return true;
  }
  return false;

}

Color shadeHit(World world, Computations comps, int reflectionsLeft){
  bool shadowed = isShadowed(world, comps.overPoint);
  
  Color surface = lighting(comps.object->getMaterial(), comps.object, world.light, comps.overPoint, comps.eyeV, comps.normalV, shadowed);
  Color reflected = reflectedColor(world, comps, reflectionsLeft);
  Color refracted = refractedColor(world, comps, reflectionsLeft);

  Material mat = comps.object->getMaterial();

  if(mat.reflective > 0 && mat.transparency > 0){
    float reflectance = schlick(comps);
    
    reflected = reflected * reflectance;
    refracted = refracted * (1-reflectance);
  }
  
  

  return surface + reflected + refracted; 
}

float schlick(Computations computations){
  float n1 = computations.n1;
  float n2 = computations.n2;

  float cos = computations.eyeV.dot(computations.normalV);
  
  if(n1 > n2){
    float n = n1 / n2;
    float sin2t = (n * n) * (1 - (cos * cos));
  
    if(sin2t > 1){
      return 1.0f;
    }

    float cosT = sqrtf(1- sin2t);
    cos = cosT;
  }

  float r0 = powf(( (n1 - n2)/(n1 + n2) ), 2);
  return r0 + (1-r0) * powf((1-cos), 5);

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
    //std::cout << "ray: " << ray << "\n";
    //std::cout << "intersection " << intersection << "\n";
    Computations c = Computations(ray, *intersection, inters);
    return shadeHit(world, c, reflectionsLeft);
  }

}

Color reflectedColor(World world, Computations computations, int reflectionsLeft){
  if(computations.object->getMaterial().reflective < EPSILON || reflectionsLeft <= 0){
    return Color(0,0,0);
  }else{
    Ray reflectRay =Ray(computations.overPoint, computations.reflectV);
    Color color = colorAt(reflectRay, world, reflectionsLeft-1);

    return color * computations.object->getMaterial().reflective;
  }
}

Color refractedColor(World world, Computations computations, int reflectionsLeft){
  if(computations.object->getMaterial().transparency == 0 || reflectionsLeft <= 0){
    return Color(0,0,0);
  }

  float nRatio = computations.n1 / computations.n2;
  float cosI = computations.eyeV.dot(computations.normalV);
  float sin2T = (nRatio * nRatio) * (1 - (cosI * cosI));

  if(sin2T > 1){
    return Color(0,0,0);
  }

  float cosT = sqrtf(1.0 - sin2T);

  Tuple d1 = computations.normalV * ((nRatio * cosI) - cosT);
  Tuple d2 = computations.eyeV * nRatio;
  Tuple direction = d1 - d2;
  //std::cout << "== remaining " << reflectionsLeft << "==\n";
  //std::cout << "comps: " << computations << "\n";
  //std::cout << "d1: " << d1 << "\n";
  //std::cout << "d2: " << d2 << "\n";
  //std::cout << "direction: " << direction << "\n";

  Ray refractRay = Ray{computations.underPoint, direction};

  //std::cout << "\nrefractedColor: " << (colorAt(refractRay, world, reflectionsLeft - 1) * computations.object->getMaterial().transparency) << "\n";

  return colorAt(refractRay, world, reflectionsLeft - 1) * computations.object->getMaterial().transparency;
}

Canvas render(Camera camera, World world){
  // h = horizontal, v = vertical
  Canvas image = Canvas(camera.hSize, camera.vSize);
  
  for(size_t y = 0; y < camera.vSize-1; ++y){
    for(size_t x = 0; x < camera.hSize-1; ++x){
    
      Ray ray = camera.rayForPixel(x, y);
      Color c = colorAt(ray, world, 5);
      image.setPixel(x, y, c);
    }
  }

  return image;
}

Canvas renderPixel(Camera camera, World world, size_t x, size_t y){

  Canvas image = Canvas(camera.hSize, camera.vSize);

  Ray ray = camera.rayForPixel(x, y);
  Color c = colorAt(ray, world, 5);
  image.setPixel(x, y, c);

  return image;
}



