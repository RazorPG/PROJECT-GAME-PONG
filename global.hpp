#ifndef __GLOBAL
#define __GLOBAL

#include <raylib.h>

#define screenWidth 1280
#define screenHeight 800

namespace clr
{
    extern Color black;
    extern Color green;
    extern Color red;
    extern Color gray;
}

namespace snd
{
    extern Sound scoringPlayer;
    extern Sound scoringComputer;
    extern Sound bounchBall;
}

#endif