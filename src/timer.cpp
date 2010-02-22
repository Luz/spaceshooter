#include "SDL/SDL.h"

#include "timer.hpp"

Timer::Timer()
:startTicks(0), pausedTicks(0), started(false), paused(false)
{
}
void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}
void Timer::stop()
{
    started = false;
    paused = false;
}
void Timer::togglePause()
{
    if(true == started)
    {
        if(false == paused)
        {   //pause function starts here
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }   //pause function ends here
        else
        {   //unpause function starts here
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
            pausedTicks = 0;
        }   //unpause function ends here
    }
}
int Timer::getTicks()
{
    if(true == started)
    {
        if(true == paused)
            return pausedTicks;
        else
            return SDL_GetTicks() - startTicks;
    }
    return 0;
}
bool Timer::isStarted()
{
    return started;
}
bool Timer::isPaused()
{
    return paused;
}

Timer::~Timer()
{
}
