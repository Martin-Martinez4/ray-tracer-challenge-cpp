#include "Floats.h"
#include "Tuple.h"
#include "iostream"
#include "Matrix.h"

int main(){

  Matrix2x2 mat = Matrix2x2{ (std::array<std::array<float, 2>, 2>){ {{1, 1}, {2, 2}} } };
  Matrix2x2& t = mat.test();
  std::cout << t.size << "\n";
  std::cout << t.get(0, 0) << "\n";
  std::cout << mat.get(1,1) << "\n";
  
  return 0;
}
