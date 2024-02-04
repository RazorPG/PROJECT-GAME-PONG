#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "ball.hpp"
#include "player.hpp"
#include "computer.hpp"
#include "global.hpp"

#define screenWidth 1280
#define screenHeight 800

bool CheckButtonPressed(Rectangle buttonRect);

int main()
{
    std::cout << "starting the game" << std::endl;
    InitWindow(screenWidth, screenHeight, "GAME PONG");
    InitAudioDevice();

    bool startMenu = true;
    bool paused = false;
    bool gameover = false;

    Texture2D skin1 = LoadTexture("image/paddleP1.png");
    Texture2D skin2 = LoadTexture("image/paddle.png");
    Texture2D backgroundMenu = LoadTexture("image/backgroundGame.png");

    Ball *ball = new Ball(screenWidth / 2, screenHeight / 2, 20, 11, 12);
    Player *player = new Player(Vector2{20, screenHeight / 2 - 60}, Rectangle{0, 0, 25, 120}, 10, skin1);
    Computer *computer = new Computer(Vector2{screenWidth - 45, screenHeight / 2}, Rectangle{0, 0, 25, 120}, 10, skin2);

    Music backsound = LoadMusicStream("music/11._jester_battle.mp3");
    Music soundMenu = LoadMusicStream("music/ytmp3free.cc_napking-legenda-birjon-instrumental-youtubemp3free.org.mp3");
    snd::bounchBall = LoadSound("music/tennis-ball-hit-151257.mp3");
    snd::scoringPlayer = LoadSound("music/score-sound-effect.mp3");
    snd::scoringComputer = LoadSound("music/sound-effect-rugi-dong.mp3");
    snd::lose = LoadSound("music/spongebob-fail.mp3");
    snd::win = LoadSound("music/ta-da_yrvBrlS.mp3");
    snd::lounch = LoadSound("music/pew_pew-dknight556-1379997159.mp3");
    snd::click = LoadSound("music/button-124476.mp3");

    Rectangle startButtonRect = {screenWidth / 2 - 200, screenHeight / 2 + 40, 400, 60};
    Rectangle exitButtonRect = {screenWidth / 2 - 200, screenHeight / 2 + 120, 400, 60};

    Rectangle retryButtonRect = {screenWidth / 2 - 200, screenHeight / 2 + 40, 400, 60};
    Rectangle quitButtonRect = {screenWidth / 2 - 200, screenHeight / 2 + 120, 400, 60};

    Texture2D background = LoadTexture("image/separator.png");

    backsound.looping = true;
    PlayMusicStream(backsound);
    PlayMusicStream(soundMenu);

    bool winSoundPlayed = false;
    bool loseSoundPlayed = false;

    SetTargetFPS(90);
    // game loop
    while (!WindowShouldClose())
    {
        if (startMenu)
        {
            UpdateMusicStream(soundMenu);
            if (!IsMusicStreamPlaying(soundMenu))
            {
                soundMenu.looping = true;
                StopMusicStream(soundMenu);
                PlayMusicStream(soundMenu);
            }
            SetMusicVolume(soundMenu, 0.5f);

            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(backgroundMenu, 0, 0, WHITE);

            DrawText("GAME PONG", screenWidth / 2 - MeasureText("GAME PONG", 40) / 2, 1.5 * screenHeight / 4, 40, GREEN);
            DrawText("credit by @rfd_hlmi08", 3.5 * screenWidth / 4 - MeasureText("credit by @rfd_hlmi08", 20) / 2, screenHeight - 20, 20, WHITE);

            DrawRectangleRec(startButtonRect, WHITE);
            DrawText("Start", screenWidth / 2 - MeasureText("Start", 40) / 2, screenHeight / 2 + 50, 40, BLACK);

            DrawRectangleRec(exitButtonRect, WHITE);
            DrawText("Exit", screenWidth / 2 - MeasureText("Exit", 40) / 2, screenHeight / 2 + 130, 40, BLACK);

            // Button logic for the start menu
            if (CheckButtonPressed(startButtonRect))
            {
                PlaySound(snd::click);
                startMenu = false;
            }
            else if (CheckButtonPressed(exitButtonRect))
            {
                PlaySound(snd::click);
            }

            EndDrawing();
        }

        else
        {
            if (IsKeyPressed(KEY_SPACE) && gameover == false)
            {
                paused = !paused;
            }

            BeginDrawing();

            if (!paused && !gameover)
            {
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
            }

            // Drawing
            ClearBackground(BLACK);
            //  DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, MAGENTA);
            DrawTexture(background, 0, 0, YELLOW);
            ball->draw();
            player->draw();
            computer->draw();

            DrawText(TextFormat("%i", static_cast<int>(player->getScore())), screenWidth / 4 - 20, 20, 80, clr::green);
            DrawText(TextFormat("%i", static_cast<int>(computer->getScore())), 3 * screenWidth / 4 - 20, 20, 80, clr::red);

            // is paused
            if (paused)
            {
                ClearBackground(clr::grayLinght);
                DrawText("PAUSE", screenWidth / 2 - MeasureText("PAUSE", 80) / 2, screenHeight / 2 - 40, 80, WHITE);
            }

            if (player->getScore() == 10 || computer->getScore() == 10)
            {
                if (player->getScore() > computer->getScore() && !winSoundPlayed)
                {
                    PlaySound(snd::win);
                    winSoundPlayed = true;
                }
                else if (player->getScore() < computer->getScore() && !loseSoundPlayed)
                {
                    PlaySound(snd::lose);
                    loseSoundPlayed = true;
                }

                gameover = true;
                if (player->getScore() > computer->getScore())
                {
                    DrawText("PLAYER 1 WIN", screenWidth / 2 - MeasureText("PLAYER 1 WIN", 80) / 2, screenHeight / 2 - 40, 80, WHITE);
                }
                else
                {
                    DrawText("PLAYER 2 WIN", screenWidth / 2 - MeasureText("PLAYER 2 WIN", 80) / 2, screenHeight / 2 - 40, 80, WHITE);
                }

                DrawRectangleRec(retryButtonRect, WHITE);
                DrawText("Retry", screenWidth / 2 - MeasureText("Retry", 40) / 2, screenHeight / 2 + 50, 40, BLACK);

                DrawRectangleRec(quitButtonRect, WHITE);
                DrawText("Quit", screenWidth / 2 - MeasureText("Quit", 40) / 2, screenHeight / 2 + 130, 40, BLACK);
            }

            // Button logic
            if (gameover)
            {
                if (CheckButtonPressed(retryButtonRect))
                {
                    PlaySound(snd::click);
                    // Reset game variables
                    player->resetScore();
                    computer->resetScore();
                    gameover = false;
                }
                else if (CheckButtonPressed(quitButtonRect))
                {
                    PlaySound(snd::click);
                    // Quit the game
                    break;
                }
            }

            DrawFPS(10, 10);
            EndDrawing();
        }
    }
    UnloadMusicStream(backsound);
    CloseAudioDevice();
    CloseWindow();

    delete ball;
    delete player;
    delete computer;

    return 0;
}

bool CheckButtonPressed(Rectangle buttonRect)
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
