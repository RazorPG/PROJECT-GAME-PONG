#include <raylib.h>
#include "global.hpp"

namespace clr
{
    Color black = Color{45, 45, 45, 255};
    Color green = Color{122, 244, 221, 255};
    Color red = Color{244, 49, 91, 255};
    Color gray = Color{137, 137, 137, 255};
    Color grayLinght = Color{137, 137, 137, 50};
}

namespace snd
{
    Sound scoringPlayer = LoadSound("music/score-sound-effect.mp3");
    Sound scoringComputer = LoadSound("music/sound-effect-rugi-dong.mp3");
    Sound bounchBall = LoadSound("music/tennis-ball-hit-151257.mp3");
    Sound lose = LoadSound("music/spongebob-fail.mp3");
    Sound win = LoadSound("music/ta-da_yrvBrlS.mp3");
    Sound lounch = LoadSound("music/pew_pew-dknight556-1379997159.mp3");
    Sound click = LoadSound("music/button-124476.mp3");
}

// namespace img
// {
//     Texture2D skin = LoadTexture("image/paddle.png");
// }
