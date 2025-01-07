#include "Sphere.h"
#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"
#include "Ray.h"
#include "Intersection.h"
#include <cstddef>
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
  Color bgColor = Color(249, 224, 217);
  Color color2 = Color(125, 207, 180);
  Color color3 = Color(240, 101, 67);
  Color color4 = Color(120, 41, 15);

  Sphere blue = Sphere();
  blue.setColor(color2);

  Sphere orange = Sphere();
  orange.setColor(color3);

  Sphere red = Sphere();
  red.setColor(color4);
  
  std::array<Sphere*, 3> shapes = {&orange, &blue, &red};

  for(size_t  y = 0; y < canvasPixels; ++y){

    float worldY = half - pixelSize * float(y);

    for(size_t  x = 0; x < canvasPixels; ++x){

      float worldX = -half + pixelSize * float(x);

      Tuple position = point(worldX, worldY, wallZ);
      Tuple temp = position.subtractTuple(rayOrigin);
      Tuple normalized = normalize(temp);

      Ray r = Ray{rayOrigin, normalized};

      for(size_t s = 0; s < 3; ++s){

        std::shared_ptr<Intersections> xs = raySphereIntersect(r, shapes[s]);

        if((*xs).size() > 0){ 
          canvas.setPixel(x, y, shapes[s]->getColor());
        }else{
          canvas.setPixel(x, y, bgColor);

        }
      }

    
    } 
  }

  return canvas;
}
