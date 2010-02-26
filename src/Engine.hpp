#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <boost/array.hpp>

#include "timer.hpp"
#include "SchussHandler.hpp"
#include "ObjectHandler.hpp"
#include "PlayerHandler.hpp"

class Spieler;
class Timer;
class SchussHandler;
class ObjectHandler;
class PlayerHandler;

class Engine
{
public:
    Engine();
	SDL_Surface* loadImage(std::string filename);
	SDL_Surface* getObjectImage(ObjectType type) { return Images[type-1]; };
	void applySurface(int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL);
	void addObject(int typ);
	void moveUpdater();
	void keyPlayer(unsigned int key);
	void update();
	bool getQuit();
	void setQuit();
	void exit();
	void limitFps(bool limit);
	void togglePause();
	bool getKeyState(SDLKey key);
	//void writeDataInFile(std::string filename);
	SDL_Surface* getBackground();
	virtual ~Engine();
private:
    static int Enginecounter;
    bool quit;
	SDL_Surface* Screen;
	SDL_Surface* Background;
	SDL_Surface* LoadedBackgroundImage;
	boost::array<SDL_Surface*, 5> Images; //todo: replace 5 with the length of all objects in ObjectType.h
	int Frame;
	bool LimitFps;
	Timer Fps;
	bool Pause;
	Uint8* Keystates;
	ObjectHandler* mObjectHandler;
	SchussHandler* mSchussHandler;
	PlayerHandler* mPlayerHandler;
};

#endif
