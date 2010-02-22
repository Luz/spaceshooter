#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <boost/array.hpp>

#include "timer.hpp"
//#include "Spieler.hpp"
#include "SchussHandler.hpp"
#include "ObjectHandler.hpp"
#include "PlayerHandler.hpp"

//class Object;
class Spieler;
class Timer;
class Schuss;
class SchussHandler;
class ObjectHandler;
class PlayerHandler;

class Engine
{
public:
    Engine();
	SDL_Surface* load_image(std::string filename);
	void applySurface(int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL);
	void addObject(int typ);
	void moveUpdater();
	void keyPlayer(int key);
	void rotatePlayer(float angle);
	void update();
	bool getQuit();
	void setQuit();
	void exit();
	void limitFps(bool limit);
	void togglePause();
	bool getKeyState(SDLKey key);
	void readKeyStates();
	//void writeDataInFile(std::string filename);
	SDL_Surface* getBackground();
	virtual ~Engine();
private:
    static int Enginecounter;
    bool quit;
	SDL_Surface* Screen;
	SDL_Surface* Background;
	SDL_Surface* LoadedBackgroundImage;
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
