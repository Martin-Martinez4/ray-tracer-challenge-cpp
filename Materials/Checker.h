
#ifndef MATERIALS_CHECKER_H_
#define MATERIALS_CHECKER_H_


#include "Pattern.h"

class Checker: public Pattern {
public:
  Checker();
  Checker(Color color1);
  Checker(Color color1, Color color2);

  Color patternAt(Tuple point) override;
  
};

#endif // !MATERIAL
