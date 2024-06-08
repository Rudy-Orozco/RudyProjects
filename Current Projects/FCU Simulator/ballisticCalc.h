#ifndef __BALLISTICCALC_H
#define __BALLISTICCALC_H

#include <iostream>
#include <vector>

const float PI = 3.14159265358979323846;
const float GRAV = 9.81;
const float TIME_STEP = 0.1;

struct Point {
    float x, y;
};

class ballisticCalc {
    private:
    double maxDist;

    public:
    ballisticCalc(double maxDist);
    std::vector<Point> compute(double v0, double angle);
    double setMaxDist(double in);
};
#endif