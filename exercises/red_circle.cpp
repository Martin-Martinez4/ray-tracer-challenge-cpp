#include "Sphere.h"
#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"
#include "Ray.h"
#include "Intersection.h"
#include <memory>
#include <iostream>

Canvas Ex001(){
  float canvasPixels = 300;
  Tuple rayOrigin = point(0,0,-5);
  float wallSize = 7;
  float wallZ = 10;
  float half = wallSize/2;
  float pixelSize = wallSize / canvasPixels;

  Canvas canvas = Canvas(canvasPixels, canvasPixels);
  Color color2 = Color(125, 207, 180);
  Color color1 = Color(255, 255, 255);
  Sphere shape = Sphere();

  for(size_t  y = 0; y < canvasPixels; ++y){

    float worldY = half - pixelSize * float(y);

    for(size_t  x = 0; x < canvasPixels; ++x){

      float worldX = -half + pixelSize * float(x);

      Tuple position = point(worldX, worldY, wallZ);
      Tuple temp = position.subtractTuple(rayOrigin);
      Tuple normalized = normalize(temp);

      Ray r = Ray{rayOrigin, normalized};


      std::shared_ptr<Intersections> xs = raySphereIntersect(r, &shape);

      if((*xs).size() > 0){
        canvas.setPixel(x, y, color2);
      }else{
        canvas.setPixel(x, y, color1);

      }
    
    } 
  }

  return canvas;
}
