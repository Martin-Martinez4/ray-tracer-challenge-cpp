#include <gtest/gtest.h>
#include "Floats.h"

TEST(FloatsTest, FloatsEqual){

  struct test {
    float f1;
    float f2;
    bool want;
  };
  
  const size_t numTests = 6;

  test tests[numTests] = {
    {1.0f, 1.0f, true},
    {2.5f, 2.0f, false},
    {1.00002, 1, true},
    {100.0f, 1.0f, false},
    {1.000009, 2, false},
    {1.000009, 1, true}
  };
  
  for(size_t i = 0; i < numTests; i++){
    if(tests[i].want){
      EXPECT_TRUE(FloatsEqual(tests[i].f1, tests[i].f2)); 

    }else{
      EXPECT_FALSE(FloatsEqual(tests[i].f1, tests[i].f2));
    }
  }
}


