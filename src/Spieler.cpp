#include <string>
#include <iostream>

#include "Spieler.hpp"

Spieler::Spieler(std::string filename, PlayerHandler* mplayerhandler, SchussHandler* mschusshandler, double x, double y)
: Object(filename,SPIELER, x, y), mPlayerHandler(mplayerhandler), mSchussHandler(mschusshandler), SchussCoolDown(0)
{
}

void Spieler::schiessen()
{
    if(mSchussHandler == NULL)
        std::cout << "Error: no mSchussHandler" << std::endl;
    else
    {
        if(SchussCoolDown == 0)
        {
            mSchussHandler->newShoot(Position, Angle, 1);
            SchussCoolDown = mSchussHandler->getSchussCoolDown();
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
