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
        Spieler(std::string filename, PlayerHandler* mplayerhandler, SchussHandler* mschusshandler,
            float x = SCREEN_WIDTH / 2, float y = SCREEN_HEIGHT / 3 * 2 );
        void schiessen();
        void decSchussCoolDown();
        virtual ~Spieler();
    private:
        PlayerHandler* mPlayerHandler;
        SchussHandler* mSchussHandler;
        unsigned int SchussCoolDown;
};

#endif