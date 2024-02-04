#include <raylib.h>
#include "computer.hpp"
#include "global.hpp"

Computer::Computer(Vector2 position, Rectangle frame, int speed, Texture2D skin) : Player(position, frame, speed, skin)
{
    this->goal = false;
    this->score = 0;
}

void Computer::update(Ball &obj)
{
    if (this->position.y + frame.height / 2 > obj.getYPos())
    {
        this->position.y -= speed;
    }

    else if (this->position.y + frame.height / 2 < obj.getYPos())
    {
        this->position.y += speed;
    }
    limitMovement();
}

void Computer::draw()
{
    DrawTextureRec(this->skin, this->frame, this->position, clr::red);
}