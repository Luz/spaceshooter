#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "SDL/SDL.h"
#include <string>
#include <complex>
#include <list>
#include "ObjectType.h"

class Engine;

class Object
{
	public:
        Object(Engine* mengine, ObjectType type, double x = 0, double y = 0, double speedx = 0, double speedy = 0);
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
        static void UpdateAll();
        static void ShowAll();
        
    protected:
        ObjectType Type;
        std::complex<double> Position;
        std::complex<double> Speed;
				double Angle;
        virtual bool Update();
        virtual void Show();
        static std::list<Object*>  AllObjects;
        Engine* mEngine;
	private:
        SDL_Surface* Image;
        SDL_Surface* RotatedImage;
		unsigned int Radius;
};
#endif
