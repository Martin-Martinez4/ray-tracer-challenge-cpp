
#include "exercises.h"
#include "PPM.h"
#include <fstream>

int main(){


  std::ofstream out("Ex003-a.ppm");
  out << ppm(Ex003());
  out.close();

  
  return 0;
}
