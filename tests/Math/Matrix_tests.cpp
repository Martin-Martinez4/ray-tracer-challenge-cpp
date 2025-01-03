#include "Matrix.h"
#include "Floats.h"
#include <array>
#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>

TEST(MatrixTest, MatrixCreate)
{

    struct check
    {
        size_t x;
        size_t y;
        float value;
    };

    struct test
    {
        std::array<float, 16> elements;
        std::array<check, 5> checks;
    };

    test test = {
        std::array<float, 16>{{1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5}},
        std::array<check, 5>{{{1, 0, 5.5}, {1, 2, 7.5}, {2, 2, 11}, {3, 0, 13.5}, {3, 2, 15.5}}},
    };

    Matrix got = Matrix(test.elements);

    for(size_t i = 0; i < 5; ++i) {
        check check = test.checks[i];
          EXPECT_EQ(got.get(check.x, check.y), check.value);
        
    }
}

TEST(MatrixTest, MatrixSubmatrix){

  struct test {
    std::array<size_t, 2> args;
    Matrix m1;
    Matrix want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      {0 ,0},
      Matrix{{0,9,3,0, 9,8,0,8, 1,8,5,3, 0,0,5,8}},
      Matrix{(std::array<float, 9>){8,0,8, 8,5,3, 0,5,8}},
    },
    {
      {1, 0},
      Matrix{{0,9,3,0, 9,8,0,8 ,1,8,5,3, 0,0,5,8}},
      Matrix{(std::array<float, 9>){9,3,0, 8,5,3, 0,5,8}},
    },
    {
      {2, 2},
      Matrix{(std::array<float, 9>){0,9,3, 0,9,8, 0,8,1}},
      Matrix{(std::array<float, 4>){0,9, 0,9}},
    },
    {
      {1, 0},
      Matrix{(std::array<float, 9>){0,9,3, 0,9,8, 0,8,1}},
      Matrix{(std::array<float, 4>){9,3, 8,1}},
    }
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.subMatrix(test.args[0], test.args[1]), test.want); 
  }
}


TEST(MatrixTest, MatrixMatrixMultiply){

  struct test {
    Matrix m1;
    Matrix m2;
    Matrix want;
  };
  
  const size_t numTests = 5;

  test tests[numTests] = {
    {
      Matrix{{1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2}},
      Matrix{{-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8}},
      Matrix{{20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42}}
    },
    {
      Matrix{{1,2,3,4 ,3,2,1,4 ,1,2,3,4 ,7,7,7,7}},
      Matrix{{4,5,6,7 ,6,5,4,7 ,4,6,5,7 ,4,4,4,4}},
      Matrix{{44,49,45,58 ,44,47,47,58 ,44,49,45,58 ,126,140,133,175}},
    },
    {
      Matrix{(std::array<float,9>){10,7,5, 2,3,4, 1.5,2.5,3.1}},
      Matrix{(std::array<float,9>){1.1,1.2,1.5 ,1,1,1 ,2.5,1.5,1.1}},
      Matrix{(std::array<float,9>){30.5,26.5,27.5, 15.2,11.4,10.4, 11.9,8.95,8.16}},
    },
    {
      Matrix{(std::array<float,9>){1,7,2.5, 2.5,1.5,4, 5,2.5,3.1}},
      Matrix{(std::array<float,9>){1.1,1.2,1.5 ,1,1,1 ,2.5,1.5,1.1}},
      Matrix{(std::array<float,9>){14.35,11.95,11.25, 14.25,10.5,9.65, 15.75,13.15,13.41}},
    },
    {
      Matrix{(std::array<float,4>){1,7 ,7,1}},
      Matrix{(std::array<float,4>){5,1 ,1.25,1.5}},
      Matrix{(std::array<float,4>){13.75, 11.5, 36.25, 8.5}},
    }
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.matrixMultiply(test.m2), test.want); 
  }
}

