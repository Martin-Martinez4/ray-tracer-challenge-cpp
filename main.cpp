 
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("output/Ex005-a.ppm");
  out << ppm(Ex005());
  out.close();

  
  return 0;
}
