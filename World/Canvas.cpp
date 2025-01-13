
#include "Canvas.h"
#include "Color.h"
#include <cstddef>


Color Canvas::getPixel(size_t x, size_t y){
  return canvas[x*height + y];
}

void Canvas::setPixel(size_t x, size_t y, Color color){
  canvas[x*height + y] = color;
}


