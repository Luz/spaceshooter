#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "global.hpp"
#include "Engine.hpp"
#include "Rakete.hpp"
#include "Asteroid.hpp"
#include "SDL_rotozoom.h" // remove this after correcting "the loading of background" in the constructor of Engine

int Engine::Enginecounter=0;

Engine::Engine()
:quit(0), Screen(NULL), Background(NULL), LoadedBackgroundImage(NULL), Frame(0),
    LimitFps(true), Pause(false), Keystates(SDL_GetKeyState(NULL))
{
    if(Enginecounter == 0)
        Enginecounter++;
    else
        std::cout << "Haha, you now have two Engines... n00b, now you have definedely the Senf" << std::endl;

    mSchussHandler = new SchussHandler(this);
    if(mSchussHandler == NULL)
        std::cout << "An error occured: Could not create a SchussHandler" << std::endl;

    mObjectHandler = new ObjectHandler(this);
    if(mObjectHandler == NULL)
        std::cout << "An error occured: Could not create a ObjectHandler" << std::endl;

    mPlayerHandler = new PlayerHandler(this, mSchussHandler);
    if(mPlayerHandler == NULL)
        std::cout << "An error occured: Could not create a PlayerHandler" << std::endl;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        std::cout << "An error occurred: Could not initialise SDL" << std::endl;

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(Screen == NULL)
	    printf("An error occured: %s\n",SDL_GetError());

	SDL_WM_SetCaption("Waracefighter? Waracealot? Warazealot? Warimat? Wurimat? Ludo? Ludos Tudios?", NULL);

    LoadedBackgroundImage = load_image("data/background.png");
	if(LoadedBackgroundImage == NULL)
	    std::cout << "Error: Coult not find the background image in data/background.png" << std::endl;

    Background = load_image("data/background.png");
	if(Background == NULL)
	    std::cout << "Error: Coult not find the background image in data/background.png" << std::endl;

/* doesnt work :'( but creates a cool "ghost"-effect!
    // create an image for the Background with 32 bit and RGBA, but not from file
    Background = SDL_CreateRGBSurface(SDL_SWSURFACE, LoadedBackgroundImage->w, LoadedBackgroundImage->h, 32,
        #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                                    0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
        #else
                                    0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
        #endif
                                    );
	if(Background == NULL)
	    std::cout << "Error: Coult not initialize the background" << std::endl;
    //SDL_BlitSurface(LoadedBackgroundImage, NULL, Background, NULL);
    SDL_BlitSurface(LoadedBackgroundImage, NULL, Screen, NULL);
    //SDL_BlitSurface(Background, NULL, Screen, NULL);
    SDL_Flip(Screen);
    SDL_Delay(1000);*/

    srand(time(0));

    mPlayerHandler->newPlayer(MENSCH);

//    mPlayer = new Spieler("data/spieler.png"/*,mSpielerHandler*/, mSchussHandler);
//    if(mPlayer == NULL)
//	    std::cout << "Coult not create the player-rakete" << std::endl;

    Fps.start();
}

SDL_Surface* Engine::load_image(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());

	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	if(optimizedImage == NULL)
        std::cout << "Error, maybe Picture not found: " << filename.c_str() << std::endl;
    return optimizedImage;
}
/*
void Engine::applySurface(int x, int y, SDL_Surface* source, SDL_Rect* clip)
{
    if(source == 0)
        std::cout << "source is 0, cant blit that" << std::endl;
    SDL_Rect offset;
	offset.x = x;
	offset.y = y;
    SDL_BlitSurface(source, clip, Background, &offset);
}*/

void Engine::addObject(int typ)
{
    switch (typ)
    {
        case 0:
            mObjectHandler->newObject(OBJEKT);
            break;
        case 1:
            mObjectHandler->newObject(SPIELER);
            break;
        case 2:
            mObjectHandler->newObject(ASTEROID);
            break;
        case 3:
            mObjectHandler->newObject(GEGNER);
            break;
        case 4:
            mObjectHandler->newObject(RAKETE);
            break;
        case 5:
            mObjectHandler->newObject(SCHUSS);
            break;
        default:
            std::cout << "unknown object -> didn't created any shit" << std::endl;
            break;
    }
}

/*void Engine::displayObject(Object* mobject)
{
    if(mobject != NULL)
        //applySurface(mobject->getMiddleX(), mobject->getMiddleY(), mobject->getRotatedImg());
    {
        SDL_Surface* tmp = mobject->getRotatedImg();
        if(tmp == 0)
            std::cout << "tmp is 0, cant blit that" << std::endl;
        SDL_Rect offset;
        offset.x = mobject->getMiddleX();
        offset.y = mobject->getMiddleY();
        SDL_BlitSurface(tmp, NULL, Background, &offset);
    }
    else
        std::cout << "mobject == 0!" << std::endl;
}*/

