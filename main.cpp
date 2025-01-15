
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("Ex003-s.ppm");
  out << ppm(Ex003());
  out.close();

  
  return 0;
}
