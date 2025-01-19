

#include "Camera.h"
#include "Canvas.h"
#include "Intersection.h"
#include "Plane.h"
#include "Ray.h"
#include "Shape.h"
#include "Sphere.h"
#include "Tuple.h"
#include "Light.h"
#include "Color.h"
#include "World.h"
#include <cmath>
#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include "Constants.h"


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

  Sphere s = Sphere();

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];
    EXPECT_EQ(lighting(t.m, &s, t.light, p, t.eyeVec, t.normalVec, false), t.want);
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


TEST(TestWorld, Render){ 
  
  Camera c = Camera{11, 11, M_PI_2};
  c.setTransform(Matrix::viewTransform(point(0,0,-5), point(0,0,0), vector(0, 1, 0)));
  Canvas canvas = render(c, createDefaultWorld());

  EXPECT_EQ(canvas.getPixel(5, 5), Color(0.38066f, 0.47583f, 0.2855f));
  
  
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
      // Color(0.90498f, 0.90498f, 0.90498f)
      Color(0.904956f, 0.904956f, 0.904956f)
    },
    
  };

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];

    Computations c = Computations(t.ray, t.intersection);
  
    EXPECT_EQ(shadeHit(t.world, c, 0), t.want);
  }
  
}

TEST(TestWorld, IsShadowed){ 
 
  struct test {
    Tuple point;
    bool want;
  };

  World theWorld = createDefaultWorld();

  const size_t numTests = 4;

  test tests[numTests] = {
    {
     point(0,10,10),
     false
    },
    {  
      point(-20, 20, -20),
      false
    },
    {  
      point(10, -10, 10),
      true
    },
    {  
      point(-22, 2, -2),
      false
    },
    
  };

  for(size_t i = 0; i < numTests; ++i){
    test t = tests[i];

  
    EXPECT_EQ(isShadowed(theWorld, t.point), t.want);
  }
  
}


TEST(TestWorld, ShadeHitWithShadow){ 
 
  Ray ray = Ray{point(0,0,5), vector(0,0,1)};
  Light light = Light(std::array<float, 3>{0,0,-10}, std::array<float, 3>{1, 1, 1});

  std::shared_ptr<Sphere> s2 (new Sphere());
  s2->setTransform(Matrix::translate(0,0,10));

  std::shared_ptr<Sphere>s1 (new Sphere());

  // std::vector<std::shared_ptr<Shape>> shapes, Light light
  World theWorld = World({s1, s2}, light);

  Intersection i = Intersection{4, s2.get()};

  Computations c = Computations{ray, i};
  
  EXPECT_EQ(shadeHit(theWorld, c, 0), Color(0.1, 0.1, 0.1));
  
}

