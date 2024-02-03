#include <raylib.h>
#include <iostream>

#include "ball.hpp"
#include "player.hpp"
#include "computer.hpp"

#define screenWidth 1280
#define screenHeight 800

int main()
{
    std::cout << "starting the game" << std::endl;
    InitWindow(screenWidth, screenHeight, "GAME PONG BY ME");

    Ball *ball = new Ball(screenWidth / 2, screenHeight / 2, 20, 11, 13);
    Player *player = new Player(20, screenHeight / 2 - 60, 25, 120, 10);
    Computer *computer = new Computer(screenWidth - 45, screenHeight / 2 - 60, 25, 120, 10);

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
        DrawText(TextFormat("%i", static_cast<int>(player->getScore())), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", static_cast<int>(computer->getScore())), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    delete ball;
    delete player;
    delete computer;
    CloseWindow();
    return 0;
}