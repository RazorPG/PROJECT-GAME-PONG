#include <raylib.h>
#include <iostream>
#include "ball.hpp"
#include "global.hpp"

Ball::Ball(float x, float y, int radius, int speedX, int speedY)
{
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedY = speedY;
    this->radius = radius;
}

void Ball::setSpeedX(int speedX)
{
    this->speedX = speedX;
}

float Ball::getSpeedX()
{
    return this->speedX;
}

float Ball::getYPos()
{
    return this->y;
}
float Ball::getXpos()
{
    return this->x;
}

float Ball::getRadius()
{
    return this->radius;
}

void Ball::draw()
{
    DrawCircle(x, y, radius, WHITE);
}

void Ball::update(Player &obj1, Computer &obj2)
{
    x += speedX;
    y += speedY;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        PlaySound(snd::bounchBall);
        speedY *= -1;
    }
    else if (x + radius >= GetScreenWidth())
    {
        obj1.setScore(1);
        std::cout << "score player 1: " << obj1.getScore() << std::endl;
        PlaySound(snd::scoringPlayer);
        resetBall(obj1, obj2);
    }
    else if (x - radius <= 0)
    {
        obj2.setScore(1);
        PlaySound(snd::scoringComputer);
        std::cout << "score player 2: " << obj2.getScore() << std::endl;
        resetBall(obj1, obj2);
    }
}

void Ball::resetBall(Player &obj1, Computer &obj2)
{
    if (obj1.isGoal() == true)
    {
        speedX *= -1;
        std::cout << "player 1 goal" << std::endl;
        x = obj2.getXpos() - getRadius() - 2;
        y = obj2.getYPos() + obj2.GetHeight() / 2;
    }
    else if (obj2.isGoal() == true)
    {
        speedX *= 1;
        std::cout << "player 2 goal" << std::endl;
        x = obj1.getXpos() + obj1.getWidth() + getRadius();
        y = obj1.getYPos() + obj1.GetHeight() / 2;
    }

    int speedChoices[2] = {-1, 1};
    speedY *= speedChoices[GetRandomValue(0, 1)];
}