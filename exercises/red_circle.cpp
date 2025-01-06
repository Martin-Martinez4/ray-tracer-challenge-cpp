#include "Sphere.h"
#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"
#include "Ray.h"
#include "Intersection.h"
#include <memory>
#include <iostream>

Canvas Ex001(){
  size_t canvasPixels = 100;
  Tuple rayOrigin = point(0,0,-5);
  int wallSize = 7;
  int wallZ = 10;
  int half = wallSize/2;
  int pixelSize = wallSize / canvasPixels;

  Canvas canvas = Canvas(canvasPixels, canvasPixels);
  Color color = Color(125, 207, 180);
  Sphere shape = Sphere();

  for(size_t  y = 0; y < canvasPixels; ++y){

    int worldY = half - pixelSize * y;

    for(size_t  x = 0; x < canvasPixels; ++x){

      int worldX = -half + pixelSize * x;

      Tuple position = point(worldX, worldY, wallZ);
      Tuple normalized = normalize(position.subtractTuple(rayOrigin));

      Ray r = Ray{rayOrigin, normalized};

      std::shared_ptr<Intersections> xs = raySphereIntersect(r, &shape);

      if((*xs).size() < 0){
        canvas.setPixel(x, y, color);
      }
    
    } 
  }

  return canvas;
}
