#ifndef WORLD_LIGHT_H_
#define WORLD_LIGHT_H_

#include "Intersection.h"
#include "Tuple.h"
#include "Shape.h"
#include "Color.h"
#include <array>

struct Material;

struct Light {
  Light():intensity{Color(255, 255, 255)}, position{point(0,0,0)}{};
  Light(Tuple position, Color color):intensity{color}, position{position}{};
  Light(std::array<float, 3> p, std::array<float, 3> rgb):intensity{Color(rgb[0], rgb[1], rgb[2])}, position{point(p[0], p[1], p[2])}{};

  Color intensity;
  Tuple position;
};

Color lighting(Material material, Shape* shape, Light light, Tuple point, Tuple eyeVec, Tuple normalVec, bool inShadow);


#endif
