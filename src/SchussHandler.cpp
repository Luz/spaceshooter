#include <iostream>

#include "SchussHandler.hpp"

SchussHandler::SchussHandler(Engine* mengine)
:mEngine(mengine)
{
    for (unsigned int i=0; i!=mSchuesse.max_size(); ++i) mSchuesse[i] = NULL;
}

void SchussHandler::newShoot(std::complex<double> position, double angle, int schusstyp)
{
    //alle schüsse sollten hier abgefeuert werden
    for (unsigned int i=0; i!=mSchuesse.max_size(); ++i)
    {
        if(mSchuesse[i] == NULL) //todo: je nach schusstyp geschwindigkeitsparameter ändern
        {
            mSchuesse[i] = new Schuss("data/rakete.png", angle, position, 10);
            break;
        }
    }
}

void SchussHandler::updateMovement()
{
    for (unsigned int i=0; i!=mSchuesse.max_size(); ++i)
    {//let every existing shoot calculate the new Positions
        if(mSchuesse[i] != 0)
            mSchuesse[i]->positionUpdate();
    }
}

void SchussHandler::displayAllShoots()
{
//first check the age of the shoots, and if they are too old, kill them
for (unsigned int i=0; i!=mSchuesse.max_size(); ++i)
{
    if(mSchuesse[i] != NULL)
    {
        if(mSchuesse[i]->getAgeWhileAging() >= 50)
        {
            delete mSchuesse[i];
            mSchuesse[i] = 0;
        }
    }
}

//then, if the shoots are still alive, lets display them
for (unsigned int i=0; i!=mSchuesse.max_size(); ++i)
    {
        if(mSchuesse[i] != NULL)
        {
            SDL_Surface* tmp = mEngine->getBackground();
            if(tmp == 0)
                std::cout << "tmp is 0, cant blit that" << std::endl;
            SDL_Rect offset;
            offset.x = mSchuesse[i]->getMiddleX();
            offset.y = mSchuesse[i]->getMiddleY();
            SDL_BlitSurface(mSchuesse[i]->getRotatedImg(), NULL, tmp, &offset);
        }
        /*else
        {
            std::cout << "mschuss == 0!" << std::endl;
        }*/
    }
}

unsigned int SchussHandler::getSchussCoolDown()
{
    return 3; //todo: the cooldown of each shoot has to be individual. atm its "3/25" seconds
}

SchussHandler::~SchussHandler()
{
    //std::cout << "SchussHandler::~SchussHandler();" << std::endl;
    for (unsigned int i=0; i!=mSchuesse.max_size(); ++i)
    { //not necessary to set te pointers to Zero, because the SchussHandler will be destroyed very soon
        if(mSchuesse[i] != NULL)
        {
            delete mSchuesse[i];
            //mSchuesse[i] = NULL; //yep, not necessary
            //std::cout << "\tdelete mSchuesse[" << i << "]" << std::endl;
        }
    }
}
