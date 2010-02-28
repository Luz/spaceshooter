#ifndef SPIELER_HPP
#define SPIELER_HPP

#include "Object.hpp"
#include "global.hpp"
#include "PlayerType.h"

class Engine;

class Spieler: public Object
{
    public:
        Spieler(Engine* mengine,
            		double x = (double)SCREEN_WIDTH / 2,
             		double y = (double)SCREEN_HEIGHT / 3 * 2 );
        void keyDown(unsigned int key);
 
        void schiessen();
        void decSchussCoolDown();

        virtual ~Spieler();
    private:
        unsigned int SchussCoolDown;
};

#endif
