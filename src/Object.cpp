#include <string>
#include <iostream>
#include <math.h>
#include <complex>

//#include "utilf.h"
//#include "interpolation.h"

#include "SDL_rotozoom.h"

#include "Object.hpp"
#include "Engine.hpp"
#include "global.hpp"

Object::Object(std::string filename, ObjectType type, float x, float y, float speedx, float speedy)
:Type(type), Position(x, y), Speed(speedx + speedy * 1i), Angle(0), Image(NULL), RotatedImage(NULL), Radius(20)
{
    SDL_Surface* LoadedImage = NULL;

	LoadedImage = IMG_Load(filename.c_str());
    if(LoadedImage == NULL)
        std::cout << "Error, maybe Picture not found: " << filename.c_str() << std::endl;
	else
	{
		Image = SDL_DisplayFormatAlpha(LoadedImage);
		RotatedImage = rotozoomSurface(Image, Angle, 0.9, 1); //and use this one
		SDL_FreeSurface(LoadedImage);
	}

	if(Image == NULL)
        std::cout << "Error, mysterious one A" << filename.c_str() << std::endl;
    if(LoadedImage == NULL)
        std::cout << "Error, mysterious one B" << std::endl;
}

int Object::getMiddleX()
{
    return (int)(Position.real() - (getRotatedImg()->w / 2) + 0.5f);
} //todo: very slow to check the size of the rotatedimg each time?

int Object::getMiddleY()
{
    return (int)(Position.imag() - (getRotatedImg()->h / 2) + 0.5f);
} //todo: very slow to check the size of the rotatedimg each time?

void Object::positionUpdate()
{
    //first, calculate the new position
    float real = Position.real()+Speed.real();
    float imag = Position.imag()+Speed.imag();

    //then, wrap the position around if its in the wrong place
    //if the object is too fast (speed bigger than screenwidth) it should disappear from the screen, but such a speed...
    if(Position.real() < 0)
        real += (float)SCREEN_WIDTH;
    if(Position.imag() < 0)
        imag += (float)SCREEN_HEIGHT;
    if(Position.real() > SCREEN_WIDTH)
        real -= (float)SCREEN_WIDTH;
    if(Position.imag() > SCREEN_HEIGHT)
        imag -= (float)SCREEN_HEIGHT;

    Position = std::complex<float>(real, imag);
}

void Object::rotate(float angle)
{
    Angle += angle;
}

void Object::incSpeed(float inc)
{
    std::complex<float> SpeedIncAngle(0,((Angle+90)/180*M_PI));
    Speed += inc * exp(-SpeedIncAngle);
}

SDL_Surface* Object::getRotatedImg()
{
    if(Image == NULL)
        std::cout << "Error: Image == NULL" << std::endl; //remove? will never happen
    else
    {
        SDL_FreeSurface(RotatedImage); //Free the Memory of the old RotatedImage
        RotatedImage = NULL; //remove this?
        RotatedImage = rotozoomSurface(Image, Angle, 0.9, 1);//Allocate new Memory for the new RotatedImage

        if(RotatedImage == NULL)
            std::cout << "Error: RotatedImage == NULL" << std::endl; //remove? will never happen
    }
    return RotatedImage;
}

bool Object::getCriticalPosition()
{
    return false; //todo: calculate the critical position in the derivated objects, such as asteroid.cpp. overwrite this function!
}

Object::~Object()
{
    SDL_FreeSurface(Image);
    SDL_FreeSurface(RotatedImage);
}
