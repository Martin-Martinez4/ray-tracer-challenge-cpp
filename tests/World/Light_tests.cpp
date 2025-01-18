
#include "Tuple.h"
#include "Light.h"
#include "Color.h"
#include "Sphere.h"
#include <cmath>
#include <array>
#include <gtest/gtest.h>

TEST(LightTest, LightingFunction){
  
  
 
  struct test {
    Material m;
    Tuple eyeVec;
    Tuple normalVec;
    Light light;
    Color want;

  };

  Material mat = Material();
  Tuple p = point(0,0,0);
  
  const size_t numTests = 5;

  test tests[numTests] = {
    {
      mat,
      vector(0,0,-1),
      vector(0,0,-1),
      Light(std::array<float,3>{0,0,-10}, std::array<float,3>{1,1,1}),
      Color(1.9, 1.9, 1.9)
    },
    {
      mat,
      vector(0, sqrtf(2)/2, -sqrtf(2)/2),
      vector(0,0,-1),
      Light(std::array<float, 3>{0, 0, -10}, std::array<float, 3>{1,1,1}),
      Color(1.0, 1.0, 1.0),
    },
    {
      mat,
      vector(0,0,-1),
      vector(0,0,-1),
      Light(std::array<float, 3>{0,10,-10}, std::array<float,3>{1,1,1}),
      Color(0.7364, 0.7364, 0.7364),
    },
    {
      mat,
      vector(0, -sqrtf(2)/2, -sqrtf(2)/2),
      vector(0,0,-1),
      Light(std::array<float, 3>{0, 10, -10}, std::array<float, 3>{1,1,1}),
      Color(1.6364, 1.6364, 1.6364),
    },
    {
      mat,
      vector(0, 0, -1),
      vector(0,0,-1),
      Light(std::array<float, 3>{0, 0, 10}, std::array<float, 3>{1,1,1}),
      Color(0.1f, 0.1f, 0.1f),
    },
    
  };

  Sphere s = Sphere();

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];
    EXPECT_EQ(lighting(t.m, &s, t.light, p, t.eyeVec, t.normalVec, false), t.want);
  }
}
