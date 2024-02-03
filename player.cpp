#include <raylib.h>
#include <iostream>
#include "player.hpp"

void Player::limitMovement()
{
    if (y <= 0)
    {
        y = 0;
    }
    else if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
}

Player::Player(float x, float y, float width, float height, int speed)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
    this->goal = false;
    this->score = 0;
}

float Player::getXpos()
{
    return this->x;
}
float Player::getYPos()
{
    return this->y;
}

float Player::getWidth()
{
    return this->width;
}

float Player::GetHeight()
{
    return this->height;
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

void Player::draw()
{
    DrawRectangle(x, y, width, height, WHITE);
}

void Player::update()
{
    if (IsKeyDown(KEY_W))
    {
        y -= speed;
    }
    else if (IsKeyDown(KEY_S))
    {
        y += speed;
    }
    limitMovement();
    goal = false;
}

bool Player::isGoal()
{
    return goal;
}
