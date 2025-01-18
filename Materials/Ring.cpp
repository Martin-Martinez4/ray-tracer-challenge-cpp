
#include "Ring.h"
#include <cmath>

Ring::Ring():Pattern(){};
Ring::Ring(Color color1):Pattern(color1){};
Ring::Ring(Color color1, Color color2):Pattern(color1, color2){};

Color Ring::patternAt(Tuple point){
  float f = std::floor(sqrtf((point.x * point.x) + point.z * point.z));

  if(int(f)%2 == 0){
    return getColor1();
  }else{
    return getColor2();
  }
}
  
