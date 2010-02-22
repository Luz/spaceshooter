#include <string>

#include "Rakete.hpp"

Rakete::Rakete(std::string filename, float x, float y) //, SchussHandler* mschusshandler, float x, float y)
: Object(filename,RAKETE, x, y)//, mSchussHandler(mschusshandler)
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
