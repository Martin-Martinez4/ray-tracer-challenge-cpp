

#include "Canvas.h"
#include <gtest/gtest.h>

TEST(CanvasTest, CanvasGetSetPixel){
  
  
  struct colorChange{
    size_t x;
    size_t y;
    Color color;
  };

  struct test {
    size_t width;
    size_t height;
    std::vector<colorChange> colorChanges;
  };
  
  const size_t numeTests = 3;

  test tests[numeTests] = {
    {
      2, 
      3, 
      std::vector<colorChange>{}
    },
    {
      5, 
      3,
      std::vector<colorChange>{},
    },
    {
      5,
      3,
      std::vector<colorChange>{
        {0, 0, Color(0, 255, 0)}, 
        {3,1, Color(255, 0, 0)}
      },

    },

  };

  for(size_t i = 0; i < numeTests; i++){
    test test = tests[i];

    Canvas c = Canvas(test.width, test.height);
    
    for(size_t i = 0; i < test.colorChanges.size(); i++){
      colorChange cc = test.colorChanges[i];

      c.setPixel(cc.x, cc.y, cc.color);
    }
     
    for(size_t i = 0; i < test.colorChanges.size(); i++){
      colorChange cc = test.colorChanges[i];

      EXPECT_EQ(cc.color, c.getPixel(cc.x, cc.y));
    }
    
  }
}
