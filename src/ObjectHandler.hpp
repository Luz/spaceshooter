#ifndef OBJECTHANDLER_HPP
#define OBJECTHANDLER_HPP

#include <boost/array.hpp>

#include "Engine.hpp"
#include "Object.hpp"
#include "Asteroid.hpp"
#include "Spieler.hpp"

class Engine;
class Object;
class Rakete;

class ObjectHandler
{
    public:
        ObjectHandler(Engine* mengine);
        void newObject(ObjectType typ, std::complex<float> position = 0, float angle=0);
        void updateMovement();
        void displayAllObjects();
        virtual ~ObjectHandler();
    private:
        bool checkCollision(Object &obj1, Object &obj2);
        Engine* mEngine;
        boost::array<Object*, 30> mObjects;
};

#endif
