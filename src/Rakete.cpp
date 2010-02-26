#include <string>

#include "Rakete.hpp"

Rakete::Rakete(Engine* mengine, float x, float y) //, SchussHandler* mschusshandler, float x, float y)
: Object(mengine, RAKETE, x, y)//, mSchussHandler(mschusshandler)
{
}
/*
void Rakete::schiessen()
{
    if(mSchussHandler != NULL)
        mSchussHandler->newShoot(getPosition(), getAngle(), 1);
}*/

Rakete::~Rakete()
{
}
