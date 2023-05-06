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

        int gameWindowWidth = windowWidth - infoWidth;
        int gameWindowHeight = windowHeight;

        int lvlWidth = 2000;
        int lvlHeight = 2000;

        Vector2D playerPos((lvlWidth / 2), (lvlHeight / 2));
        float playerAngle = 0.f;

        //
        bool accesDebugMode = true;
        bool drawHitboxes = false;

        bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint)
        {
            // Calculate the screen coordinates of the world point
            screenPoint.x = (worldPoint.x - Utils::GlobalVars::playerPos.x) + Utils::GlobalVars::gameWindowWidth / 2;
            screenPoint.y = (worldPoint.y - Utils::GlobalVars::playerPos.y) + Utils::GlobalVars::gameWindowHeight / 2;

            // Check if the point is within the bounds of the screen
            if (screenPoint.x < 0 || screenPoint.x >= Utils::GlobalVars::gameWindowWidth || screenPoint.y < 0 || screenPoint.y >= Utils::GlobalVars::gameWindowHeight)
            {
                return false;
            }

            return true;
        }
    };


} // Utils