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
      Matrix{std::array<float, 9>{8,0,8, 8,5,3, 0,5,8}},
    },
    {
      {1, 0},
      Matrix{{0,9,3,0, 9,8,0,8 ,1,8,5,3, 0,0,5,8}},
      Matrix{std::array<float, 9>{9,3,0, 8,5,3, 0,5,8}},
    },
    {
      {2, 2},
      Matrix{std::array<float, 9>{0,9,3, 0,9,8, 0,8,1}},
      Matrix{std::array<float, 4>{0,9, 0,9}},
    },
    {
      {1, 0},
      Matrix{std::array<float, 9>{0,9,3, 0,9,8, 0,8,1}},
      Matrix{std::array<float, 4>{9,3, 8,1}},
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
      Matrix{std::array<float,9>{10,7,5, 2,3,4, 1.5f,2.5f,3.1f}},
      Matrix{std::array<float,9>{1.1f,1.2f,1.5f ,1,1,1 ,2.5f,1.5f,1.1f}},
      Matrix{std::array<float,9>{30.5f,26.5f,27.5f, 15.2f,11.4f,10.4f, 11.9f,8.95f,8.16f}},
    },
    {
      Matrix{std::array<float,9>{1,7,2.5f, 2.5f,1.5f,4, 5,2.5f,3.1f}},
      Matrix{std::array<float,9>{1.1f,1.2f,1.5f ,1,1,1 ,2.5f,1.5f,1.1f}},
      Matrix{std::array<float,9>{14.35f,11.95f,11.25f, 14.25f,10.5f,9.65f, 15.75f,13.15f,13.41f}},
    },
    {
      Matrix{std::array<float,4>{1,7 ,7,1}},
      Matrix{std::array<float,4>{5,1 ,1.25,1.5}},
      Matrix{std::array<float,4>{13.75, 11.5, 36.25, 8.5}},
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
      Matrix{std::array<float, 9>{1,2,3, 3,2,1, 1,2,3,}},
      Matrix{std::array<float, 9>{1,3,1, 2,2,2, 3,1,3}},
    },
    {
      Matrix{std::array<float, 4>{10,7, 5,4}},
      Matrix{std::array<float, 4>{10, 5, 7, 4}}
    },
    {
      Matrix{std::array<float, 4>{1.5,7, 2.5,1.5}},
      Matrix{std::array<float, 4>{1.5,2.5, 7,1.5}}
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
      Matrix{std::array<float, 4>{1,5, -3,2}},
      17.0f,
    },
    {
      Matrix{std::array<float, 4>{10,15, 25,20}},
      -175
    },
    {
      Matrix{std::array<float, 4>{1.25,1.5, 2.25,2.5}},
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
      Matrix{std::array<float, 9>{3,5,0, 2,-1,-7, 6,-1,5}},
      15.0f,
    },
    {
      {0, 0},
      Matrix{std::array<float, 9>{3,5,0, 2,-1,-7, 6,-1,5}},
      -12
    },
    {
      {2, 2},
      Matrix{std::array<float, 9>{46,75,20, 32,87,60, 48,11,51}},
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
      Matrix{std::array<float, 9>{1,2,3, 4,5,6, 7,8,9}},
      -3
    },
    {
      {2,1},
      Matrix{std::array<float, 9>{1,2,3, 4,5,6, 7,8,9}},
      6
    },
    {
      {0,0},
      Matrix{std::array<float, 9>{1.5,.25,.5, 10,20,12, 7,8,9}},
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
      Matrix{std::array<float, 9>{10,1,20, 2,0.10f,10, 0.20f,20,8}},
      -1206.4f
    },
    {
      Matrix{std::array<float, 9>{35,14,93, 62,85,84, 56,84,84}},
      37547.99999999999998f
    },
    {
      Matrix{std::array<float, 9>{50.62f,50.02f,95.73f, 89.2f,45.26f,59.97f, 39.79f,45.03f,62.87f}},
      58304.625f
    },
    {
      Matrix{std::array<float, 9>{1,2,6, -5,8,-4, 2,6,4}},
      -196 
    }
    
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_TRUE(FloatsEqual(test.m1.determinate(), test.want)); 
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
      Matrix{std::array<float, 16>{10, 1, 20, 2, 0.10f, 10, 0.20f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      -786.9f,
    },
    {
      {0, 1},
      Matrix{std::array<float, 16>{10, 1, 20, 2, 0.10f, 10, 0.20f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      -62.325f
    },
    {
      {0, 0},
      Matrix{std::array<float, 16>{8, 51, 10, 1, .5f, 7, .25f, 4, 10, 10, 1, 20, 2, 0.10f, 10, 0.20f}},
      -999.00f
    },
    {
      {1, 3},
      Matrix{std::array<float, 16>{8, 51, 10, 1, .5, 7, .25, 4, 10, 10, 1, 20, 2, 0.10f, 10, 0.20f}},
      -4388.8f
    },
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.minor(test.args[0], test.args[1]), test.want); 
  }
}

