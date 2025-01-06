

#include "Ray.h"
#include "Sphere.h"
#include <gtest/gtest.h>

TEST(RayTest, IntersectEquals){
  

  struct test {
    Intersections inter1;
    Sphere* sphere;
    Intersections inter2;
  };

  Sphere theSphere = Sphere();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 5;

  test tests[numeTests] = {
    {
      Intersections{{{4, &theSphere}, {6, &theSphere}}},
      (&theSphere), 
      Intersections{{{4, &theSphere}, {6, &theSphere}}}
    },
    {
      Intersections{{{5, &theSphere}}},
      (&theSphere), 
      Intersections{{{5, &theSphere}}}
    },
    {
      Intersections{},
      (&theSphere), 
      Intersections{}
    },
    {
      Intersections{{{-1, &theSphere}, {1, &theSphere}}}, 
      (&theSphere), 
      Intersections{{{-1, &theSphere}, {1, &theSphere}}}
    },
     {
      Intersections{{{-6, &theSphere}, {-4, &theSphere}}},
      (&theSphere), 
      Intersections{{{-6, &theSphere}, {-4, &theSphere}}}
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test test = tests[i];


    EXPECT_TRUE((test.inter1 == test.inter2));
  }
    
}

TEST(RayTest, RaySphereIntersect){
  

  struct test {
    Ray ray;
    Sphere* sphere;
    Intersections want;
  };

  Sphere theSphere = Sphere();
  
  // const size_t numeTests = 5;
  const size_t numeTests = 5;

  test tests[numeTests] = {
    {
      Ray(point(0,0,-5), point(0,0,1)), 
      (&theSphere), 
      Intersections{{{4, &theSphere}, {6, &theSphere}}}
    },
    {
      Ray(point(0,1,-5), point(0,0,1)), 
      (&theSphere), 
      Intersections{{{5, &theSphere}}}
    },
    {
      Ray(point(0,2,-5), point(0,0,1)), 
      (&theSphere), 
      Intersections{}
    },
    {
      Ray(point(0,0,0), point(0,0,1)), 
      (&theSphere), 
      Intersections{{{-1, &theSphere}, {1, &theSphere}}}
    },
     {
      Ray(point(0,0,5), point(0,0,1)), 
      (&theSphere), 
      Intersections{{{-6, &theSphere}, {-4, &theSphere}}}
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test test = tests[i];

    std::shared_ptr<Intersections> got = raySphereIntersect(test.ray, test.sphere);

    EXPECT_EQ(test.want, (*got))<< "test: "<< i << "\n";
  }
    
}
