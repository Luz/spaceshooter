#include <iostream>

#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(Engine* mengine)//, ObjectHandler* mobjecthandler, SchussHandler* mschusshandler)
:mEngine(mengine)//, mObjectHandler(mobjecthandler), mSchussHandler(mschusshandler)
{
    //for (int i=0; i!=mSchuesse.max_size(); ++i) mSchuesse[i] = NULL;
}

bool CollisionHandler::checkCollision(std::complex<float> position1, unsigned int radius1,
                                        std::complex<float> position2, unsigned int radius2)
{
    return false; //todo: implement this method!
}

void CollisionHandler::executeCollision()
{
//todo
}

void CollisionHandler::executeAllCollisions()
{
//todo
}
