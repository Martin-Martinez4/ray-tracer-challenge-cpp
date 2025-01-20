#ifndef MATH_FLOATS_H_
#define MATH_FLOATS_H_

#include <cmath>
const float EPSILON = 0.00009f;

const float INFINIT_F = 10e6;

bool floatsEqual(float first, float second);
float clampToInt(float value, int min, int max);


#endif // !MATH_FLOATS_H_
