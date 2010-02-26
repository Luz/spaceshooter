#include <string>

#include "Asteroid.hpp"
#include "global.hpp"

Asteroid::Asteroid(Engine* mengine)
:Object(mengine, ASTEROID), weight(8)
{
    double x0 = -0.2 * SCREEN_WIDTH; //todo: -widthofimg + 0
    double x1 = 1.2 * SCREEN_WIDTH;  //todo: widthofimg + SCREEN_WIDTH
    double y0 = -0.2 * SCREEN_HEIGHT;//todo: -heightofimg + 0
    double y1 = 1.2 * SCREEN_HEIGHT; //todo: heightofimg + SCREEN_HEIGHT

    Position = (x0 + (x1 - x0) * rand() / ((double) RAND_MAX) )
        + 1i * (y0 + (y1 - y0) * rand() / ((double) RAND_MAX) );

    double xs0 = -5;
    double xs1 = 5;
    double ys0 = -5;
    double ys1 = 5;
    Speed =   (xs0 + (xs1 - xs0) * rand() / ((double) RAND_MAX) )
        +1i * (ys0 + (ys1 - ys0) * rand() / ((double) RAND_MAX) );

    Angle = 360 * rand() / ((double) RAND_MAX);
}

bool Asteroid::getCriticalPosition()
{
    if(     (Position.real() <= SCREEN_WIDTH * -0.25)
        ||  (Position.real() >= SCREEN_WIDTH * 1.25)
        ||  (Position.imag() <= SCREEN_HEIGHT * -0.25)
        ||  (Position.imag() >= SCREEN_HEIGHT * 1.25)    )
        {
            return true;
        }
    return false; //else
}

Asteroid::~Asteroid()
{
}
