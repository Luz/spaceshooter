#include <math.h>
//#include <iostream>

#include "Schuss.hpp"

Schuss::Schuss(std::string filename, double angle, std::complex<double> position, double speed, SchussType type)
:Object(filename, SCHUSS, position.real(), position.imag(),
speed*cos((angle+90)/180*M_PI),speed*sin((angle-90)/180*M_PI)), Type(type), Weight(1), Age(0)
{
    //std::cout << "Schuss::Schuss();" << std::endl;
    Angle = angle;
}

unsigned int Schuss::getAgeWhileAging()
{//each schuss-type has its own lifetime, but not its own age! altering is implemented in SchussHandler
    Age += 1;
    return Age;
}

Schuss::~Schuss()
{
    //std::cout << "Schuss::~Schuss();" << std::endl;
}
