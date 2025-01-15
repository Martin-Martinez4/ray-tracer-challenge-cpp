


#include "Intersection.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tuple.h"
#include <array>
#include <gtest/gtest.h>
#include <iostream>

TEST(IntersectionTest, PrepareComputations){
  

  struct test {
    Ray ray;
    Sphere* sphere;
    Intersection intersection;
    Computations want;
  };

  Sphere theSphere = Sphere();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 2;

  test tests[numeTests] = {
    {
      Ray(std::array<float, 3>{0,0,-5}, std::array<float, 3>{0,0,1}),
      (&theSphere), 
      Intersection{4, &theSphere},
      Computations(4, &theSphere, point(0,0,-1), vector(0, 0, -1), vector(0,0,-1), false)
    },
    {
      Ray(std::array<float, 3>{0,0,0}, std::array<float, 3>{0,0,1}),
      (&theSphere), 
      Intersection{1, &theSphere},
      Computations(1, &theSphere, point(0,0,1), vector(0, 0, -1), vector(0,0,-1), true)
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test test = tests[i];
    
    Computations c = Computations(test.ray, test.intersection);

    EXPECT_EQ(Computations(test.ray, test.intersection), test.want);
  }
    
}


TEST(IntersectionTest, OverPointWithinRange){
  
  Ray ray = Ray{point(0,0,-5), vector(0,0,1)};
  Sphere theSphere = Sphere();
  theSphere.setTransform(Matrix::translate(0,0,1));
  Intersection i = Intersection{5, &theSphere};

  Computations comps = Computations{ray, i};

  EXPECT_TRUE((comps.overPoint.z < -EPSILON/2) && (comps.point.z > comps.overPoint.z));
    
}
