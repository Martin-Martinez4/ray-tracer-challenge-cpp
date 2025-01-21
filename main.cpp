 
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("output/Ex008.ppm");
  out << ppm(Ex008());
  out.close();

  
  return 0;
}
