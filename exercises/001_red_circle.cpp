#include "Sphere.h"
#include "Shape.h"
#include "Canvas.h"
#include "Color.h"
#include "Tuple.h"
#include "Intersection.h"
#include "Ray.h"
#include <cstddef>
#include <memory>
#include <iostream>
#include "001_red_circle.h"

Canvas Ex001(){
  std::clog << "Start \n";

  float canvasPixels = 400;
  Tuple rayOrigin = point(0,0,-5);
  float wallSize = 7;
  float wallZ = 10;
  float half = wallSize/2;
  float pixelSize = wallSize / canvasPixels;

  Color bgColor = Color(0.9765, 0.878, 0.8509);
  Color color1 = Color(1.0f, 1.0f, 1.0f);
  Color color2 = Color(0.49f, 0.8118f, 0.7059f);
  Color color3 = Color(0.9412f, 0.3961f, 0.2627f);
  Color color4 = Color(0.4706f, 0.1608f, 0.0588f);

  Canvas canvas = Canvas(canvasPixels, canvasPixels, bgColor );
  
  Sphere blue = Sphere();
  blue.setColor(color2);
  blue.setTransform(Matrix::scale(1.1, 1.1, 1.1));

  Sphere orange = Sphere();
  orange.setColor(color3);

  Sphere white = Sphere();
  white.setColor(color1);
  white.setTransform(Matrix::scale(.6,.6,.6));

  Sphere red = Sphere();
  red.setColor(color4);
  red.setTransform(Matrix::scale(.5,.5,.5));
  
  
  std::array<Sphere*, 4> shapes = {&blue, &orange, &white, &red};

  for(size_t  y = 0; y < canvasPixels; ++y){

    float worldY = half - pixelSize * float(y);

    for(size_t  x = 0; x < canvasPixels; ++x){

      float worldX = -half + pixelSize * float(x);

      Tuple position = point(worldX, worldY, wallZ);
      Tuple temp = position - rayOrigin;
      Tuple normalized = normalize(temp);

      Ray r = Ray{rayOrigin, normalized};

      for(size_t s = 0; s < 4; ++s){

        std::shared_ptr<Intersections> xs (raySphereIntersect(r, shapes[s]));

        if((*xs).size() > 0){ 
          canvas.setPixel(x, y, shapes[s]->getColor());
        }
      }

    
    } 
  }
  std::clog << "Ran \n";

  return canvas;
}
