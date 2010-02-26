#ifndef SPIELER_HPP
#define SPIELER_HPP

#include "Object.hpp"
#include "Engine.hpp"
#include "PlayerHandler.hpp"
#include "SchussHandler.hpp"
#include "global.hpp"

class PlayerHandler;

class Spieler: public Object
{
    public:
        Spieler(Engine* mengine, PlayerHandler* mplayerhandler, SchussHandler* mschusshandler,
            double x = (double)SCREEN_WIDTH / 2, double y = (double)SCREEN_HEIGHT / 3 * 2 );
        void schiessen();
        void decSchussCoolDown();
        virtual ~Spieler();
    private:
        PlayerHandler* mPlayerHandler;
        SchussHandler* mSchussHandler;
        unsigned int SchussCoolDown;
};

#endif
