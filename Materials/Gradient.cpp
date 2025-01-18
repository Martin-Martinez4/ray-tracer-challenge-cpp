
#include "Gradient.h"
#include "Pattern.h"
#include <cmath>

Gradient::Gradient():Pattern(){};
Gradient::Gradient(Color color1):Pattern(color1){};
Gradient::Gradient(Color color1, Color color2):Pattern(color1, color2){};

Color Gradient::linearInterpolation(Tuple point){
  Color distance = getColor2() - getColor1();
  float fraction = point.x - std::floor(point.x);
  return getColor1() + (distance * fraction);

}

Color Gradient::patternAt(Tuple point){
  return linearInterpolation(point);
}
