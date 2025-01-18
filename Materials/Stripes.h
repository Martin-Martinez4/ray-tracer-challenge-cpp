

#ifndef MATERIALS_STRIPES_H_
#define MATERIALS_STRIPES_H_


#include "Pattern.h"

class Stripes: public Pattern {
public:
  Stripes();
  Stripes(Color color1);
  Stripes(Color color1, Color color2);

  Color patternAt(Tuple point) override;
  
};

#endif // !MATERIAL
