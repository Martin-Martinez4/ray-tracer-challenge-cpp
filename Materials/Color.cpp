#include "Color.h"
#include "Floats.h"
#include <ostream>

Color Color::add(Color const& color) const{
  return Color(r+color.r, g+color.g, b+color.b);
} 

Color Color::subtract(Color const& color) const{
  return Color(r+color.r, g+color.g, b+color.b);
}

// Color Color::scalarMultiply(float scalar) const{
//   return Color(r*scalar, g*scalar, b*scalar);
// }

Color Color::multiply(Color const& color) const {
  return Color(r*color.r, g*color.g, b*color.b);
}

bool Color::equal(Color const& color) const{
  return(
    floatsEqual(r, color.r) &&
    floatsEqual(g, color.g) &&
    floatsEqual(b, color.b) 
  );
} 

std::ostream& operator<<(std::ostream &os, const Color& color){ 
  return os << color.r << " " << color.g << " " << color.b;
}
