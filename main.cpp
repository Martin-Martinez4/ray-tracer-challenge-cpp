 
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("output/Ex006.ppm");
  out << ppm(Ex006());
  out.close();

  
  return 0;
}
