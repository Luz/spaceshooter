#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Object.hpp"
#include "Engine.hpp"

class Engine;

class Asteroid: public Object
{
    public:
        Asteroid(Engine* mengine);
        bool getCriticalPosition(); //this overwrites the method of the class Object
        virtual ~Asteroid();
    private:
        unsigned int weight;
};

#endif
