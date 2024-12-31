#include "./Math/tuple.h"
#include "iostream"

int main(){

    Tuple t1 = Tuple(1, 2, 3);
    Tuple t2 = Tuple(1, 2, 3);


    std::cout <<( t1 + t2); 

    return 0;
}