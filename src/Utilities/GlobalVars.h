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

    namespace GlobalVars {
        extern int windowWidth;
        extern int windowHeight;
        extern int infoWidth;

        extern int lvlWidth;
        extern int lvlHeight;

        extern Uint64 currenPTS;
        extern Vector2D cameraPos;
        extern float playerAngle;


        extern std::vector<Level> lvlsInfos;

        extern std::vector<Frame> frames;

        //
        extern bool menuActive;

        extern bool accesDebugMode;
        extern bool drawHitboxes;

        extern float normalizeAngle180(float angle);
        extern float normalizeAngle360(float angle);
        extern float RandomFloat(float min, float max);

        extern bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint);
        extern bool ScreenToWorld(Utils::Vector2D screenPoint, Utils::Vector2D& worldPoint);
        extern bool isCursorInRect(Utils::Vector2D xy, Utils::Vector2D wh);
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
