#include <iostream>

#include "ObjectHandler.hpp"

ObjectHandler::ObjectHandler(Engine* mengine)
:mEngine(mengine)
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i) mObjects[i] = NULL;
    //goes through the mObjects array and puts every pointer to NULL
}

void ObjectHandler::newObject(ObjectType type, std::complex<float> position, float angle)
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    {
        if(mObjects[i] == NULL)
        {

            switch (type)
            {
                //case 0: //Object --> maybe needed sometime
                //    mObjects[i] = new Objekt("data/objekt.png");
                //    break;
                //case SPIELER
                //    mObjects[i] = dynamic_cast<Object*> (new Spieler("data/spieler.png"),mschusshandler);
                //    break;
                case ASTEROID:
                    mObjects[i] = dynamic_cast<Object*> (new Asteroid(mEngine));
                    break;
                //case GEGNER:
                //    mObjects[i] = new Gegner("data/gegner.png"); //todo class gegner
                //    break;
                //case ROCKET:
                //    mObjects[i] = dynamic_cast<Object*> (new Rakete(mEngine));
                //    break;
                //case GREEN:
                    //mObjects[i] = dynamic_cast<Object*> (new Schuss(mEngine));
                    //break;
                default://Else
                    std::cout << "dont know this object, (so didnt create any shit)" << std::endl;
                    break;
            }
            break;
        }
    }
}

bool ObjectHandler::checkCollision(Object &obj1, Object &obj2)
{
    float x = obj1.getMiddleX() - obj2.getMiddleX();
    float y = obj1.getMiddleY() - obj2.getMiddleY();
    float distanz = sqrt(x*x+y*y);
    // TODO: Radius seems to be wrong, without -10 it looks ugly
    if (distanz - (obj1.getRadius()+obj2.getRadius()) < -10 )
     {
         return true;
     }
     return false;
}

void ObjectHandler::updateMovement()
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    {//let every existing object calculate the new Position
        if(mObjects[i] != NULL)
        {
            mObjects[i]->positionUpdate();
            ObjectType type = mObjects[i]->getType();
            if(type == ASTEROID )
            {
                // check for collision with all remaining objects
                for(unsigned int j=i+1; j!=mObjects.max_size(); ++j)
                {
                    if(mObjects[j] )
                    {
                        if(mObjects[j]->getType() == ASTEROID && checkCollision(*mObjects[i], *mObjects[j]))
                        {
                            delete mObjects[j];
                            delete mObjects[i];
                            mObjects[j]=0;
                            mObjects[i]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void ObjectHandler::displayAllObjects()
{
    //if the objects are still alive, lets display them
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    {
        if(mObjects[i] != NULL)
        {
            SDL_Surface* tmp = mEngine->getBackground();
            if(tmp == 0)
                std::cout << "tmp is 0, cant blit that" << std::endl;
            SDL_Rect offset;
            offset.x = mObjects[i]->getMiddleX();
            offset.y = mObjects[i]->getMiddleY();
            SDL_BlitSurface(mObjects[i]->getRotatedImg(), NULL, tmp, &offset);
        }
    }
}

ObjectHandler::~ObjectHandler()
{
    //std::cout << "ObjectHandler::~ObjectHandler();" << std::endl;
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    { //not necessary to set te pointers to Zero, because the ObjectHandler will be destroyed very soon
        if(mObjects[i] != NULL)
        {
            delete mObjects[i];
            //std::cout << "\tdelete mObjects[" << i << "]" << std::endl;
        }
    }
}
