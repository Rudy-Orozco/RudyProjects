#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include <iostream>

class Projectile {
    private:
    std::string _name;
    double _weight;
    double _veloFps;
    double _sizeCal;
    char _shape;

    public:
    Projectile(std::string name, double weight, double veloFps, double sizeCal, char shape);
    std::string name();
    double weight();
    double veloFps();
    double sizeCal();
    double shape();
};
#endif