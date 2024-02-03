#ifndef __COMPUTER
#define __COMPUTER

#include "player.hpp"
#include "ball.hpp"

class Ball;

class Computer : public Player
{
public:
    Computer(float x, float y, float width, float height, int speed);
    void update(Ball &obj);
};

#endif