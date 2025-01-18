

#include "Checker.h"
#include "Gradient.h"
#include "Ring.h"
#include "Stripes.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(PatternTest, StripesPatternAt){
  

  struct test {
    Tuple point;
    Color want;
  };

  Color black = Color(0,0,0);
  Color white = Color(1,1,1);
  Stripes stripes = Stripes(black, white);

  
  const size_t numeTests = 4;

  test tests[numeTests] = {
    {
      point(0, 0, 0),
      white
    },
    {
      point(0.9f, 0, 0),
      white
    },
    {
      point(-1, 0, 0),
      black
    },
    {
      point(-0.1f, 0, 0),
      black
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];


    EXPECT_EQ(stripes.patternAt(t.point), t.want);
  }
    
}

TEST(PatternTest, GradientPatternAt){
  

  struct test {
    Tuple point;
    Color want;
  };

  Color black = Color(0,0,0);
  Color white = Color(1,1,1);
  Gradient gradient = Gradient(white, black);

  
  const size_t numeTests = 3;

  test tests[numeTests] = {
    {
      point(0, 0, 0),
      white
    },
    {
      point(0.25f, 0, 0),
      Color(0.75, 0.75, 0.75)
    },
    {
      point(0.5f, 0, 0),
      Color(0.5, 0.5, 0.5)
    },
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];


    EXPECT_EQ(gradient.patternAt(t.point), t.want);
  }
    
}

TEST(PatternTest, CheckerPatternAt){
  

  struct test {
    Tuple point;
    Color want;
  };

  Color black = Color(0,0,0);
  Color white = Color(1,1,1);
  Checker checker = Checker(white, black);

  
  const size_t numeTests = 5;

  test tests[numeTests] = {
    {
      point(0, 0, 0),
      white
    },
    {
      point(0.99, 0, 0),
      white
    },
    {
      point(1.01, 0, 0),
      black
    },
    {
      point(0, 0.99f, 0),
      white
    },
    {
      point(0, 1.01, 0),
      black
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];


    EXPECT_EQ(checker.patternAt(t.point), t.want);
  }
    
}

TEST(PatternTest, RingPatternAt){
  

  struct test {
    Tuple point;
    Color want;
  };

  Color black = Color(0,0,0);
  Color white = Color(1,1,1);
  Ring ring = Ring(white, black);

  
  const size_t numeTests = 4;

  test tests[numeTests] = {
    {
      point(0, 0, 0),
      white
    },
    {
      point(1, 0, 0),
      black
    },
    {
      point(0, 0, 1),
      black
    },
    {
      point(0.708f, 0, 0.708f),
      black
    }
  };

  for(size_t i = 0; i < numeTests; ++i){
    test t = tests[i];


    EXPECT_EQ(ring.patternAt(t.point), t.want);
  }
    
}
