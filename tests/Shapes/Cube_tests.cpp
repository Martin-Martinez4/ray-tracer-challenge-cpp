

#include "Cube.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(CubeTest, CubeIntersect){
  
  Cube cube = Cube();

  struct test {
    Ray ray;
    Intersections want;
  };

  Sphere theSphere = Sphere();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 6;

  test tests[numeTests] = {
    {
      Ray{point(5, 0.5, 0), vector(-1, 0, 0)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
    {
      Ray{point(-5, 0.5, 0), vector(1, 0, 0)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
    {
      Ray{point(0.5, 5, 0), vector(0, -1, 0)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
    {
      Ray{point(0.5, -5, 0), vector(0, 1, 0)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
    {
      Ray{point(0.5, 0, 5), vector(0, 0, -1)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
    {
      Ray{point(0.5, 0, -5), vector(0, 0, 1)},
      Intersections{
        {
          Intersection{4, &cube},
          Intersection{6, &cube},
        }
      }
    },
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];
    
    auto inters = cube.localIntersect(t.ray);
  
    EXPECT_EQ(*(cube.localIntersect(t.ray).get()), t.want) << "\ntest: " << i << "\n";
  }
    
}

TEST(CubeTest, CubeNormal){
  
  Cube cube = Cube();

  struct test {
    Tuple point;
    Tuple want;
  };

  // const size_t numeTests = 5;
  const size_t numeTests = 6;

  test tests[numeTests] = {
    {
      point(1, 0.5, -0.8),
      vector(1,0,0)
    },
    {
      point(-1, -0.2, 0.9),
      vector(-1,0,0)
    },
    {
      point(-0.4, 1, -0.1),
      vector(0,1,0)
    },
    {
      point(-0.6, 0.3, 1),
      vector(0,0,1)
    },
    {
      point(1, 1, 1),
      vector(1,0,0)
    },
    {
      point(-1, -1, -1),
      vector(-1,0,0)
    },
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];
  
    EXPECT_EQ(cube.normalAt(t.point), t.want) << "\ntest: " << i << "\n";
  }
    
}
