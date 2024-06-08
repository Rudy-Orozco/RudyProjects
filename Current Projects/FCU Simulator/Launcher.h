#ifndef __LAUNCHER_H
#define __LAUNCHER_H

#include <iostream>

class Launcher {
    private:
    std::string _name;
    double _barLength;
    char _type;
    char _launchMeth;

    public:
    Launcher(std::string name, double barLength, char type, char launchMeth);
    std::string name();
    double barLength();
    char type();
    char launchMeth();
};
#endif