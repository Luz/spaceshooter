#include <string>
#include <iostream>
#include <math.h>
#include <complex>

#include "SDL_rotozoom.h"

#include "Object.hpp"
#include "Engine.hpp"
#include "global.hpp"

Object::Object(Engine* mengine, ObjectType type, double x, double y, double speedx, double speedy)
:Type(type), Position(x, y), Speed(speedx + speedy * 1i), Angle(0),
    mEngine(mengine), Image(mengine->getObjectImage(type)), RotatedImage(NULL), Radius(20)
{
}

int Object::getMiddleX()
{   //0.5f has been outcommented, because its not much
    return (int)(Position.real() - (getRotatedImg()->w / 2) );//+ 0.5l);
} //todo: very slow to check the size of the rotatedimg each time?

int Object::getMiddleY()
{   //0.5f has been outcommented, because its not much
    return (int)(Position.imag() - (getRotatedImg()->h / 2) );//+ 0.5l);
} //todo: very slow to check the size of the rotatedimg each time?

void Object::positionUpdate()
{
    //first, calculate the new position
    double real = Position.real()+Speed.real();
    double imag = Position.imag()+Speed.imag();

    //then, wrap the position around if its in the wrong place
    //if the object is too fast (speed bigger than screenwidth) it should disappear from the screen, but such a speed...
    if(Position.real() < 0)
        real += (double)SCREEN_WIDTH;
    if(Position.imag() < 0)
        imag += (double)SCREEN_HEIGHT;
    if(Position.real() > SCREEN_WIDTH)
        real -= (double)SCREEN_WIDTH;
    if(Position.imag() > SCREEN_HEIGHT)
        imag -= (double)SCREEN_HEIGHT;

    Position = std::complex<double>(real, imag);
}

void Object::rotate(double angle)
{
    Angle += angle;
}

void Object::incSpeed(double inc)
{
    std::complex<double> SpeedIncAngle(0,((Angle+90)/180*M_PI));
    Speed += inc * exp(-SpeedIncAngle);
}

SDL_Surface* Object::getRotatedImg()
{
    if(Image != NULL)
    {
        SDL_FreeSurface(RotatedImage); //Free the Memory of the old RotatedImage
        //RotatedImage = NULL; //unnecessary
        RotatedImage = rotozoomSurface(Image, Angle, 0.9, 1);//Allocate new Memory for the new RotatedImage
    }
    if(Image == NULL)
        std::cout << "Error: Image == NULL" << std::endl; //should absolutely never happen
    return RotatedImage;
}

bool Object::getCriticalPosition()
{   //todo: calculate the critical position in the derivated objects, such as asteroid.cpp. overwrite this function!
    return false;
}

Object::~Object()
{
    SDL_FreeSurface(RotatedImage);
}
