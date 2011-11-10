#include <string>
#include <iostream>

#include "Spieler.hpp"

Spieler::Spieler(Engine* mengine, PlayerHandler* mplayerhandler, SchussHandler* mschusshandler, double x, double y)
: Object(mengine, PLAYER, x, y), mPlayerHandler(mplayerhandler), mSchussHandler(mschusshandler), SchussCoolDown(0)
{
}

void Spieler::schiessen(ObjectType type)
{
    if(mSchussHandler == NULL)
        std::cout << "Error: no mSchussHandler" << std::endl;
    else
    {
        if(SchussCoolDown == 0)
        {
            mSchussHandler->newShoot(Position, Angle, type);
            SchussCoolDown = mSchussHandler->getSchussCoolDown();// TODO: test this for ROCKET and GREEN
        }
    }
}

void Spieler::decSchussCoolDown()
{
    if(SchussCoolDown != 0)
        SchussCoolDown--;
}

Spieler::~Spieler()
{
}
