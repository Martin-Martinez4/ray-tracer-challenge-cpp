#include "tuple.h"

std::ostream& operator<<(std::ostream &os, const Tuple& tuple){
    return os << "Tuple: { x: " << tuple.x << ", y: " << tuple.y << ", z: " << tuple.z << " }";
}




