#include "002_purple_ball.h"
#include "Tuple.h"
#include "Canvas.h"
#include "Sphere.h"
#include "Color.h"
#include "Light.h"
#include "Ray.h"
#include "Intersection.h"
#include "Constants.h"

Canvas Ex002(){
  
std::clog << "Start \n";

  float canvasPixels = 200;
  Tuple rayOrigin = point(0,0,-5);
  float wallSize = 7;
  float wallZ = 10;
  float half = wallSize/2;
  float pixelSize = wallSize / canvasPixels;

  Light light = Light(point(-10, 10, -10), Color(1, 1, 1));

  Color bgColor = Color(0.9765, 0.878, 0.8509);
  Color color1 = Color(1.0f, 1.0f, 1.0f);
  Color color2 = Color(0.314f, 0.188f, 0.278f);

  Canvas canvas = Canvas(canvasPixels, canvasPixels);
  
  Sphere violet = Sphere();
  violet.setColor(color2);
  violet.setTransforms({
    Matrix::scale(1, 0.5f, 1),
    Matrix::rotationAlongY(M_PI_2)
  });

  

  for(size_t  y = 0; y < canvasPixels; ++y){

    float worldY = half - pixelSize * float(y);

    for(size_t  x = 0; x < canvasPixels; ++x){

      float worldX = -half + pixelSize * float(x);

      Tuple position = point(worldX, worldY, wallZ);
      Tuple temp = position.subtractTuple(rayOrigin);
      Tuple normalized = normalize(temp);

      Ray r = Ray{rayOrigin, normalized};


        std::shared_ptr<Intersections> xs = raySphereIntersect(r, &violet);

        if((*xs).size() > 0){ 
          Intersection* found = (*xs).hit();


        if(found != nullptr){
          Tuple point =  r.position(found->t);
          Tuple normal = found->s->normalAt(point);
          Tuple eye = r.direction.multiplyScalar(-1);

          Color color = lighting(found->s->getMaterial(), light, point, eye, normal, false);

          canvas.setPixel(x, y, color);
        }
      }

    
    } 
  }
  std::clog << "Ran \n";

  return canvas;
  
}
