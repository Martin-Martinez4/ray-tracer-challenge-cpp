
#include "Color.h"

struct Material {

  Color color = Color(1, 1, 1);
  float ambient = 0.1f;
  float diffuse = 0.9f;
  float specular = 0.9f;
  float shininess = 200.0f;
  float reflective = 0;
  float transparency = 0;
  float refractiveIndex = 1;

};


