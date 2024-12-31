
#ifndef MATH_TUPLE_H_
#define MATH_TUPLE_H_

#include "ostream"

struct Tuple {

    Tuple(float x, float y, float z):x(x), y(y), z(z){}

    float x;
    float y;
    float z;

    Tuple operator+(Tuple const& tuple) {
        return Tuple{x + tuple.x , y + tuple.y, z + tuple.z};
    }

    friend std::ostream& operator<<(std::ostream &os, const Tuple& p);
};

#endif