TEST(TestWorld, Reflection){ 

  // ReflectionV
  Plane plane1 = Plane();
  Ray ray1 = Ray{point(0, 1, -1), vector(0, -sqrtf(2)/2, sqrtf(2)/2)};
  Intersection inter1 = Intersection{sqrtf(2), &plane1};

  Computations comps1 = Computations{ray1, inter1};
  EXPECT_EQ(comps1.reflectV, vector(0, sqrtf(2)/2, sqrtf(2)/2)) << "Test 1 refelctionV failed: \n";

  // non-reflective Material
  World w2 = createDefaultWorld();
  Material mat2 = Material();
  mat2.ambient = 1;
  w2.shapes[1]->setMaterial(mat2);
  Intersection inter2 = Intersection{sqrtf(2), w2.shapes[1].get()};
  Ray ray2 = Ray{point(0,1,-1), vector(0, -sqrtf(2)/2, sqrtf(2)/2)};
  Computations comps2 = Computations{ray2, inter2};

  EXPECT_EQ(reflectedColor(w2, comps2, 1), Color(0,0,0)) << "Test 2 non-reflective failed: \n";

  // reflective material
  World w3 = createDefaultWorld();
  Material mat3 = Material();
  mat3.reflective = 0.5;
  Plane plane3 = Plane(mat3);
  plane3.setTransform(Matrix::translate(0, -1, 0));
  Ray ray3 = Ray{point(0,0,-3), vector(0, -sqrtf(2)/2, sqrtf(2)/2)};
  Intersection inter3 = Intersection{sqrtf(2), &plane3};
  Computations comps3 = Computations(ray3, inter3);
  Color reflected3 = reflectedColor(w3, comps3, 1);

  EXPECT_EQ(reflected3, Color(0.19032f, 0.2379f, 0.14277f)) << "Test 3 refelctive material failed: \n";

  // reflective Material, zero reflections
  World w5 = createDefaultWorld();
  Material mat5 = Material();
  mat5.reflective = 0.5;
  Plane plane5 = Plane(mat5);
  plane5.setTransform(Matrix::translate(0, -1, 0));
  Intersection inter5 = Intersection{sqrtf(2), &plane5};
  Ray ray5 = Ray{point(0,0,-3), vector(0, sqrtf(2)/2, sqrtf(2)/2)};
  Computations comps5 = Computations{ray5, inter5};

  EXPECT_EQ(reflectedColor(w5, comps5, 0), Color(0,0,0));


  // ------------ Reflective ShadeHit ------------
  World w6 = createDefaultWorld();
  
  Material planeMat = Material();
  planeMat.reflective = 0.5;

  std::shared_ptr<Shape> plane6 (new Plane(planeMat));
  plane6->setTransform(Matrix::translate(0, -1, 0));

  Ray ray6 = Ray{point(0,0,-3), vector(0, -sqrtf(2)/2, sqrtf(2)/2)};

  Intersection inter6 = Intersection{sqrtf(2), plane6.get()};

  Computations comps6 = Computations{ray6, inter6};

  EXPECT_EQ(shadeHit(w6, comps6, 1), Color(0.87677, 0.92436, 0.82918));

  // ------------ Two Reflective Shapes ------------

}

TEST(TestWorld, Schlick){ 
  
  Ray ray = Ray{point(0,0,sqrtf(2)/2), vector(0, 1, 0)};
  
  Material m = Material();
  m.transparency = 1;
  m.refractiveIndex = 1.5;
  std::shared_ptr<Shape> g (new Sphere(m));

  Intersection inter = Intersection{-sqrtf(2)/2, g.get()};
  Intersection inter1 = Intersection{sqrtf(2)/2, g.get()};
  std::shared_ptr<Intersections> inters (new Intersections{{inter, inter1}});

  Computations comps = Computations{ray, inter1, inters};

  EXPECT_EQ(schlick(comps), 1.0f);

  Ray ray1 = Ray{point(0,0,0), vector(0, 1, 0)};
  std::shared_ptr<Intersections> inters1 (new Intersections{{
    Intersection{-1, g.get()},
    Intersection{1, g.get()}
  }});

  Computations comps1 = Computations(ray1, inters1->get(1), inters1);
  EXPECT_FLOAT_EQ(schlick(comps1), 0.04) << "wanted: 0.04 \nschlick perpendicular failed";

  Ray ray2 = Ray{point(0,0.99,-2), vector(0, 0, 1)};
  std::shared_ptr<Intersections> inters2 (new Intersections{{
    Intersection{1.8589, g.get()},
  }});

  Computations comps2 = Computations(ray2, inters2->get(0), inters2);
  EXPECT_FLOAT_EQ(schlick(comps2), 0.4887307f) << "wanted: 0.48873 \nschlick small angle failed";
  
}


