
#include "Color.h"

struct Material {

  Color color;
  float ambient = 0.1;
  float diffuse = 0.9;
  float specular = 0.9;
  float shiniess = 200.0;
  float reflective = 0;
  float transparency = 0;
  float refractiveIndex = 1;
};


