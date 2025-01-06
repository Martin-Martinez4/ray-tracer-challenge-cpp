
#include "Canvas.h"
#include "PPM.h"
#include "Color.h"
#include <cstddef>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

TEST(ParseTest, PPMHeader){
  struct test {
    size_t width;
    size_t height;
    std::string want;
  };
  
  const size_t numeTests = 3;

  test tests[numeTests] = {
    {10, 5, "P3\n10 5\n255"},
    {100, 50, "P3\n100 50\n255"},
    {10, 50, "P3\n10 50\n255"}
  };

  for(size_t i = 0; i < numeTests; i++){
    test test = tests[i];

    std::stringstream ss;
    ppmHeader(ss, test.width, test.height);

    EXPECT_EQ(ss.str(), test.want);

  }
}

TEST(ParseTest, PPMBody){
  
  struct colorChange{
    size_t x;
    size_t y;
    Color color;
  };

  struct test {
    size_t width;
    size_t height;
    std::vector<colorChange> colorChanges;
    std::string want;
  };
  
  const size_t numeTests = 5;

  test tests[numeTests] = {
    {
      2, 
      3, 
      std::vector<colorChange>{}, 
      "0 0 0 0 0 0 \n0 0 0 0 0 0 \n0 0 0 0 0 0"
    },
    {
      5, 
      3,
      std::vector<colorChange>{},
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"
    },
    {
      5,
      3,
      std::vector<colorChange>{
        {0, 0, Color(0, 255, 0)}, 
        {1,3, Color(255, 0, 0)}
      },
      "0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 255 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"

    },
    {
      5,
      3,
      std::vector<colorChange>{
        {0, 0, Color(0, 255, 0)}, 
        {2,4, Color(255, 0, 0)}
      },
      "0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 255 0 0"

    },
    {
      5,
      3,
      std::vector<colorChange>{
        {0, 0, Color(0, -0.5f, 0.5f)}, 
      },
      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 0"

    },

  };

  for(size_t i = 0; i < numeTests; i++){
    test test = tests[i];

    Canvas c = Canvas(test.width, test.height);
    
    for(size_t i = 0; i < test.colorChanges.size(); i++){
      colorChange cc = test.colorChanges[i];

      c.setPixel(cc.x, cc.y, cc.color);
    }

    std::stringstream ss;
    ppmBody(ss, c);

    EXPECT_EQ(ss.str(), test.want);

  }
}
