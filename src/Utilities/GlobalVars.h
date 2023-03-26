#ifndef BOSCONIAN_GLOBALVARS_H
#define BOSCONIAN_GLOBALVARS_H

#include "Vector2D.h"

namespace Utils {
    namespace GlobalVars {
        extern int windowWidth;
        extern int windowHeight;
        extern int infoWidth;

        extern int lvlWidth;
        extern int lvlHeight;

        extern Vector2D playerPos;
        extern float playerAngle;

        //
        extern bool accesDebugMode;
        extern bool drawHitboxes;
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
