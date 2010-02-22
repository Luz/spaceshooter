#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "SDL/SDL.h"
#include <string>
#include <complex>

#include "ObjectType.h"

class Engine;

class Object
{
	public:
        Object(std::string filename, ObjectType type=OBJEKT, float x = 0, float y = 0, float speedx = 0, float speedy = 0);
        int getMiddleX();
        int getMiddleY();
        void positionUpdate();
        void rotate(float angle);
        void incSpeed(float inc);
        SDL_Surface* getRotatedImg();
        void display();
        virtual bool getCriticalPosition();
        virtual ~Object();
    protected:
        ObjectType Type;
        std::complex<float> Position;
        std::complex<float> Speed;
		float Angle;
	private:
        SDL_Surface* Image;
        SDL_Surface* RotatedImage;
		unsigned int Radius;
};
#endif
