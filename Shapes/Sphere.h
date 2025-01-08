#ifndef SHAPES_SPHERE_H_
#define SHAPES_SPHERE_H_

#include "Shape.h"
#include "Tuple.h"

class Sphere: public Shape{
public:
  Sphere(): Shape(){};

  Tuple normalAt(Tuple worldPoint) override;
  
private:

};


#endif // !SHAPES_SPHERE_H_
