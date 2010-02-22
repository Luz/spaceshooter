#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Object.hpp"

class Asteroid: public Object
{
    public:
        Asteroid(std::string filename);
        bool getCriticalPosition(); //this overwrites the method of the class Object
        virtual ~Asteroid();
    private:
        unsigned int weight;
};

#endif
