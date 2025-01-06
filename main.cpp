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

  Matrix mat = Matrix{std::array<float, 16>{{1,1,1,1, 2,2,2,2, 3,3,3,3 ,4,4,4,4}}};
  Matrix scalared = (mat.scalarMultiply(2));

  std::cout << "old :" << "\n";
  std::cout << mat << "\n";

  std::cout << "scalared :" << "\n";
  std::cout << tupleMultiply(mat, Tuple{1,2,3,1}) << "\n";

  std::ofstream out("Ex001.ppm");
  out << ppm(Ex001());
  out.close();


  
  
  return 0;
}
