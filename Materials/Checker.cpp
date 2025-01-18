
#include "Checker.h"
#include <cmath>

Checker::Checker():Pattern(){};
Checker::Checker(Color color1):Pattern(color1){};
Checker::Checker(Color color1, Color color2):Pattern(color1, color2){};

Color Checker::patternAt(Tuple point){
  float added = std::floor(point.x) + std::floor(point.y) + std::floor(point.z);

  if(std::remainderf(added, 2) == 0){
    return getColor1();
  }else{
    return getColor2();
  }
}
