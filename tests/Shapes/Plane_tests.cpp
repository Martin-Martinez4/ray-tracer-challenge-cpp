
#include "Intersection.h"
#include "Plane.h"
#include "Tuple.h"
#include "Ray.h"
#include <cmath>
#include <gtest/gtest.h>
#include <memory>

TEST(PlaneTest, PlaneNormalAt){
  

  struct test {
    Tuple point;
    Tuple want;
  };

  Plane thePlane = Plane();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 3;

  test tests[numeTests] = {
    {
      point(0, 0, 0),
      vector(0, 1, 0)
    },
    {
      point(10, 1, -100),
      vector(0, 1, 0)
    },
    {
      point(-5, 0, 150),
      vector(0, 1, 0)
    },

  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];


    EXPECT_EQ(thePlane.normalAt(t.point), t.want);
  }
    
}

TEST(PlaneTest, PlaneIntersect){
  

  struct test {
    Ray ray;
    Intersections want;
  };

  Plane thePlane = Plane();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 3;

  test tests[numeTests] = {
    {
      Ray{point(0, 10, 0), vector(0, 0, 1)}, 
      Intersections()
    },
    {
      Ray{point(0, 1, 0), vector(0, -1, 0)},
      Intersections(std::vector<Intersection>{Intersection{1, &thePlane}})
    },
    {
      Ray{point(0, -1, 0), vector(0, 1, 0)},
      Intersections(std::vector<Intersection>{Intersection{1, &thePlane}})
    },

  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];

    auto inters = thePlane.localIntersect(t.ray);


    EXPECT_EQ((*inters), t.want);
  }
    
}




