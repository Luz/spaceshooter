#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Engine.hpp"
#include "Object.hpp"
//#include "ObjectHandler.hpp"
//#include "SchussHandler.hpp"

class Engine;
//class ObjectHandler;
//class SchussHandler;

class CollisionHandler
{
    public:
        CollisionHandler(Engine* mengine);
        bool checkCollision(std::complex<double> position1, unsigned int radius1,
                            std::complex<double> position2, unsigned int radius2);
        void executeCollision();
        void executeAllCollisions();
    private:
        Engine* mEngine;
        //ObjectHandler* mObjectHandler;
        //SchussHandler* mSchussHandler;
        //boost::array<Object*, MAXOBJECTS, MAXSCHUESSE> mAllObjects;
};

#endif
