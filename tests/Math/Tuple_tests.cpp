#include "Tuple.h"
#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>

TEST(TupleTest, EqualTuples){
  struct test {
    Tuple t1;
    Tuple t2;
    bool want;
  };
  
  const size_t numeTests = 5;

  test tests[numeTests] = {
    {Tuple(0,0,0), Tuple(0,0,0), true},
    {Tuple(1,2,3), Tuple(1,2,3), true},
    {Tuple(3,2,1), Tuple(1,2,3), false},
    {Tuple(2,1,3), Tuple(1,2,3), false},
    {vector(0, 0, 0), point(0, 0, 0), false},
  };

  for(size_t i = 0; i < numeTests; i++){
    test test = tests[i];

    if(test.want){
      EXPECT_TRUE(test.t1.equal(test.t2));
    }else{
      EXPECT_FALSE(test.t1.equal(test.t2));
    }
  }
}

TEST(TupleTest, AddTuples){

  struct test {
    Tuple t1;
    Tuple t2;
    Tuple want;
  };
  
  const size_t numTests = 3;

  test tests[numTests] = {
    {Tuple{1,1,1}, Tuple{1,1,1}, Tuple{2,2,2}},
    {Tuple{1.5, 1.25, 1.0}, Tuple{1.25, 1.5, 1.0}, Tuple{2.75, 2.75, 2.0}},
    {Tuple{-1, 5, -10}, Tuple{1, -2, 5}, Tuple{0, 3, -5}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];

    EXPECT_EQ(test.t1 + test.t2, test.want); 
  }
}


TEST(TupleTest, SubtractTuples){

  struct test {
    Tuple t1;
    Tuple t2;
    Tuple want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {Tuple{1,1,1}, Tuple{1,1,1}, Tuple{0,0,0}},
    {Tuple{1.5, 1.25, 1.0}, Tuple{1.25, 1.5, 1.0}, Tuple{.25, -.25, 0.0}},
    {Tuple{-1, 5, -10}, Tuple{1, -2, 5}, Tuple{-2, 7, -15}},
    {Tuple{-1, 5, -10, 4}, Tuple{1, -2, 5}, Tuple{-2, 7, -15, 4}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];

    EXPECT_EQ(test.t1 - test.t2, test.want); 
  }
}

TEST(TupleTest, NegateTuple){

  struct test {
    Tuple t1;
    Tuple want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {Tuple{1,1,1}, Tuple{-1,-1,-1}},
    {Tuple{1.5, 1.25, 1.0}, Tuple{-1.5, -1.25, -1.0}},
    {Tuple{-1, -5, -10}, Tuple{1, 5, 10}},
    {Tuple{-1, 5, -10, 4}, Tuple{1, -5, 10, -4}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1.negate(), test.want); 
  }
}

TEST(TupleTest, MultiplyScalarTuple){

  struct test {
    Tuple t1;
    float s;
    Tuple want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {Tuple{1,1,1}, -1, Tuple{-1,-1,-1}},
    {Tuple{1.5, 1.25, 1.0}, 2, Tuple{3.0f, 2.5f, 2.0f}},
    {Tuple{-1, -5, -10}, -.5, Tuple{.5, 2.5, 5}},
    {Tuple{-1, 5, -10, 4}, 3, Tuple{-3, 15, -30, 12}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1 * test.s, test.want); 
  }
}

TEST(TupleTest, DivideScalarTuple){

  struct test {
    Tuple t1;
    float s;
    Tuple want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {Tuple{1,1,1}, -1, Tuple{-1,-1,-1}},
    {Tuple{1.5, 1.25, 1.0}, 1.5, Tuple{1.0f, .8333333f, .666667f}},
    {Tuple{-1, -5, -10}, -.5, Tuple{2, 10, 20}},
    {Tuple{-3, 6, -12, 9}, 3, Tuple{-1, 2, -4, 3}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1/test.s, test.want); 
  }
}

TEST(TupleTest, MagnitudeTuple){

  struct test {
    Tuple t1;
    float want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {Tuple{1,0,0}, 1},
    {Tuple{1, 2, 3}, sqrtf(14)},
    {Tuple{-1, -2, -3, 1}, sqrtf(15)},
    {Tuple{-3, 6, -12, 2}, sqrtf(193)}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1.magnitude(), test.want); 
  }
}

TEST(TupleTest, NormalizeTuple){

  struct test {
    Tuple t1;
    Tuple want;
  };
  
  const size_t numTests = 4;

  test tests[numTests] = {
    {vector(1, 0, 0), Tuple{1,0,0}},
    {vector(0, 1, 0), Tuple{0,1,0}},
    {vector(1, 2, 3), Tuple{(1.0f/sqrtf(14)), (2.0f/sqrtf(14)), (3.0f/sqrtf(14))}},
    {vector(-1, -2, -3), Tuple{(-1.0f/sqrtf(14)), (-2.0f/sqrtf(14)), (-3.0f/sqrtf(14))}}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(normalize(test.t1), test.want); 
  }
}

TEST(TupleTest, DotProductTuple){

  struct test {
    Tuple t1;
    Tuple t2;
    float want;
  };
  
  const size_t numTests = 2;

  test tests[numTests] = {
    {vector(1, 2, 3), vector(2, 3, 4), 20},
    {vector(1, 2, 3), vector(3, 4, 5), 26}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1.dot(test.t2), test.want); 
  }
}

TEST(TupleTest, CrossProductTuple){

  struct test {
    Tuple t1;
    Tuple t2;
    Tuple want;
  };
  
  const size_t numTests = 2;

  test tests[numTests] = {
    {vector(1, 2, 3), vector(2, 3, 4), vector(-1, 2, -1)},
    {vector(2, 3, 4), vector(1, 2, 3), vector(1, -2, 1)}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.t1.cross(test.t2), test.want); 
  }
}

TEST(TupleTest, ReflectTuple){

  struct test {
    Tuple vec;
    Tuple normal;
    Tuple want;
  };
  
  const size_t numTests = 2;

  test tests[numTests] = {
    {vector(1, -1, 0), vector(0, 1, 0), vector(1, 1, 0)},
    {vector(0, -1, 0), vector(sqrtf(2)/2, sqrtf(2)/2, 0), vector(1, 0, 0)}
  };
  
  for(size_t i = 0; i < numTests; i++){
    test test = tests[i];
    EXPECT_EQ(test.vec.reflectBy(test.normal), test.want); 
  }
}
