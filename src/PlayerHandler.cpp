#include <iostream>

#include "PlayerHandler.hpp"

PlayerHandler::PlayerHandler(Engine* mengine, SchussHandler* mschusshandler)
:mEngine(mengine), mSchussHandler(mschusshandler)
{
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i) mPlayers[i] = NULL;
    //goes through the mPlayers array and puts every pointer to NULL
}

void PlayerHandler::newPlayer(PlayerType typ, std::complex<double> position, double angle)
{
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    {
        if(mPlayers[i] == NULL)
        {
            switch (typ)
            {
                case 0://MENSCH
                    mPlayers[i] = dynamic_cast<Spieler*> (new Spieler("data/spieler.png", this, mSchussHandler));
                    break;
                /*case 1://ALIEN
                     mPlayers[i] = new Gegner("data/gegner.png"); //todo class gegner
                    break;
                case 2://
                    //mPlayers[i] = dynamic_cast<Player*> (new Rakete("data/rakete.png"));
                    mPlayers[i] = new Rakete("data/rakete.png");
                    break;*/
                default://Else
                    std::cout << "dont know this Player, (so didnt created any shit)" << std::endl;
                    break;
            }
            break;
        }
    }
}

void PlayerHandler::updateMovement()
{
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    {//let every existing Player calculate the new Position
        if(mPlayers[i] != NULL)
            mPlayers[i]->positionUpdate();
    }
}


void PlayerHandler::keyDown(unsigned int key, unsigned int playernumber)
{
/*    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    {//let every existing Player calculate the new Position
        if(mPlayers[i] != NULL)
            mPlayers[i]->positionUpdate();
    }
*/
        switch (key)
        {
            case 1: mPlayers[playernumber]->incSpeed(0.2); break;
            case 2: mPlayers[playernumber]->incSpeed(-0.2); break;
            case 3: mPlayers[playernumber]->rotate(10); break;
            case 4: mPlayers[playernumber]->rotate(-10); break;
            case 5: mPlayers[playernumber]->schiessen(); break;
            //case 6: delete mPlayer; mPlayer = 0; break;
            default: break;
        }
}

void PlayerHandler::displayAllPlayers()
{
    //first let each player calculate the new cooldown for the next shooting
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    {
        if(mPlayers[i] != NULL)
            mPlayers[i]->decSchussCoolDown();
    }

    //then, if the player is still alive, lets display them
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    {
        if(mPlayers[i] != NULL)
        {
            SDL_Surface* tmp = mEngine->getBackground();
            if(tmp == 0)
                std::cout << "tmp is 0, cant blit that" << std::endl;
            SDL_Rect offset;
            offset.x = mPlayers[i]->getMiddleX();
            offset.y = mPlayers[i]->getMiddleY();
            SDL_BlitSurface(mPlayers[i]->getRotatedImg(), NULL, tmp, &offset);
        }
    }
}

PlayerHandler::~PlayerHandler()
{
    for (unsigned int i=0; i!=mPlayers.max_size(); ++i)
    { //not necessary to set te pointers to Zero, because the PlayerHandler will be destroyed very soon
        if(mPlayers[i] != NULL)
            delete mPlayers[i];
    }
}
