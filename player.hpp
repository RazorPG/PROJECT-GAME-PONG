#ifndef __PLAYER
#define __PLAYER

class Player
{
    friend class Ball;

protected:
    float x, y;
    float width, height;
    int speed;
    int score;
    bool goal;

    void limitMovement();

public:
    Player(float x, float y, float width, float height, int speed);

    float getXpos();
    float getYPos();
    float getWidth();
    float GetHeight();
    float getScore();
    void setScore(int score);
    void draw();
    void update();
    bool isGoal();
};

#endif