TEST(MatrixTest, MatrixTranspose){

  struct test {
    Matrix m1;
    Matrix want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      Matrix{{0,9,3,0, 9,8,0,8, 1,8,5,3, 0,0,5,8}},
      Matrix{{0,9,1,0, 9,8,8,0, 3,0,5,5, 0,8,3,8}},
    },
    {
      Matrix{(std::array<float, 9>){1,2,3, 3,2,1, 1,2,3,}},
      Matrix{(std::array<float, 9>){1,3,1, 2,2,2, 3,1,3}},
    },
    {
      Matrix{(std::array<float, 4>){10,7, 5,4}},
      Matrix{(std::array<float, 4>){10, 5, 7, 4}}
    },
    {
      Matrix{(std::array<float, 4>){1.5,7, 2.5,1.5}},
      Matrix{(std::array<float, 4>){1.5,2.5, 7,1.5}}
    }
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.transpose(), test.want); 
  }
}

TEST(MatrixTest, Matrix2x2Determinate){

  struct test {
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 3;

  test tests[numTests] = {
    {
      Matrix{(std::array<float, 4>){1,5, -3,2}},
      17.0f,
    },
    {
      Matrix{(std::array<float, 4>){10,15, 25,20}},
      -175
    },
    {
      Matrix{(std::array<float, 4>){1.25,1.5, 2.25,2.5}},
      -0.25
    },
    
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.determinate(), test.want); 
  }
}

TEST(MatrixTest, Matrix3x3Minor){

  struct test {
    std::array<size_t, 2> args;
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 3;

  test tests[numTests] = {
    {
      {1, 1},
      Matrix{(std::array<float, 9>){3,5,0, 2,-1,-7, 6,-1,5}},
      15.0f,
    },
    {
      {0, 0},
      Matrix{(std::array<float, 9>){3,5,0, 2,-1,-7, 6,-1,5}},
      -12
    },
    {
      {2, 2},
      Matrix{(std::array<float, 9>){46,75,20, 32,87,60, 48,11,51}},
      1602.0f
    },
    
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.minor(test.args[0], test.args[1]), test.want); 
  }
}

TEST(MatrixTest, Matrix3x3Cofactor){

  struct test {
    std::array<size_t, 2> args;
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 3;

  test tests[numTests] = {
    {
      {0,0},
      Matrix{(std::array<float, 9>){1,2,3, 4,5,6, 7,8,9}},
      -3
    },
    {
      {2,1},
      Matrix{(std::array<float, 9>){1,2,3, 4,5,6, 7,8,9}},
      6
    },
    {
      {0,0},
      Matrix{(std::array<float, 9>){1.5,.25,.5, 10,20,12, 7,8,9}},
      84
    },
    
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.cofactor(test.args[0], test.args[1]), test.want); 
  }
}

TEST(MatrixTest, Matrix3x3Determinate){

  struct test {
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      Matrix{(std::array<float, 9>){10,1,20, 2,0.10,10, 0.20,20,8}},
      -1206.4
    },
    {
      Matrix{(std::array<float, 9>){35,14,93, 62,85,84, 56,84,84}},
      37547.99999999999998
    },
    {
      Matrix{(std::array<float, 9>){50.62,50.02,95.73, 89.2,45.26,59.97, 39.79,45.03,62.87}},
      58304.625 
    },
    {
      Matrix{(std::array<float, 9>){1,2,6, -5,8,-4, 2,6,4}},
      -196 
    }
    
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_FLOAT_EQ(test.m1.determinate(), test.want); 
  }
}

TEST(MatrixTest, Matrix4x4Minor){

  struct test {
    std::array<size_t, 2> args;
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      {0, 0},
      Matrix{(std::array<float, 16>){10, 1, 20, 2, 0.10, 10, 0.20, 20, 8, 51, 10, 1, 0.5, 7, 0.25, 4}},
      -786.9,
    },
    {
      {0, 1},
      Matrix{(std::array<float, 16>){10, 1, 20, 2, 0.10, 10, 0.20, 20, 8, 51, 10, 1, 0.5, 7, 0.25, 4}},
      -62.325
    },
    {
      {0, 0},
      Matrix{(std::array<float, 16>){8, 51, 10, 1, .5, 7, .25, 4, 10, 10, 1, 20, 2, 0.10, 10, 0.20}},
      -999.00
    },
    {
      {1, 3},
      Matrix{(std::array<float, 16>){8, 51, 10, 1, .5, 7, .25, 4, 10, 10, 1, 20, 2, 0.10, 10, 0.20}},
      -4388.8
    },
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.minor(test.args[0], test.args[1]), test.want); 
  }
}
