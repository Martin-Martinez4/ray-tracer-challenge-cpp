

#include "Canvas.h"
#include "Floats.h"
#include <cstddef>
    
std::stringstream& ppmHeader(std::stringstream& ss,  size_t width, size_t height){
  ss << "P3\n" << width << " " << height << "\n" << "255";
  return ss;
}

  std::stringstream& ppmBody(std::stringstream& ss, Canvas canvas){
    
    size_t height = canvas.height;
    size_t width = canvas.width;
  
    for(size_t h = 0; h < height; h++){

      if(h > 0 && h != height){
        ss << "\n";
      }

      for(size_t w = 0; w < width; w++){

        Color currentColor = canvas.getPixel(h, w);

        if(w%11 == 0 && w != 0){
          ss << "\n";
        }
        
        // PPM only uses ints, values have to be clamped
        ss << clampToInt(currentColor.r, 0, 255) << " " << clampToInt(currentColor.g, 0, 255) << " " << clampToInt(currentColor.b, 0, 255);

        if(w != width-1 || h != height-1){
          ss << " ";
        }

      }
    }

    return ss;
  }

std::string ppm(Canvas canvas) {
    std::stringstream ss;
    ppmHeader(ss, canvas.width, canvas.height);
    ss << "\n";
    ppmBody(ss, canvas);
    ss << "\n";

    return ss.str();
  }

