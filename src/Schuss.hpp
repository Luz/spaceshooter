#ifndef SCHUSS_HPP
#define SCHUSS_HPP

#include "Object.hpp"
#include "SchussType.h"

class Schuss : public Object
{
    public:
        Schuss(std::string filename, float angle, std::complex<float> position, float speed, SchussType type=ROCKET);
        unsigned int getAgeWhileAging();
        ~Schuss();
    private:
        SchussType Type;
        unsigned int Weight;
        unsigned int Age; // Age in Frames
};

#endif
