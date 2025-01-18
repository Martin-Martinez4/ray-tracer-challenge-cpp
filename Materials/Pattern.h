
#ifndef MATERIALS_PATTERN_H_
#define MATERIALS_PATTERN_H_

#include "Color.h"
#include "Matrix.h"
#include "Tuple.h"

class Pattern {
public:
  Pattern();
  Pattern(Color color1);
  Pattern(Color color1, Color color2);
  
  void setTransform(Matrix transform);
  void setTransforms(std::vector<Matrix> transforms);
  Matrix getTransform();
  Matrix getInverseTransform();

  Color getColor1();
  Color getColor2();

  virtual Color patternAt(Tuple point);
  

private:
  Color color1;
  Color color2;
  Matrix transform;
  Matrix inverseTransform;

};

#endif // !MATERIAL



