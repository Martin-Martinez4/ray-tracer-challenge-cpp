#include "002_purple_ball.h"
#include "Tuple.h"
#include "Canvas.h"
#include "Sphere.h"
#include "Color.h"

Canvas Ex002(){

  Tuple rayOrigin = point(0, 0, -5);
  float wallZ = 10.0f;
  int wallSize = 7;
  float half = wallSize / 2;

  int canvasPixels = 100;
  int pixelSize =  wallSize / canvasPixels;

  Canvas canvas = Canvas(canvasPixels, canvasPixels);

  Sphere sphere = Sphere();
  sphere.setColor(Color(1,1,1));

  return canvas;

  
}