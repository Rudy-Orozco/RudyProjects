#include "Projectile.h"

Projectile::Projectile(std::string name, double weight, double veloFps, double sizeCal, char shape) 
    : _name{name}, _weight{weight}, _veloFps{veloFps}, _sizeCal{sizeCal}, _shape{shape} {}

std::string Projectile::name() {
    return _name;
}

double Projectile::weight() {
    return _weight;
}

double Projectile::veloFps() {
    return _veloFps;
}

double Projectile::sizeCal() {
    return _sizeCal;
}

double Projectile::shape() {
    return _shape;
}