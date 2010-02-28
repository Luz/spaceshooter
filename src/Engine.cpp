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
#include "Rakete.hpp"
#include "Asteroid.hpp"


int Engine::Enginecounter=0;

Engine::Engine()
:quit(0), Screen(NULL), Background(NULL), LoadedBackgroundImage(NULL), Frame(0),
    LimitFps(true), Pause(false), Keystates(SDL_GetKeyState(NULL)),
    Player(this)
{
    if(Enginecounter == 0)
        Enginecounter++;
    else
        std::cerr << "Haha, you now have two Engines... n00b, now you have definedely the Senf" << std::endl;

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        std::cerr << "An error occurred: Could not initialise SDL" << std::endl;

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(Screen == NULL)
	    printf("An error occured: %s\n",SDL_GetError());

	SDL_WM_SetCaption("Space Shooter", NULL);

    LoadedBackgroundImage = loadImage("data/background.png");
	if(LoadedBackgroundImage == NULL)
	    std::cerr << "Error: Coult not find the background image in data/background.png" << std::endl;

    Background = loadImage("data/background.png");
	if(Background == NULL)
	    std::cerr << "Error: Coult not find the background image in data/background.png" << std::endl;

    std::string tmp;
    //should be done for each object in objecttype
    for (unsigned int i=0; i!=5; ++i)
    {
        tmp = "data/";
        tmp += (char)(i+49);
        tmp += ".png";
     
        Images.push_back(loadImage(tmp));//todo: correct image -> objecttype!
    }
    srand(time(0));

    Keystates = SDL_GetKeyState(NULL);
    std::cout << "Engine start" << std::endl;

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

  std::cout << "image load: " << filename << std::endl;

  return optimizedImage;
}

void Engine::addObject(int typ)
{
    switch (typ)
    {
        case 0:
            std::cout << "don't do anything. i'm in file src/Engine.cpp in the method addObject(..)" << std::cout;
            break;
//        case 1:
//            mObjectHandler->newObject(SPIELER);
//            break;
        case 2:
            new Asteroid(this);
            break;
//        case 3:
//            mObjectHandler->newObject(GEGNER);
//            break;
        case 4:
            new Rakete(this);
            break;
//        case 5:
//            new Schuss(this);
//            break;
        default:
            std::cout << "unknown object -> didn't created any shit" << std::endl;
            break;
    }
}

void Engine::moveUpdater()
{
    Object::UpdateAll();
}

void Engine::keyPlayer(unsigned int key)
{
	 Player.keyDown(key);
}

void Engine::update()
{
    if(Pause == false)
    {
        moveUpdater();

        SDL_BlitSurface(LoadedBackgroundImage, NULL, Background, NULL);

        Object::UpdateAll();
        

        SDL_BlitSurface(Background, NULL, Screen, NULL); //draw the background on the screen
        Object::ShowAll();
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

    for (unsigned int i=0; i!=Images.max_size(); ++i)
    { //should be done for each object in objecttype
        if(Images[i] != NULL)
            SDL_FreeSurface(Images[i]);
    }
}
