
#ifndef MATERIALS_GRADIENT_H_
#define MATERIALS_GRADIENT_H_


#include "Pattern.h"

class Gradient: public Pattern {
public:
  Gradient();
  Gradient(Color color1);
  Gradient(Color color1, Color color2);

  Color patternAt(Tuple point) override;

private:
  Color linearInterpolation(Tuple point);
  
};

#endif // !MATERIAL
