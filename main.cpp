 
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("output/Ex007.ppm");
  out << ppm(Ex007());
  out.close();

  
  return 0;
}
