#include "Matrix.h"
#include "Floats.h"
#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>

TEST(MatrixTest, MatrixCreate)
{

    struct check
    {
        size_t x;
        size_t y;
        float value;
    };

    struct test
    {
        std::array<float, 16> elements;
        std::array<check, 5> checks;
    };

    test test = {
        std::array<float, 16>{{1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5}},
        std::array<check, 5>{{{1, 0, 5.5}, {1, 2, 7.5}, {2, 2, 11}, {3, 0, 13.5}, {3, 2, 15.5}}},
    };

    Matrix got = Matrix(test.elements);

    for(size_t i = 0; i < 5; ++i) {
        check check = test.checks[i];
        std::cout << check.value << "\n";
        
    }
}
