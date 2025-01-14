
#include "Canvas.h"
#include "Color.h"
#include <cstddef>
#include <iostream>


// Color Canvas::getPixel(size_t x, size_t y){

//   return canvas[x + y*height];
// }

// void Canvas::setPixel(size_t x, size_t y, Color color){
 
//   canvas[x + y*height] = color;
// }

Color Canvas::getPixel(size_t x, size_t y){

  return canvas[y][x];
}

void Canvas::setPixel(size_t x, size_t y, Color color){
 
  canvas[y][x] = color;
}


