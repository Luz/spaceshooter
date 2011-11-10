#ifndef SCHUSS_HPP
#define SCHUSS_HPP

#include "Object.hpp"
#include "ObjectType.h"

class Schuss : public Object
{
    public:
        Schuss(Engine* mengine, double angle, std::complex<double> position, double speed, ObjectType type);
        unsigned int getAgeWhileAging();
        ~Schuss();
    private:
        ObjectType Type;
        unsigned int Weight;
        unsigned int Age; // Age in Frames
};

#endif
