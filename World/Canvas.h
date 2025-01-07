#ifndef WORLD_CANVAS_H_
#define WORLD_CANVAS_H_

#include <cstddef>
#include <vector>
#include "Color.h"
#include <sstream>


class Canvas {
public:
  Canvas():Canvas(10, 10){};
  Canvas(size_t width, size_t height):width{width},height{height},canvas{std::vector<Color>(width*height, Color())}{};
  Canvas(size_t width, size_t height, Color color):width{width},height{height},canvas{std::vector<Color>(width*height, color)}{};

  size_t width;
  size_t height;
  std::vector<Color> canvas;

  Color getPixel(size_t x, size_t y);
  void setPixel(size_t x, size_t y, Color color);

};

#endif // !WORLD_CANVAS_H_
