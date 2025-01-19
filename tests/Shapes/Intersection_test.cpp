


#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "Tuple.h"
#include <array>
#include <cstddef>
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

TEST(IntersectionTest, n1Andn2PrepareComputations){
  
  // Glass
  // transparency = 1
  // refractiveIndex = 1.5
  
  Material mat1 = Material();
  mat1.transparency = 1;
  mat1.refractiveIndex = 1.5f;
  
  Material mat2 = Material();
  mat2.transparency = 1;
  mat2.refractiveIndex = 2.f;

  Material mat3 = Material();
  mat3.transparency = 1;
  mat3.refractiveIndex = 2.5f;

  Sphere s1 = Sphere(mat1);
  s1.setTransform(Matrix::scale(2, 2, 2));

  Sphere s2 = Sphere(mat2);
  s2.setTransform(Matrix::translate(0, 0, -0.25f));

  Sphere s3 = Sphere(mat3);
  s3.setTransform(Matrix::translate(0, 0, 0.25f));

  Ray ray = Ray{point(0,0,-4), vector(0, 0, 1)};

  struct test {
    Intersection intersection;
    float n1;
    float n2;
  };

  std::shared_ptr<Intersections> inters (new Intersections{
    {{2, &s1},
		{2.75,  &s2},
		{3.25,  &s3},
		{4.75,  &s2},
		{5.25,  &s3},
		{6, &s1},
	}});

  test tests[6] = {
    {
      {2, &s1}, 
      1.0f, 
      1.5f
    },
    {
      {2.75, &s2},
      1.5f,
      2.f
    },
    {
      { 3.25, &s3},
        2, 
        2.5
    },
    {
      {4.75, &s2},
      2.5, 
      2.5
    },
    {
      {5.25, &s3},
      2.5, 
      1.5,
    },
    {
      {6, &s1},
      1.5,
      1.0
    },
	};

  for(size_t i = 0; i < 6; ++i){
    test t = tests[i];

    Computations c = Computations{ray, t.intersection, inters};

    EXPECT_EQ(t.n1, c.n1);
    EXPECT_EQ(t.n2, c.n2);
  }

}
