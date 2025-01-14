
#include "Camera.h"
#include <array>
#include <cstddef>
#include <stdexcept>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "Constants.h"

TEST(CameraTest, PixelSize){

  

  struct test {
    Camera camera;
    float want;
  };
  
  const size_t numTests = 2;
    test tests[numTests] = {
    {
      Camera{200, 125, M_PI_2},
      0.01f
    },
    {
      Camera{125, 200, M_PI_2},
      0.01
    },
  

  };
     
  for(size_t i = 0; i < numTests; i++){
    test t = tests[i];

    EXPECT_EQ(t.camera.pixelSize, t.want);
  }
}

TEST(CameraTest, RayForPixel){

  enum transformName {
    rotation_y,
    translate
  };

  struct Transformation {
    transformName name;
    std::vector<float> args;
  };

  struct test {
    Camera camera;
    float px;
    float py;
    std::vector<Transformation> trs;
    Ray want;
  };
  
  const size_t numTests = 3;
    test tests[numTests] = {
    {
      Camera{201, 101, M_PI_2},
      100,
      50,
      {},
      Ray{std::array<float, 3>{0,0,0}, std::array<float, 3>{0,0,-1}}
    },
    {
      Camera{201, 101, M_PI_2},
      0,
      0,
      {},
      Ray{std::array<float, 3>{0,0,0}, std::array<float, 3>{0.66519f, 0.33259f, -0.66851f}}
    },
    {
      Camera{201, 101, M_PI_2},
      100,
      50,
      {{transformName::rotation_y, {M_PI_4_F}}, {transformName::translate, {0, -2, 5}}},
      Ray{std::array<float, 3>{0,2,-5}, std::array<float, 3>{sqrtf(2)/2, 0, -sqrtf(2)/2}}
    },

  };
     
    for(size_t i = 0; i < numTests; i++){
      test t = tests[i];

      Matrix transforms = Matrix::identityMatrix(4);

      for(size_t j = 0; j < t.trs.size(); ++j){

        switch(t.trs[j].name){
        case transformName::rotation_y :

          if(t.trs[j].args.size() != 1){
            throw std::invalid_argument("test "+ std::to_string(i) + " tranformation " + std::to_string(j) + " failed needed 1 argument got " + std::to_string(t.trs[j].args.size()));
          }
          transforms = transforms * Matrix::rotationAlongY(t.trs[j].args[0]);
          break;

        case transformName::translate :
          if(t.trs[j].args.size() != 3){
            throw std::invalid_argument("test "+ std::to_string(i) + " tranformation " + std::to_string(j) + " failed needed 3 argument got " + std::to_string(t.trs[j].args.size()));
          }
          transforms = transforms * Matrix::translate(t.trs[j].args[0], t.trs[j].args[1], t.trs[j].args[2]);
          break;

          default:
            throw std::invalid_argument("test failed invalid transform name" + std::to_string(t.trs[j].name) + "\n");
        }

      }

      t.camera.setTransform(transforms);

      EXPECT_EQ(t.camera.rayForPixel(t.px, t.py), t.want);
    }
}
