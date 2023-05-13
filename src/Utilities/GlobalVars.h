#ifndef BOSCONIAN_GLOBALVARS_H
#define BOSCONIAN_GLOBALVARS_H

#include "Vector2D.h"

namespace Utils {
    namespace GlobalVars {
        extern int windowWidth;
        extern int windowHeight;
        extern int infoWidth;

        extern int gameWindowWidth;
        extern int gameWindowHeight;

        extern int lvlWidth;
        extern int lvlHeight;

        extern Vector2D cameraPos;
        extern float playerAngle;

        //
        extern bool accesDebugMode;
        extern bool drawHitboxes;

        extern bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint);
        extern bool ScreenToWorld(Utils::Vector2D screenPoint, Utils::Vector2D& worldPoint);
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
