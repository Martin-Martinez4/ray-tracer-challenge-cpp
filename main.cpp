#include "Floats.h"
#include "Tuple.h"
#include "iostream"
#include "Matrix.h"
#include <array>
#include "exercises.h"
#include "PPM.h"
#include <iostream>
#include <fstream>
#include <string>

int main(){

  std::ofstream out("Ex001.ppm");
  out << ppm(Ex001());
  out.close();
  
  return 0;
}
