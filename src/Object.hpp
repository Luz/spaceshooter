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
        Object(std::string filename, ObjectType type=OBJEKT, double x = 0, double y = 0, double speedx = 0, double speedy = 0);
        int getMiddleX();
        int getMiddleY();
        void positionUpdate();
        void rotate(double angle);
        void incSpeed(double inc);
        SDL_Surface* getRotatedImg();
        void display();
        virtual bool getCriticalPosition();
        ObjectType getType() { return Type; };
        unsigned int getRadius() { return Radius; };
        virtual ~Object();
    protected:
        ObjectType Type;
        std::complex<double> Position;
        std::complex<double> Speed;
		double Angle;
	private:
        SDL_Surface* Image;
        SDL_Surface* RotatedImage;
		unsigned int Radius;
};
#endif
