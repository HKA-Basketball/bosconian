#ifndef BOSCONIAN_GLOBALVARS_H
#define BOSCONIAN_GLOBALVARS_H

#include "Vector2D.h"
#include <SDL.h>
#include <string>
#include <vector>

namespace Utils {
    struct Frame {
        std::string filename;
        struct {
            int x, y, w, h;
        } frame;
    };

    struct Level {
        int lvlNum;
        std::vector<Vector2D> baseShipsPos;
        Vector2D playerPos;
    };

    namespace PlayOptions {
        enum class Coinage
        {
            One_One = 0, // Norm
            One_Tow,
            One_Three,
            Tow_One,
            Tow_Three,
            Three_One,
            Four_One,
            Free_Play
        };

        enum class BonusFighter
        {
            // if Lives not set to 5
            None = 0,
            Opt0_0,
            Opt0_1,
            Opt0_2,
            Opt0_3,
            Opt0_4,
            Opt0_5, // Norm
            Opt0_6,

            // if Lives set to 5
            Opt1_0,
            Opt1_1,
            Opt1_2,
            Opt1_3, // Norm
            Opt1_4,
            Opt1_5,
            Opt1_6
        };

        enum class Lives
        {
            One = 0,
            Tow,
            Three, // Norm
            Five
        };

        enum class Difficulty
        {
            Auto = 0,
            Easy,
            Hardest,
            Medium  // Norm
        };

        enum class Cabinet
        {
            Cocktail = 0,
            Upright // Norm & Only Supported
        };

        extern Coinage conage;
        extern BonusFighter bonusFighter;
        extern Lives lives;
        extern Difficulty difficulty;
        extern bool allowContinue;
        extern bool demoSound;
        extern bool freeze;
        extern Cabinet cabinet;

        extern int maxSpy;
    }

    namespace Math {
        extern float normalizeAngle180(float angle);
        extern float normalizeAngle360(float angle);
        extern float RandomFloat(float min, float max);
        extern bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2);
        extern void wrapPos(Vector2D* newPosition);
    }

    namespace render {
        extern bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint);
        extern bool ScreenToWorld(Utils::Vector2D screenPoint, Utils::Vector2D& worldPoint);
        extern bool isCursorInRect(Utils::Vector2D xy, Utils::Vector2D wh);
        extern SDL_Rect getFrameInfo(std::string name);
    }

    namespace GlobalVars {
        extern int windowWidth;
        extern int windowHeight;
        extern int infoWidth;

        extern int lvlWidth;
        extern int lvlHeight;

        extern Uint64 currenPTS;
        extern Uint64 currenHiScore;
        extern Vector2D cameraPos;
        extern float playerAngle;


        extern std::vector<Level> lvlsInfos;

        extern std::vector<Frame> frames;

        //
        extern bool menuActive;
        extern bool dipSwitchActive;
        extern bool need2ExitProc;

        extern bool accesDebugMode;
        extern bool drawHitboxes;
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
