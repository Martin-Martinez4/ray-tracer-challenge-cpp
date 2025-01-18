#include "Stripes.h"
#include "Pattern.h"
#include <cmath>
#include <iostream>

Stripes::Stripes():Pattern(){};
Stripes::Stripes(Color color1):Pattern(color1){};
Stripes::Stripes(Color color1, Color color2):Pattern(color1, color2){};

Color Stripes::patternAt(Tuple point){
  if(int(floorf(point.x))%2 == 0){
    return getColor2();
  }else{
    return getColor1();
  }
}


