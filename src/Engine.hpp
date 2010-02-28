#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <vector>

#include "timer.hpp"
#include "Spieler.hpp"

class Timer;

class Engine
{
public:
  Engine();
	SDL_Surface* loadImage(std::string filename);
	int					 loadGLImage(std::string filename);
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
	SDL_Surface* getScreen() { return Screen; }
	
	virtual ~Engine();
private:
    static int Enginecounter;
    bool quit;
		SDL_Surface* Screen;
		SDL_Surface* Background;
		std::vector<SDL_Surface*> Images;
		int Frame;
		int ListCounter;
		bool LimitFps;
		Timer Fps;
		bool Pause;
		Uint8* Keystates;
		Spieler Player;
};

#endif
