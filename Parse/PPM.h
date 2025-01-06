#ifndef PARSE_PPPM_H_
#define PARSE_PPPM_H_

#include "Canvas.h"
#include <string>

std::string ppm(Canvas Canvas);
std::stringstream& ppmHeader(std::stringstream& ss, size_t width, size_t height);
std::stringstream& ppmBody(std::stringstream& ss, Canvas canvas);

#endif // !PARSE_PPPM_H_
