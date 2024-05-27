#include <gtest/gtest.h>
#include <iostream>
#include "GDALDLL.h"
TEST(MYTEST0, A)
{
    int    inpesg = 4326, outepsg = 2000;
    double x = 118, y = 31, z  = 0;
    double input[3] = {x, y, z};

    std::cout << "input coorinate: " << input[0] << ", " << input[1] << ", " << input[2]
              << std::endl;
    CoordinateTransformation(input, inpesg, outepsg);
    std::cout << "output coorinate: " << input[0] << ", " << input[1] << ", " << input[2]
              << std::endl;
}