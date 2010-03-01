#include <iostream>

#include "CollisionHandler.hpp"

CollisionHandler::CollisionHandler(Engine* mengine)//, ObjectHandler* mobjecthandler, SchussHandler* mschusshandler)
:mEngine(mengine)//, mObjectHandler(mobjecthandler), mSchussHandler(mschusshandler)
{
    //for (int i=0; i!=mSchuesse.max_size(); ++i) mSchuesse[i] = NULL;
}

bool CollisionHandler::checkCollision(std::complex<double> pos1, unsigned int radius1,
                                      std::complex<double> pos2, unsigned int radius2)
{
	float x = pos1.real() - pos2.real()
	float y = pos1.imag() - pos2.imag();
	float distanz = sqrt(x*x+y*y);

	if (distanz < (radius1+radius2) )
		return true;
	return false;
}

void CollisionHandler::executeCollision()
{
//todo
}

void CollisionHandler::executeAllCollisions()
{
//todo
}
