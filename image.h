#pragma once
using namespace std;
#include <Imagine/Graphics.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES
using namespace Imagine; // Imagine C++ library

struct Point {
    /*
    Structure of a 2D point
    */
    int x;
    int y;
};

double mean(byte* P, int width, int height);
double standard_dev(byte* P, int width, int height);
byte* color_to_bw(char* name, int W, int H);



