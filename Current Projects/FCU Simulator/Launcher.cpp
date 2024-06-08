#include "Launcher.h"

Launcher::Launcher(std::string name, double barLength, char type, char launchMeth)
    : _name{name}, _barLength{barLength}, _type{type}, _launchMeth{launchMeth} {}

std::string Launcher::name() {
    return _name;
}

double Launcher::barLength() {
    return _barLength;
}

char Launcher::type() {
    return _type;
}

char Launcher::launchMeth() {
    return _launchMeth;
}