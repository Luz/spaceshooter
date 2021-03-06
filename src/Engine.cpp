#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>

//#include <fstream>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>

#include "global.hpp"
#include "Engine.hpp"
#include "Asteroid.hpp"

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

	SDL_WM_SetCaption("Space Shooter", NULL);

    LoadedBackgroundImage = loadImage("data/background.png");
	if(LoadedBackgroundImage == NULL)
	    std::cout << "Error: Coult not find the background image in data/background.png" << std::endl;

    Background = loadImage("data/background.png");
	if(Background == NULL)
	    std::cout << "Error: Coult not find the background image in data/background.png" << std::endl;

    std::string tmp;
    //should be done for each object in objecttype
    for (unsigned int i=0; i!=Images.max_size(); ++i)
    {
        tmp = "data/";
        tmp += (char)(i+49);
        tmp += ".png";
        Images[i] = loadImage(tmp);//todo: correct image -> objecttype!
        if(Images[i] == NULL)
            std::cout << "should not be here!" << std::endl;
    }

    srand(time(0));

    mPlayerHandler->newPlayer(HUMAN);

    Keystates = SDL_GetKeyState(NULL);

    Fps.start();
}

SDL_Surface* Engine::loadImage(std::string filename)
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

void Engine::addObject(ObjectType type)
{
    switch (type)
    {
        case PLAYER:
            mObjectHandler->newObject(PLAYER);
            break;
        case ASTEROID:
            mObjectHandler->newObject(ASTEROID);
            break;
        case ENEMY:
            mObjectHandler->newObject(ENEMY);
            break;
        case ROCKET:
            mObjectHandler->newObject(ROCKET);
            break;
        case GREEN:
            mObjectHandler->newObject(GREEN);
            break;
        default:
            std::cout << "unknown object -> didn't created any shit!" << std::endl;
            break;
    }
}

void Engine::moveUpdater()
{
    if(mPlayerHandler != NULL) //let the playerhandler calculate the new position of the player
        mPlayerHandler->updateMovement();
    /*else
        std::cout << "Engine: mPlayerHandler is 0" << std::endl;*/

    if(mObjectHandler != NULL)
        mObjectHandler->updateMovement();
    /*else
        std::cout << "Engine: mObjectHandler is 0" << std::endl;*/

    if(mSchussHandler != NULL)
        mSchussHandler->updateMovement();
    /*else
        std::cout << "Engine: mSchussHandler is 0" << std::endl;*/
}

void Engine::keyPlayer(unsigned int key)
{
    if( (mPlayerHandler != NULL) && (Pause == false) )
    {
        mPlayerHandler->keyDown(key);
    }
}

void Engine::update()
{
    if(Pause == false)
    {
        moveUpdater();

        SDL_BlitSurface(LoadedBackgroundImage, NULL, Background, NULL);

        if(mPlayerHandler != NULL)
            mPlayerHandler->displayAllPlayers();//draw the players on the background
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
    //SDL_FreeSurface(Screen); dont uncomment this line! forbidden! would crash some systems
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
    //not necessary to set the pointer to zero, the engine wont exist in a few
    delete mObjectHandler;

    if(mPlayerHandler != NULL)
        delete mPlayerHandler; //not necessary to set the pointer to zero, the engine wont exist in a few
    if(mSchussHandler != NULL)
        delete mSchussHandler; //not necessary to set the pointer to zero, the engine wont exist in a few

    for (unsigned int i=0; i!=Images.max_size(); ++i)
    { //should be done for each object in objecttype
        if(Images[i] != NULL)
            SDL_FreeSurface(Images[i]);
    }
}
