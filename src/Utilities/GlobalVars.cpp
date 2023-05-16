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

        int gameWindowWidth = windowWidth;
        int gameWindowHeight = windowHeight;

        int lvlWidth = 2000;
        int lvlHeight = 2000;

        Vector2D cameraPos((lvlWidth / 2), (lvlHeight / 2));
        float playerAngle = 0.f;

        //
        bool accesDebugMode = true;
        bool drawHitboxes = false;

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

        bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint)
        {
            // Wrap the world coordinates around the edges of the screen
            while (worldPoint.x < Utils::GlobalVars::cameraPos.x - Utils::GlobalVars::lvlWidth / 2) {
                worldPoint.x += Utils::GlobalVars::lvlWidth;
            }
            while (worldPoint.x > Utils::GlobalVars::cameraPos.x + Utils::GlobalVars::lvlWidth / 2) {
                worldPoint.x -= Utils::GlobalVars::lvlWidth;
            }
            while (worldPoint.y < Utils::GlobalVars::cameraPos.y - Utils::GlobalVars::lvlHeight / 2) {
                worldPoint.y += Utils::GlobalVars::lvlHeight;
            }
            while (worldPoint.y > Utils::GlobalVars::cameraPos.y + Utils::GlobalVars::lvlHeight / 2) {
                worldPoint.y -= Utils::GlobalVars::lvlHeight;
            }

            // Calculate the screen coordinates of the wrapped world point
            screenPoint.x = worldPoint.x - Utils::GlobalVars::cameraPos.x + Utils::GlobalVars::gameWindowWidth / 2;
            screenPoint.y = worldPoint.y - Utils::GlobalVars::cameraPos.y + Utils::GlobalVars::gameWindowHeight / 2;

            // Check if the point is within the bounds of the screen
            if (screenPoint.x < 0 || screenPoint.x >= Utils::GlobalVars::gameWindowWidth || screenPoint.y < 0 || screenPoint.y >= Utils::GlobalVars::gameWindowHeight)
            {
                return false;
            }

            return true;
        }

        bool ScreenToWorld(Utils::Vector2D screenPoint, Utils::Vector2D& worldPoint)
        {
            // Check if the point is within the bounds of the screen
            if (screenPoint.x < 0 || screenPoint.x >= Utils::GlobalVars::gameWindowWidth || screenPoint.y < 0 || screenPoint.y >= Utils::GlobalVars::gameWindowHeight)
            {
                return false;
            }

            // Calculate the world coordinates of the screen point
            worldPoint.x = screenPoint.x - Utils::GlobalVars::gameWindowWidth / 2 + Utils::GlobalVars::cameraPos.x;
            worldPoint.y = screenPoint.y - Utils::GlobalVars::gameWindowHeight / 2 + Utils::GlobalVars::cameraPos.y;

            return true;
        }

        bool isCursorInRect(Utils::Vector2D xy, Utils::Vector2D wh) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Rect p = {x, y};
            return ( (p.x >= xy.x) && (p.x < (xy.x + wh.x)) && (p.y >= xy.y) && (p.y < (xy.y + wh.y)) );
        }

        std::vector<Frame> frames = {
                {
                        "E-Type",
                        {0, 0, 28, 64}
                },
                {
                        "I-Type-attack",
                        {0, 64, 56, 56}
                },
                {
                        "I-Type-norm",
                        {0, 120, 56, 56}
                },
                {
                        "P-Type-attack",
                        {0, 176, 52, 48}
                },
                {
                        "P-Type-norm",
                        {0, 224, 52, 48}
                },
                {
                        "astro-explo-01",
                        {0, 272, 56, 60}
                },
                {
                        "astro-explo-02",
                        {0, 332, 64, 60}
                },
                {
                        "astro-explo-03",
                        {0, 392, 64, 64}
                },
                {
                        "astroid-01",
                        {0, 456, 56, 44}
                },
                {
                        "astroid-02",
                        {0, 500, 48, 40}
                },
                {
                        "astroid-03",
                        {0, 540, 52, 44}
                },
                {
                        "base",
                        {0, 584, 288, 256}
                },
                {
                        "bomb",
                        {0, 840, 60, 60}
                },
                {
                        "ship",
                        {0, 900, 60, 64}
                },
                {
                        "spy",
                        {0, 964, 44, 52}
                }
                // ... add more here
        };
    };


} // Utils