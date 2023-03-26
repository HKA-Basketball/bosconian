#include "GlobalVars.h"

namespace Utils {
    namespace GlobalVars {
        /*
         Original game size in pixels:
         288x224
         In terms of width, 64 pixels is the width for the info panel
         ==> Level size = 224x224

         Upscaling by a factor of 4
         */
        int windowWidth = 896;   // 224 * 4;
        int windowHeight = 896;  // 224 * 4;
        int infoWidth = 256;    //  64 * 4

        int lvlWidth = 2000;
        int lvlHeight = 2000;

        Vector2D playerPos((lvlWidth / 2), (lvlHeight / 2));
        float playerAngle = 0.f;

        //
        bool accesDebugMode = true;
        bool drawHitboxes = false;
    };


} // Utils