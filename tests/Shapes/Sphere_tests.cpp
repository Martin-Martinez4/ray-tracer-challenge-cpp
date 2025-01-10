
#include "Sphere.h"
#include "Tuple.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(SphereTest, SphereNormalAt){
  

  struct test {
    Tuple point;
    Tuple want;
  };

  Sphere theSphere = Sphere();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 4;

  test tests[numeTests] = {
    {
      point(1, 0, 0),
      vector(1, 0, 0)
    },
    {
      point(0, 1, 0),
      vector(0, 1, 0)
    },
    {
      point(0, 0, 1),
      vector(0, 0, 1)
    },
    {
      point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3),
      vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test test = tests[i];


    EXPECT_EQ(test.want, theSphere.normalAt(test.point));
  }
    
}
