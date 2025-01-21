


#include "Cylinder.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(CylinderTest, CylinderIntersect){
  
  Cylinder tCylinder = Cylinder(1,2);
  Cylinder cylinder = Cylinder();

  struct test {
    Ray ray;
    Cylinder& cylinder;
    Intersections want;
  };

  
  const size_t numeTests = 7;

  test tests[numeTests] = {
    {
      Ray{point(1,0,0), vector(0, 1, 0)},
      cylinder,
      Intersections{
        {
        }
      }
    },
    {
      Ray{point(0,0,0), vector(0, 1, 0)},
      cylinder,
      Intersections{
        {
        }
      }
    },
    {
      Ray{point(1, 0, -5), vector(0, 0, 1)},
      cylinder,
      Intersections{
        {
          Intersection{5, &cylinder},
          Intersection{5, &cylinder},
        }
      }
    },
    {
      Ray{point(0, 0, -5), vector(0, 0, 1)},
      cylinder,
      Intersections{
        {
          Intersection{4, &cylinder},
          Intersection{6, &cylinder},
        }
      }
    },
    {
      Ray{point(0.5, 0, -5), vector(0.1, 1, 1)},
      cylinder,
      Intersections{
        {
          Intersection{6.80798, &cylinder},
          Intersection{7.08872, &cylinder},
        }
      }
    },
    {
      Ray{point(0, 1.5, 0), vector(0.1, 1, 0)},
      tCylinder,
      Intersections{
        {
        }
      }
    },
    {
      Ray{point(0, 1.5, -2), vector(0, 0, 1)},
      tCylinder,
      Intersections{
        {
          Intersection{1, &tCylinder},
          Intersection{3, &tCylinder}
        }
      }
    },
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];
  
    EXPECT_EQ(*(t.cylinder.intersect(t.ray).get()), t.want);
  }
    
}

/*
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
*/
