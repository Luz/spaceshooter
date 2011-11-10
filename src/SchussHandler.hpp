#ifndef SCHUSSHANDLER_HPP
#define SCHUSSHANDLER_HPP

#include <boost/array.hpp>

#include "Engine.hpp"
#include "Schuss.hpp"

class Engine;
class Schuss;

class SchussHandler
{
    public:
        SchussHandler(Engine* mengine);
        void newShoot(std::complex<double> position, double angle, ObjectType type);
        void updateMovement();
        void displayAllShoots();
        unsigned int getSchussCoolDown();
        virtual ~SchussHandler();
    private:
        Engine* mEngine;
        boost::array<Schuss*, 30> mSchuesse;
        ObjectType lastFiredShootType;
};

#endif