void Engine::moveUpdater()
{
    if(mPlayerHandler != NULL) //let the object(player) calculate his new Position
        mPlayerHandler->updateMovement();
    //if(mPlayer != NULL)
    //    mPlayer->positionUpdate();

    mObjectHandler->updateMovement();

    if(mSchussHandler != NULL)
    {
        mSchussHandler->updateMovement();
    }
}

void Engine::keyPlayer(int key)
{
    if( (mPlayerHandler != NULL) && (Pause == false) )
    {
        mPlayerHandler->keyDown(key);
/*        switch (key)
        {
            case 1: mPlayerHandler->keyDown(key); break; //incSpeed(0.2); break;
            case 2: mPlayerHandler->incSpeed(-0.2); break;
            case 3: mPlayerHandler->rotatePlayer(10); break;
            case 4: mPlayerHandler->rotatePlayer(-10); break;
            case 5: mPlayerHandler->schiessen(); break;
            //case 6: delete mPlayer; mPlayer = 0; break;
            default: break;
        }*/
    }
}

/*void Engine::rotatePlayer(float angle)
{
    mPlayer->setAngle(mPlayer->getAngle() + angle);
}*/

void Engine::update()
{
    if(Pause == false)
    {
        moveUpdater();

        //Background = LoadedBackgroundImage;
//        applySurface(0, 0, LoadedBackgroundImage);
        SDL_BlitSurface(LoadedBackgroundImage, NULL, Background, NULL);

        if(mPlayerHandler != NULL)
            mPlayerHandler->displayAllPlayers();//draw the player on the background
        else
            std::cout << "Error: mPlayerHandler is 0" << std::endl;

        if(mObjectHandler != NULL) //draw the objects on the background
            mObjectHandler->displayAllObjects();
        else
            std::cout << "Error: mObjectHandler is 0" << std::endl;

        if(mSchussHandler != NULL) //draw the shoots on the background
            mSchussHandler->displayAllShoots();
        else
            std::cout << "Error: mSchussHandler is 0" << std::endl;

        SDL_BlitSurface(Background, NULL, Screen, NULL); //draw the background on the screen

        SDL_Flip(Screen); //show the new screen
        //std::cout << "Frame Number: " << Frame << std::endl;

        Frame++;
        if( (true == LimitFps) && (Fps.getTicks() < (1000 / FRAMES_PER_SECOND)) )
        {
            //std::cout << "Wait for next Frame" << std::endl;
            SDL_Delay( (1000 / FRAMES_PER_SECOND) - Fps.getTicks() );
        }
        Fps.start();
    }
}

bool Engine::getQuit()
{
    return quit;
}

void Engine::setQuit()
{
    quit = true;
}

void Engine::exit()
{
    SDL_FreeSurface(Background);
    SDL_FreeSurface(Screen);// bruchts die ziilä eigentlich würklich nöd? s'tutorial meint "nei", ich denk es het falsch
    SDL_Quit();
}

void Engine::limitFps(bool limit)
{
    LimitFps = limit;
}

void Engine::togglePause()
{
if(Pause == true)
    Pause = false;
else
    Pause = true;
}

bool Engine::getKeyState(SDLKey key)
{
    if(Keystates[key])
        return true;
    else
        return false;
}

void Engine::readKeyStates()
{
    Keystates = SDL_GetKeyState(NULL);
}

/*void Engine::writeDataInFile(std::string filename)
{
    const int x = 42;
    std::ofstream save(filename.c_str());
    boost::archive::text_oarchive oa(save);
    oa << x;
    save.close();

//    typedef base::file_stream bafst;
//    bafst::file_stream ofs("test.txt", bafst::trunc | bafst::out);
//    boost::archive::xml_oarchive xml(ofs);
//    xml << boost::serialization::make_nvp("Italian Sandwich", sw);


//    std::ofstream save(filename.c_str());
//    const std::string g("hllk");
//    boost::archive::text_oarchive oa(save);
//    oa << g;
//    save.close();
}*/

SDL_Surface* Engine::getBackground()
{
    return Background;
}

Engine::~Engine()
{
    /*char typeString[32];
    switch (mObjects[i]->getType())
    {
        case OBJEKT:    strcpy(typeString, "Objekt"); break;
        case RAKETE:    strcpy(typeString, "Rakete"); break;
        case ASTEROID:  strcpy(typeString, "Asteroid"); break;
        case GEGNER:    strcpy(typeString, "Gegner"); break;
        default:        strcpy(typeString, "WtfIsThis?"); break;
    }*/
    //std::cout << "Deleting a : " << typeString << std::endl;
    //not necessary to set the pointer to zero, the engine wont exist in a few
    delete mObjectHandler;

    if(mPlayerHandler != NULL)
        delete mPlayerHandler; //not necessary to set the pointer to zero, the engine wont exist in a few
    if(mSchussHandler != NULL)
        delete mSchussHandler; //not necessary to set the pointer to zero, the engine wont exist in a few
}
