#include <raylib.h>
#include <iostream>

#define screenWidth 1280
#define screenHeight 800

class Ball
{
    friend class Player;
    friend class Computer;

private:
    float x, y;
    int speedX, speedY;
    int radius;

public:
    Ball(float x, float y, int radius, int speedX, int speedY)
    {
        this->x = x;
        this->y = y;
        this->speedX = speedX;
        this->speedY = speedY;
        this->radius = radius;
    }

    void setSpeedX(int speedX)
    {
        this->speedX = speedX;
    }

    float getSpeedX()
    {
        return this->speedX;
    }

    float getYPos()
    {
        return this->y;
    }
    float getXpos()
    {
        return this->x;
    }

    float getRadius()
    {
        return this->radius;
    }

    void draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void update(Player &obj1, Computer &obj2)
    {
        x += speedX;
        y += speedY;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
        else if (x + radius >= GetScreenWidth())
        {
            obj1.incrementScore();
        }
        else if (x - radius <= 0)
        {
            obj1.incrementScore();
        }
    }
};

class Player
{
    friend class Ball;

protected:
    float x, y;
    float width, height;
    int speed;
    int score;

    void limitMovement()
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

public:
    Player(float x, float y, float width, float height, int speed)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->speed = speed;
    }

    float getXpos()
    {
        return this->x;
    }
    float getYPos()
    {
        return this->y;
    }

    float getWidth()
    {
        return this->width;
    }

    float GetHeight()
    {
        return this->height;
    }

    float getScore()
    {
        return this->score;
    }

    void incrementScore()
    {
        this->score++;
    }

    void draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void update()
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
    }
};

class Computer : public Player
{
public:
    Computer(float x, float y, float width, float height, int speed) : Player(x, y, width, height, speed) {}

    void update(Ball &obj)
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
};

int main()
{
    std::cout << "starting the game" << std::endl;
    InitWindow(screenWidth, screenHeight, "GAME PONG BY ME");

    Ball *ball = new Ball(screenWidth / 2, screenHeight / 2, 20, 11, 11);
    Player *player = new Player(screenWidth - 45, screenHeight / 2 - 60, 25, 120, 10);
    Computer *computer = new Computer(20, screenHeight / 2 - 60, 25, 120, 10);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        // updating
        ball->update(*player, *computer);
        player->update();
        computer->update(*ball);

        // check collisions
        if (CheckCollisionCircleRec(Vector2{ball->getXpos(), ball->getYPos()}, ball->getRadius(), Rectangle{player->getXpos(), player->getYPos(), player->getWidth(), player->GetHeight()}))
        {
            ball->setSpeedX(ball->getSpeedX() * -1);
        }

        else if (CheckCollisionCircleRec(Vector2{ball->getXpos(), ball->getYPos()}, ball->getRadius(), Rectangle{computer->getXpos(), computer->getYPos(), computer->getWidth(), computer->GetHeight()}))
        {
            ball->setSpeedX(ball->getSpeedX() * -1);
        }

        // Drawing
        ClearBackground(BLACK);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball->draw();
        player->draw();
        computer->draw();
        DrawText(TextFormat("%i", player->getScore()), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", computer->getScore()), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}