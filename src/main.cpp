#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

//#include "global.hpp"
#include "Engine.hpp"
//#include "Rakete.hpp"

int main()
{
    Engine E;
    SDL_Event event;

	while(false == E.getQuit())
	{
		while(SDL_PollEvent(&event))
		{//de ganz scheiss useschmeisse und sofort ufd igabe reagiere gaht schneller, glichr meinig?
			if(event.type == SDL_QUIT)
				E.setQuit();
			if(event.type == SDL_KEYDOWN)
			{
                if(event.key.keysym.sym == SDLK_p)
                    E.togglePause();
                else // if (E.getPause() == false)
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_s:        E.addObject(1); break; //Spieler
                        case SDLK_g:        E.addObject(3); break; //Gegner
                        case SDLK_r:        E.addObject(4); break; //Rakete
                        //case SDLK_0:        E.writeDataInFile("test.txt"); break;

                        case SDLK_u:        E.limitFps(false); break; // in final version, these
                        case SDLK_l:        E.limitFps(true); break; //  two should be removed

                        case SDLK_d:        E.setQuit(); break;
                        case SDLK_q:        E.setQuit(); break;
                        case SDLK_ESCAPE:   E.setQuit(); break;
                        default: break;
                    }
                }
			}
		}
		E.readKeyStates();
        if(E.getKeyState(SDLK_UP))
            E.keyPlayer(1);
        if(E.getKeyState(SDLK_DOWN))
            E.keyPlayer(2);
        if(E.getKeyState(SDLK_LEFT))
            E.keyPlayer(3);
        if(E.getKeyState(SDLK_RIGHT))
            E.keyPlayer(4);
        if(E.getKeyState(SDLK_SPACE))
            E.keyPlayer(5);
        if(E.getKeyState(SDLK_a))
            E.addObject(2); //Asteroid
		E.update();
	}
	E.exit();
	return 0;
}
