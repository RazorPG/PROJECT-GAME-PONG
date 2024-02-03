#include <raylib.h>
#include "computer.hpp"

Computer::Computer(float x, float y, float width, float height, int speed) : Player(x, y, width, height, speed)
{
    this->goal = false;
    this->score = 0;
}

void Computer::update(Ball &obj)
{
    if (y + height / 2 > obj.getYPos())
    {
        y -= speed;
    }

    else if (y + height / 2 < obj.getYPos())
    {
        y += speed;
    }
    limitMovement();
}