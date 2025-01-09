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
#include <iostream>

int main(){


  std::ofstream out("Ex002.ppm");
  out << ppm(Ex002());
  out.close();

  
  return 0;
}
