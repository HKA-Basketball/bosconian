#include "GlobalVars.h"

namespace Utils {
    namespace Math {

        // TODO: Move this to a math class or something
        float normalizeAngle180(float angle)
        {
            angle = fmod(angle, 360.0);
            if (angle > 180.0) {
                angle -= 360.0;
            }
            return angle;
        }

        float normalizeAngle360(float angle)
        {
            angle = fmod(angle, 360.0);
            return angle;
        }

        // TODO: move to Math
        float RandomFloat(float min, float max)
        {
            float random = ((float)rand()) / (float)RAND_MAX;

            float range = max - min;
            return (random * range) + min;
        }

        bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2)
        {
            // Check if the bounding boxes of the two intersect
            return (rect1.x < rect2.x + rect2.w &&
                    rect1.x + rect1.w > rect2.x &&
                    rect1.y < rect2.y + rect2.h &&
                    rect1.y + rect1.h > rect2.y);
        }
    }

    namespace render {

        bool WorldToScreen(Vector2D worldPoint, Vector2D& screenPoint)
        {
            // Wrap the world coordinates around the edges of the screen
            while (worldPoint.x < GlobalVars::cameraPos.x - GlobalVars::lvlWidth / 2) {
                worldPoint.x += GlobalVars::lvlWidth;
            }
            while (worldPoint.x > GlobalVars::cameraPos.x + GlobalVars::lvlWidth / 2) {
                worldPoint.x -= GlobalVars::lvlWidth;
            }
            while (worldPoint.y < GlobalVars::cameraPos.y - GlobalVars::lvlHeight / 2) {
                worldPoint.y += GlobalVars::lvlHeight;
            }
            while (worldPoint.y > GlobalVars::cameraPos.y + GlobalVars::lvlHeight / 2) {
                worldPoint.y -= GlobalVars::lvlHeight;
            }

            // Calculate the screen coordinates of the wrapped world point
            screenPoint.x = worldPoint.x - GlobalVars::cameraPos.x + GlobalVars::windowWidth / 2;
            screenPoint.y = worldPoint.y - GlobalVars::cameraPos.y + GlobalVars::windowHeight / 2;

            // Check if the point is within the bounds of the screen
            if (screenPoint.x < 0 || screenPoint.x >= GlobalVars::windowWidth || screenPoint.y < 0 || screenPoint.y >= GlobalVars::windowHeight)
            {
                return false;
            }

            return true;
        }

        bool ScreenToWorld(Vector2D screenPoint, Vector2D& worldPoint)
        {
            // Check if the point is within the bounds of the screen
            if (screenPoint.x < 0 || screenPoint.x >= GlobalVars::windowWidth || screenPoint.y < 0 || screenPoint.y >= GlobalVars::windowHeight)
            {
                return false;
            }

            // Calculate the world coordinates of the screen point
            worldPoint.x = screenPoint.x - GlobalVars::windowWidth / 2 + GlobalVars::cameraPos.x;
            worldPoint.y = screenPoint.y - GlobalVars::windowHeight / 2 + GlobalVars::cameraPos.y;

            return true;
        }

        bool isCursorInRect(Vector2D xy, Vector2D wh) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Rect p = {x, y};
            return ( (p.x >= xy.x) && (p.x < (xy.x + wh.x)) && (p.y >= xy.y) && (p.y < (xy.y + wh.y)) );
        }
    }

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

        Uint64 currenPTS = 0;
        Uint64 currenHiScore = 0;
        Vector2D cameraPos((lvlWidth / 2), (lvlHeight / 2));
        float playerAngle = 0.f;

        std::vector<Level> lvlsInfos;

        //
        bool menuActive = false;

        bool accesDebugMode = false;
        bool drawHitboxes = false;

        std::vector<Frame> frames;
    };


} // Utils