#include <iostream>

#include "ObjectHandler.hpp"

ObjectHandler::ObjectHandler(Engine* mengine)
:mEngine(mengine)
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i) mObjects[i] = NULL;
    //goes through the mObjects array and puts every pointer to NULL
}

void ObjectHandler::newObject(ObjectType typ, std::complex<float> position, float angle)
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    {
        if(mObjects[i] == NULL)
        {

            switch (typ)
            {
                //case 0://Objekt
                //    mObjects[i] = new Objekt("data/objekt.png");
                //    break;
                //case 1://Spieler
                //    mObjects[i] = dynamic_cast<Object*> (new Spieler("data/spieler.png"),mschusshandler);
                //    break;
                case 2://Asteroid
                    mObjects[i] = dynamic_cast<Object*> (new Asteroid("data/asteroid.png"));
                    break;
                //case 3://Gegner
                //    mObjects[i] = new Gegner("data/gegner.png"); //todo class gegner
                //    break;
                /*case 4://Rakete
                    //mObjects[i] = dynamic_cast<Object*> (new Rakete("data/rakete.png"));
                    mObjects[i] = new Rakete("data/rakete.png");
                    break;*/
                //case 5://Schuss
                //    mObjects[i] = new Schuss("data/spieler.png");
                //    break;
                default://Else
                    std::cout << "dont know this object, (so didnt created any shit)" << std::endl;
                    break;
            }
            break;
        }
    }
}

void ObjectHandler::updateMovement()
{
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    {//let every existing object calculate the new Position
        if(mObjects[i] != NULL)
            mObjects[i]->positionUpdate();
    }
}

void ObjectHandler::displayAllObjects()
{
//first check the position of the objects, and if they are too far, kill them
for (int i=0; i!=mObjects.max_size(); ++i)
{
    if(mObjects[i] != NULL)
    {
        if(mObjects[i]->getCriticalPosition() == true)
        {
            delete mObjects[i];
            mObjects[i] = 0;
        }
    }
}
//then, if the objects are still alive, lets display them
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
    std::cout << "ObjectHandler::~ObjectHandler();" << std::endl;
    for (unsigned int i=0; i!=mObjects.max_size(); ++i)
    { //not necessary to set te pointers to Zero, because the ObjectHandler will be destroyed very soon
        if(mObjects[i] != NULL)
        {
            delete mObjects[i];
            std::cout << "\tdelete mObjects[" << i << "]" << std::endl;
        }
    }
}
