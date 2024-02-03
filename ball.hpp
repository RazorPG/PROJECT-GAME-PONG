#ifndef __BALL
#define __BALL

#include "player.hpp"
#include "computer.hpp"

class Computer;

class Ball
{
    friend class Player;
    friend class Computer;

private:
    float x, y;
    int speedX, speedY;
    int radius;

public:
    Ball(float x, float y, int radius, int speedX, int speedY);
    void setSpeedX(int speedX);
    float getSpeedX();
    float getYPos();
    float getXpos();
    float getRadius();
    void draw();
    void update(Player &, Computer &);
    void resetBall(Player &, Computer &);
};

#endif