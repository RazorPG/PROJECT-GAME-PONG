#include <raylib.h>
#include <iostream>

#include "ball.hpp"
#include "player.hpp"
#include "computer.hpp"
#include "global.hpp"

#define screenWidth 1280
#define screenHeight 800

int main()
{
    std::cout << "starting the game" << std::endl;
    InitWindow(screenWidth, screenHeight, "GAME PONG BY ME");
    InitAudioDevice();

    Ball *ball = new Ball(screenWidth / 2, screenHeight / 2, 20, 11, 13);
    Player *player = new Player(20, screenHeight / 2 - 60, 25, 120, 10);
    Computer *computer = new Computer(screenWidth - 45, screenHeight / 2 - 60, 25, 120, 10);

    Music backsound = LoadMusicStream("music/11._jester_battle.mp3");
    snd::bounchBall = LoadSound("music/tennis-ball-hit-151257.mp3");
    snd::scoringPlayer = LoadSound("music/score-sound-effect.mp3");
    snd::scoringComputer = LoadSound("music/sound-effect-rugi-dong.mp3");

    backsound.looping = true;
    PlayMusicStream(backsound);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        // music
        UpdateMusicStream(backsound);
        if (!IsMusicStreamPlaying(backsound))
        {
            backsound.looping = true;
            StopMusicStream(backsound);
            PlayMusicStream(backsound);
        }
        SetMusicVolume(backsound, 0.5f);

        // updating
        ball->update(*player, *computer);
        player->update();
        computer->update(*ball);

        // check collisions
        if (CheckCollisionCircleRec(Vector2{ball->getXpos(), ball->getYPos()}, ball->getRadius(), Rectangle{player->getXpos(), player->getYPos(), player->getWidth(), player->GetHeight()}))
        {
            PlaySound(snd::bounchBall);
            ball->setSpeedX(ball->getSpeedX() * -1);
        }

        else if (CheckCollisionCircleRec(Vector2{ball->getXpos(), ball->getYPos()}, ball->getRadius(), Rectangle{computer->getXpos(), computer->getYPos(), computer->getWidth(), computer->GetHeight()}))
        {
            PlaySound(snd::bounchBall);
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

    UnloadMusicStream(backsound);
    CloseAudioDevice();
    CloseWindow();

    delete ball;
    delete player;
    delete computer;

    return 0;
}
