
#ifndef MATERIALS_COLOR_H_
#define MATERIALS_COLOR_H_

#include "Floats.h"
#include <ostream>

struct Color {
  
  Color():r{0}, g{0}, b{0}{};
  Color(float r, float g, float b):r{r}, g{g}, b{b}{};

  float r;
  float g;
  float b;

  Color add(Color const& color) const; 
  Color subtract(Color const& color) const;
  Color scalarMultiply(float scalar) const;
  // hadamard product
  Color multiply(Color const& color) const;
  bool equal(Color const& color) const;

  bool operator==(Color const& otherColor) const{

    return (
      floatsEqual(r, otherColor.r) &&
      floatsEqual(g, otherColor.g) &&
      floatsEqual(b, otherColor.b)
    );
  }

  friend std::ostream& operator<<(std::ostream &os, const Color& color);

};

#endif // !MATERIALS_COLOR_H_


