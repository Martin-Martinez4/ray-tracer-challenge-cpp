
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("output/Ex004-s.ppm");
  out << ppm(Ex004());
  out.close();

  
  return 0;
}
