

#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include "Tuple.h"
#include "Light.h"
#include "Color.h"
#include "World.h"
#include <cmath>
#include <array>
#include <gtest/gtest.h>
#include <iostream>

TEST(TestWorld, IntersectWorld){
  
  
 
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

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];
    EXPECT_EQ(lighting(t.m, t.light, p, t.eyeVec, t.normalVec, false), t.want);
  }
}

TEST(TestWorld, ColorAt){
   
  struct test {
    Ray ray;
    World world;
    Color want;
  };

  World theWorld = createDefaultWorld();
  
  const size_t numTests = 2;

  test tests[numTests] = {
    {
      Ray{std::array<float, 3>{0,0,-5}, std::array<float, 3>{0,1,0}},
      theWorld,
      Color(0.0f, 0.0f, 0.0f)
    },
    {  
      Ray{std::array<float, 3>{0,0,-5}, std::array<float, 3>{0,0,1}},
      theWorld,
      Color(0.38066f, 0.47583f, 0.2855f)
    },
    
  };

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];
  
    EXPECT_EQ(colorAt(t.ray, t.world, 1), t.want);
  }
  
}


TEST(TestWorld, ShadeHit){
  
  
 
  struct test {
    Ray ray;
    std::shared_ptr<Shape> shape;
    World world;
    Intersection intersection;
    Color want;
  };

  World theWorld = createDefaultWorld();
  
  World theOtherWorld = createDefaultWorld();
  Light otherLight = Light(std::array<float,3>{0,0.25f,0}, std::array<float,3>{1,1,1});
  theOtherWorld.light = otherLight;

  const size_t numTests = 2;

  test tests[numTests] = {
    {
      Ray{std::array<float, 3>{0,0,-5}, std::array<float, 3>{0,0,1}},
      theWorld.shapes[0],
      theWorld,
      Intersection{4, theWorld.shapes[0].get()},
      Color(0.38066f, 0.47583f, 0.2855f)
    },
    {  
      Ray{std::array<float, 3>{0,0,0}, std::array<float, 3>{0,0,1}},
      theOtherWorld.shapes[1],
      theOtherWorld,
      Intersection{0.5f, theOtherWorld.shapes[1].get()},
      Color(0.90498f, 0.90498f, 0.90498f)
    },
    
  };

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];

    Computations c = Computations(t.ray, t.intersection);
  
    EXPECT_EQ(shadeHit(t.world, c), t.want);
  }
  
}
