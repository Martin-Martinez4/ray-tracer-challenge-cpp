#include "Floats.h"
#include <cmath>

bool FloatsEqual(float first, float second){
  return fabs(first - second) < EPSILON;
}

