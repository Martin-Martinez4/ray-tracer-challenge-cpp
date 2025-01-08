
#include "Material.h"
#include "Tuple.h"
#include "Light.h"
#include "Color.h"
#include <array>
#include <gtest/gtest.h>

TEST(LightTest, LightingFunction){
  
  
 
  struct test {
    Material m;
    Tuple eyeVec;
    Tuple normalVec;
    Tuple point;
    Light light;
    Color want;

  };

  Material mat = Material();
  Tuple p = point(0,0,0);
  
  const size_t numTests = 3;

  test tests[numTests] = {
    {
      mat,
      vector(0,0,-1),
      vector(0,0,-1),
      p,
      Light(std::array<float, 3>{0,0,-10}, std::array<float, 3>{1,1,1}),
      Color(1.9, 1.9, 1.9),
    },
    {
      mat,
      vector(0,sqrtf(2)/2,-sqrtf(2)/2),
      vector(0,0,-1),
      p,
      Light(std::array<float, 3>{0, 10, -10}, std::array<float, 3>{1,1,1}),
      Color(0.7364, 0.7364, 0.7364),
    },
    {
      mat,
      vector(0, -sqrtf(2)/2, -sqrtf(2)/2),
      vector(0,0,-1),
      p,
      Light(std::array<float, 3>{0, 10, -10}, std::array<float, 3>{1,1,1}),
      Color(1.6364, 1.6364, 1.6364),
    },
    
  };

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];
    EXPECT_EQ(lighting(t.m, t.light, t.point, t.eyeVec, t.normalVec, false), t.want);
  }


  
  
}
