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
            //20K and 70K Only
            Opt0_0  = 0,
            //15K and 50K Only
            Opt0_1,
            //30K, 100K, Every 100K
            Opt0_2,
            //20K, 70K, Every 70K
            Opt0_3, // Norm
            //15K, 70K, Every 70K
            Opt0_4,
            //15K, 50K, Every 50K
            Opt0_5,
            //10K, 50K, Every 50K
            Opt0_6,
            None,

            // if Lives set to 5
            //30K, 120K, Every 120K
            Opt1_0,
            //30K, 100K, Every 100K
            Opt1_1,
            //30K, 80K, Every 80K
            Opt1_2,
            //30K and 120K Only
            Opt1_3, // Norm
            //20K and 100K Only
            Opt1_4,
            //20K and 70K Only
            Opt1_5,
            //15K and 70K Only
            Opt1_6,
            None_pl
        };

        enum class Lives
        {
            Five = 0,
            Three, // Norm
            Tow,
            On
        };

        enum class Difficulty
        {
            Medium = 0, // Norm
            Hardest,
            Easy,
            Auto
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

        extern bool swa_0;
        extern bool swa_1;
        extern bool swa_2;
        extern bool swa_3;
        extern bool swa_4;
        extern bool swa_5;
        extern bool swa_6;
        extern bool swa_7;

        extern bool swb_0;
        extern bool swb_1;
        extern bool swb_2;
        extern bool swb_3;
        extern bool swb_4;
        extern bool swb_5;
        extern bool swb_6;
        extern bool swb_7;

        extern void updateSettings();
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
        extern int condition;
        extern std::vector<SDL_Color> conditionColors;

        extern std::vector<Level> lvlsInfos;

        extern std::vector<Frame> frames;

        //
        extern bool menuActive;
        extern bool dipSwitchActive;
        extern bool need2ExitProc;
        extern bool debugMode;

        extern bool lvlEditorActive;

        extern bool accesDebugMode;
        extern bool drawHitboxes;
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
