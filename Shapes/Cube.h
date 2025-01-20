
#ifndef SHAPES_CUBE_H_
#define SHAPES_CUBE_H_

#include "Shape.h"
#include "Tuple.h"
#include <memory>

struct Intersections;

class Cube: public Shape{
public:
  Cube(): Shape(){};
  Cube(Material mat): Shape(mat){};

  std::array<float, 2> checkAxis(float origin, float direction);
  
  std::shared_ptr<Intersections> localIntersect(Ray ray) override;

  Tuple normalAt(Tuple const& worldPoint, Intersection const* intersection) override;
  Tuple normalAt(Tuple const& worldPoint);
  
private:

};


#endif // !SHAPES_Cube_H_
