#include <raylib.h>
#include <iostream>
#include "player.hpp"
#include "global.hpp"

void Player::limitMovement()
{
    if (position.y <= 0)
    {
        position.y = 0;
    }
    else if (position.y + frame.height >= GetScreenHeight())
    {
        position.y = GetScreenHeight() - frame.height;
    }
}

Player::Player(Vector2 position, Rectangle frame, int speed, Texture2D skin)
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->frame.width = frame.width;
    this->frame.height = frame.height;
    this->frame.x = 0;
    this->frame.y = 0;
    this->skin = skin;
    this->speed = speed;
    this->goal = false;
    this->score = 0;
}

float Player::getXpos()
{
    return this->position.x;
}
float Player::getYPos()
{
    return this->position.y;
}

float Player::getWidth()
{
    return this->frame.width;
}

float Player::GetHeight()
{
    return this->frame.height;
}

float Player::getScore()
{
    return this->score;
}

void Player::setScore(int score)
{
    goal = true;
    this->score += score;
}

void Player::resetScore()
{
    this->score = 0;
}

void Player::draw()
{
    DrawTextureRec(this->skin, this->frame, this->position, clr::green);
}

void Player::update()
{
    if (IsKeyDown(KEY_W))
    {
        this->position.y -= speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        this->position.y += speed;
    }
    limitMovement();
    goal = false;
}

bool Player::isGoal()
{
    return goal;
}
