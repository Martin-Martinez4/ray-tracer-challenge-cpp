
#ifndef MATERIALS_RING_H_
#define MATERIALS_Ring_H_


#include "Pattern.h"

class Ring: public Pattern {
public:
  Ring();
  Ring(Color color1);
  Ring(Color color1, Color color2);

  Color patternAt(Tuple point) override;
  
};

#endif // !MATERIAL
