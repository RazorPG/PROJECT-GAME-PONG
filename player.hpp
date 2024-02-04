#ifndef __PLAYER
#define __PLAYER

#include <raylib.h>

class Player
{
    friend class Ball;

protected:
    Texture2D skin;
    Rectangle frame;
    Vector2 position;
    // Vector2 playerVelocity;
    //  float x, y;
    //  float width, height;
    int speed;
    int score;
    bool goal;

    void limitMovement();

public:
    Player(Vector2, Rectangle, int speed, Texture2D);

    float getXpos();
    float getYPos();
    float getWidth();
    float GetHeight();
    float getScore();
    void setScore(int score);
    void resetScore();
    void draw();
    void update();
    bool isGoal();
};

#endif