TEST(TestWorld, Refraction){ 
  // opaque color
  World w0 = createDefaultWorld();
  Ray ray0 = Ray{point(0,0,-5), vector(0,0,1)};
  std::shared_ptr<Intersections> inters0 (new Intersections{
    {
      Intersection{4, w0.shapes[0].get()},
      Intersection{6, w0.shapes[0].get()}
    }
  });

  Computations comps0 = Computations{ray0, inters0->get(0), inters0};

  EXPECT_EQ(refractedColor(w0, comps0, 5), Color(0,0,0));

  // ------------ reflectionsLeft 0 ------------ 
  World w1 = createDefaultWorld();
  Ray ray1 = Ray{point(0,0,-5), vector(0,0,1)};
  
  Material mat1 = Material();
  mat1.transparency = 1.0f;
  mat1.refractiveIndex = 1.5f;
 
  w1.shapes[0]->setMaterial(mat1);

  std::shared_ptr<Intersections> inters1 (new Intersections{
    {
      Intersection{4, w1.shapes[0].get()},
      Intersection{6, w1.shapes[0].get()}
    }
  });

  Computations comps1 = Computations{ray1, inters1->get(0), inters1};

  EXPECT_EQ(refractedColor(w1, comps1, 0), Color(0,0,0));
   
  //  ------------ refracted ray ------------ 
  World w3 = createDefaultWorld();
  Ray ray3 = Ray{point(0,0,0.1), vector(0,1,0)};
  
  Material mat3_0 = Material(Color(1,1,1), std::shared_ptr<Pattern>(new Pattern()));
  mat3_0.ambient = 1.0f;

  Material mat3_1 = Material();
  mat3_1.transparency = 1.0f;
  mat3_1.refractiveIndex = 1.5f;
 
  w3.shapes[0]->setMaterial(mat3_0);
  w3.shapes[1]->setMaterial(mat3_1);


  std::shared_ptr<Intersections> inters3 (new Intersections{
    {
      Intersection{-0.9899, w3.shapes[0].get()},
      Intersection{-0.4899, w3.shapes[1].get()},
      Intersection{0.4899, w3.shapes[1].get()},
      Intersection{0.9899, w3.shapes[0].get()}
    }
  });

  Computations comps3 = Computations{ray3, inters3->get(2), inters3};

  EXPECT_EQ(refractedColor(w3, comps3, 5), Color(0,0.99888,0.04725));
   
  //  ------------ ShadeHit refracted ray ------------ 
  World w4 = createDefaultWorld();
  Ray ray4 = Ray{point(0,0,-3), vector(0,-sqrtf(2)/2,sqrtf(2)/2)};

  Material floorMat = Material();
  floorMat.transparency = 0.5;
  floorMat.refractiveIndex = 1.5;

  std::shared_ptr<Shape> floor (new Plane(floorMat));
  floor->setTransform(Matrix::translate(0, -1, 0));

  Material ballMat = Material(Color(1,0,0));
  ballMat.ambient = 0.5;
  std::shared_ptr<Shape> ball (new Sphere(ballMat));
  ball->setTransform(Matrix::translate(0, -3.5, -0.5));

  w4.addShape(floor);
  w4.addShape(ball);

  std::shared_ptr<Intersections> inters4 (new Intersections{
    {
      Intersection{sqrtf(2), floor.get()},
    }
  });

  Computations comps4 = Computations{ray4, inters4->get(0), inters4};

  EXPECT_EQ(shadeHit(w4, comps4, 5), Color(0.93642, 0.68642, 0.68642));

}
TEST(TestWorld, SchlickReflectionAndRefraction){ 
  
  Ray ray = Ray{point(0,0,-3), vector(0, -sqrtf(2)/2, sqrtf(2)/2)};
  World w = createDefaultWorld();

  Material floorMat = Material();
  floorMat.reflective = 0.5f;
  floorMat.transparency = 0.5f;
  floorMat.refractiveIndex = 1.5f;

  std::shared_ptr<Shape> floor (new Plane(floorMat));
  floor->setTransform(Matrix::translate(0, -1, 0));

  Material sMat = Material(Color(1,0,0));
  sMat.ambient = 0.5f;
  
  std::shared_ptr<Shape> s (new Sphere(sMat));
  s->setTransform(Matrix::translate(0, -3.5, -0.5));

  w.addShape(floor);
  w.addShape(s);

  Intersection inter = Intersection{sqrtf(2), floor.get()};
  std::shared_ptr<Intersections> inters (new Intersections{{inter}});

  Computations comps = Computations{ray, inter, inters};

  EXPECT_EQ(shadeHit(w, comps, 5), Color(0.93391f, 0.69643f, 0.69243f));
  
}
