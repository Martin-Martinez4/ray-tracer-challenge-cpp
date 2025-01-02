#include "Floats.h"
#include "Tuple.h"
#include "iostream"

int main(){

  Tuple t1 = Tuple(1, 2, 3);
  Tuple t2 = Tuple(1, 2, 3);

  Tuple t3 = t1.addTuple(t2);

  std::cout << t3 << "\n";

  std::cout << ((0 - -0) < EPSILON) << "\n";
  
  return 0;
}
