#ifndef __COMPUTER
#define __COMPUTER

#include <raylib.h>
#include "player.hpp"
#include "ball.hpp"

class Ball;

class Computer : public Player
{
public:
    Computer(Vector2 position, Rectangle frame, int speed, Texture2D skin);
    void update(Ball &obj);
    void draw();
};

#endif