TEST(MatrixTest, Matrix4x4Cofactor){

  struct test {
    std::array<size_t, 2> args;
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 7;

  test tests[numTests] = {
    {
      {0, 0},
      Matrix{std::array<float, 16>{10, 1, 20, 2, 0.10f, 10, 0.20f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      -786.9f,
    },
    {
      {0, 1},
      Matrix{std::array<float, 16>{10, 1, 20, 2, 0.10f, 10, 0.20f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      62.325f
    },
    {
      {0, 0},
      Matrix{std::array<float, 16>{7, -7, 8, -8, 9, -9, 10, -10, 11, -11, 12, -12, 13, -13, 14, -14}},
      0
    },
    {
      {3, 3},
      Matrix{std::array<float, 16>{46, 75, 20, 32, 87, 60, 48, 11, 51, 82, 54, 55, 16, 12, 43, 64}},
      -119286
    },
    {
      {3, 3},
      Matrix{std::array<float, 16>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      149.6f
    },
    {
      {3, 1},
      Matrix{std::array<float, 16>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      -399.6f
    },
    {
      {0, 0},
      Matrix{std::array<float, 16>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8, 51, 10, 1, 0.5, 7, 0.25f, 4}},
      -786.9f
    },
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_FLOAT_EQ(test.m1.cofactor(test.args[0], test.args[1]), test.want); 
  }
}

TEST(MatrixTest, Matrix4x4Determinate){

  struct test {
    Matrix m1;
    float want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      Matrix{std::array<float, 16>{10, 1, 20, 2, 0.10f, 10, 0.20f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      -1573.4248f,
    },
    {
      Matrix{std::array<float, 16>{1, 1, 2, 2, 1, 1, 2, 2, 4, 5, 1, 1, 5, 7, 5, 4}},
      0
    },
    {
      Matrix{std::array<float, 16>{35, 14, 93, 62, 85, 84, 56, 84, 84, 62, 96, 92, 49, 46, 22, 28}},
      656256
    },
    {
      Matrix{std::array<float, 16>{-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9 }},
       -4071
    },
   
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_TRUE(FloatsEqual(test.m1.determinate(), test.want)) << " got: " << test.m1.determinate() << " want: " << test.want; 
  }
}

TEST(MatrixTest, Matrix4x4TupleMultiply){

  struct test {
    Matrix m1;
    Tuple t1;
    Tuple want;
  };
  
  const size_t numTests = 1;

  test tests[numTests] = {
    {
      Matrix{std::array<float, 16>{1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1}},
      Tuple{1, 2, 3, 1},
      Tuple{18, 24, 33, 1},
    },
   
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(tupleMultiply(test.m1, test.t1), test.want);
  }
}

// static identity

TEST(MatrixTest, CofactorMatrix){

  struct test {
    Matrix m1;
    Matrix want;
  };
  
  const size_t numTests = 1;

  test tests[numTests] = {
    {
      Matrix{std::array<float, 16>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      Matrix{std::array<float, 16>{-786.9f, 62.325f, 314.7f, -30.375f, 1987.5f, 79.5f, -1969, -264.5f, 996.9f, -53.925f, -994.7f, 31.925f, -9990, -399.6f, 10015, 149.6f}},
    },
   
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.cofactorMatrix(), test.want);
  }
}

TEST(MatrixTest, InverseMatrix){

  struct test {
    Matrix m1;
    Matrix want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {
      Matrix{std::array<float, 16>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8, 51, 10, 1, 0.5f, 7, 0.25f, 4}},
      Matrix{std::array<float, 16>{0.167781f, -0.423769f, -0.212556f, 2.130041f, -0.013288f, -0.016950f, 0.011497745226596731377f, 0.085201650302235583847f, -0.06709949787315700261f, 0.4198249485613159773f, 0.21208729118026460273f, -2.1353716911333567873f, 0.0064764767966226372851f, 0.056395987249602882696f, -0.0068069636784256031385f, -0.031897314527563672031f}},
    },
    {
      Matrix{std::array<float, 16>{35, 14, 93, 62, 85, 84, 56, 84, 84, 62, 96, 92, 49, 46, 22, 28}},
      Matrix{std::array<float, 16>{-0.0926712f, -0.0795421f, 0.139519f, -0.0145919f, 0.0955846f, 0.0711247f, -0.148509f, 0.0629328f, 0.058404f, 0.00908792f, -0.0630669f, 0.0506327f, -0.0407463f, 0.0152105f, 0.049374f, -0.0819223f}},
    },
    {
      Matrix{std::array<float, 9>{10, 1, 10, 1, 0.10f, 10, 0.2f, 20, 8}},
      Matrix{std::array<float, 9>{0.110777f, -0.106773f, -0.00500501f, 0.00333667f, -0.0433767f, 0.0500501f, -0.0111111f, 0.111111f, 0}},
    },
    {
      Matrix{std::array<float, 9>{35, 14, 93, 62, 85, 84, 56, 84, 84}},
      Matrix{std::array<float, 9>{0.00223714f, 0.176734f, -0.179211f, -0.0134228f, -0.0604027f, 0.0752637f, 0.0119314f, -0.0574198f, 0.0561148f}},
    },
   
    
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.m1.inverse(), test.want);
  }
}


 

