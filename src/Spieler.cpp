#include <string>
#include <iostream>

#include "Spieler.hpp"
#include "Schuss.hpp"

Spieler::Spieler(Engine* mengine, double x, double y)
: Object(mengine, SPIELER, x, y), SchussCoolDown(0)
{
}

void Spieler::schiessen()
{
	  new Schuss(mEngine,Angle,Position,5.0);

    SchussCoolDown = 3;
}



void Spieler::keyDown(unsigned int key)
{
    switch (key)
    {
        case 1: incSpeed(0.2); break;
        case 2: incSpeed(-0.2); break;
        case 3: rotate(10); break;
        case 4: rotate(-10); break;
        case 5: schiessen(); break;
        //case 6: delete mPlayer; mPlayer = 0; break;
        default: break;
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
