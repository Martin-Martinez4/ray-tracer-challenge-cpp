#include "Floats.h"
#include <cmath>
#include <iostream>

bool floatsEqual(float first, float second){
  return fabs(first - second) < EPSILON;
}

float clampToInt(float value, int min, int max){
  int intVal = int(value);


  if(intVal >= max){
    return max;
  }else if(intVal <= min){
    return min;
  }else{
    return intVal;
  }
}

