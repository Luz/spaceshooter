#ifndef PLAYERHANDLER_HPP
#define PLAYERHANDLER_HPP

#include <boost/array.hpp>

#include "Engine.hpp"
#include "Object.hpp"
#include "Asteroid.hpp"
#include "Spieler.hpp"
#include "SchussHandler.hpp"

#include "PlayerType.h"

class Engine;
class Spieler;
class Object;
class Rakete;
class SchussHandler;

class PlayerHandler
{
    public:
        PlayerHandler(Engine* mengine, SchussHandler* mSchussHandler);
        void newPlayer(PlayerType typ, std::complex<double> position = 0, double angle=0);
        void updateMovement();
        void keyDown(unsigned int key, unsigned int playernumber=0);
        void displayAllPlayers();
        virtual ~PlayerHandler();
    private:
        Engine* mEngine;
        SchussHandler* mSchussHandler;
        boost::array<Spieler*, 1> mPlayers;
};

#endif
