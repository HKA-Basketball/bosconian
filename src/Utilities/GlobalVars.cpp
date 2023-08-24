#include <array>
#include <iostream>
#include "GlobalVars.h"

namespace Utils {
    namespace PlayOptions {
        Coinage conage = Coinage::One_One;
        BonusFighter bonusFighter = BonusFighter::Opt0_3;
        Lives lives = Lives::Three;
        Difficulty difficulty = Difficulty::Medium;
        bool allowContinue = true;
        bool demoSound = true;
        bool freeze = false;
        Cabinet cabinet = Cabinet::Upright;

        int maxSpy = 1;

        // Mehh ik
        bool swa_0 = 0;
        bool swa_1 = 0;
        bool swa_2 = 0;
        bool swa_3 = 1;
        bool swa_4 = 1;
        bool swa_5 = 0;
        bool swa_6 = 1;
        bool swa_7 = 0;

        bool swb_0 = 0;
        bool swb_1 = 0;
        bool swb_2 = 0;
        bool swb_3 = 1;
        bool swb_4 = 0;
        bool swb_5 = 0; // not used
        bool swb_6 = 0; // not used
        bool swb_7 = 0;

        Lives GetLivesFromBits(int bits) {
            switch (bits) {
                case 0b00: return Lives::Five;
                case 0b11: return Lives::On;
                case 0b10: return Lives::Tow;
                case 0b01: return Lives::Three;
                default: return Lives::Three; // Default to Three
            }
        }

        void updateSettings() {
            int swa = (swa_7 << 7) | (swa_6 << 6) | (swa_5 << 5) | (swa_4 << 4) | (swa_3 << 3) | (swa_2 << 2) | (swa_1 << 1) | swa_0;

            // Update lives based on swa_6 and swa_7
            lives = GetLivesFromBits((swa >> 6) & 0x03);

            // Update conage based on swa_0, swa_1, and swa_2
            conage = static_cast<Coinage>((swa >> 0) & 0x07);

            // Update bonusFighter based on swa_3 to swa_5 and lives
            if (lives != Lives::Five) {
                bonusFighter = static_cast<BonusFighter>((swa >> 3) & 0x07);
            } else {
                bonusFighter = static_cast<BonusFighter>(8 + ((swa >> 3) & 0x07));
            }

            int swb = (swb_1 << 1) | swb_0;
            difficulty = static_cast<Difficulty>(swb);

            allowContinue = swb_2;
            demoSound = swb_3;
            freeze = swb_4;
            cabinet = static_cast<Cabinet>(swb_7);
        }
    }

    namespace Math {
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
            angle = fmod(angle, 360.0f);
            if (angle < 0) {
                angle += 360.0f;
            }
            return angle;
        }

        float RandomFloat(float min, float max)
        {
            float random = ((float)rand()) / (float)RAND_MAX;

            float range = max - min;
            return (random * range) + min;
        }

        // Check if the bounding boxes of the two intersect
        bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2) {
            if (rect1.x + rect1.w < rect2.x ||
                rect2.x + rect2.w < rect1.x) {
                return false; // No horizontal overlap
            }

            if (rect1.y + rect1.h < rect2.y ||
                rect2.y + rect2.h < rect1.y) {
                return false; // No vertical overlap
            }

            return true; // Intersection
        }

        void wrapPos(Vector2D* newPosition) {
            // Wrap the position around the map edges
            while (newPosition->x < Utils::GlobalVars::cameraPos.x - Utils::GlobalVars::lvlWidth / 2) {
                newPosition->x += Utils::GlobalVars::lvlWidth;
            }
            while (newPosition->x > Utils::GlobalVars::cameraPos.x + Utils::GlobalVars::lvlWidth / 2) {
                newPosition->x -= Utils::GlobalVars::lvlWidth;
            }
            while (newPosition->y < Utils::GlobalVars::cameraPos.y - Utils::GlobalVars::lvlHeight / 2) {
                newPosition->y += Utils::GlobalVars::lvlHeight;
            }
            while (newPosition->y > Utils::GlobalVars::cameraPos.y + Utils::GlobalVars::lvlHeight / 2) {
                newPosition->y -= Utils::GlobalVars::lvlHeight;
            }
        }
    }

    namespace render {

        bool WorldToScreen(Vector2D worldPoint, Vector2D& screenPoint)
        {
            Math::wrapPos(&worldPoint);

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

        SDL_Rect getFrameInfo(std::string name) {
            SDL_Rect out;
            for (const auto& frame : Utils::GlobalVars::frames) {
                if (!frame.filename.compare(name)) {
                    out.w = frame.frame.w;
                    out.h = frame.frame.h;
                    out.x = frame.frame.x;
                    out.y = frame.frame.y;
                    return out;
                }
            }
            return out;
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

        int lvlWidth = 3000;
        int lvlHeight = 4000;

        Uint64 currenPTS = 0;
        Uint64 currenHiScore = 0;
        Vector2D cameraPos((lvlWidth / 2), (lvlHeight / 2));
        float playerAngle = 0.f;
        int condition = 0;
        std::vector<SDL_Color> conditionColors = {
                {0, 255, 0, 255},
                {255, 255, 0, 255},
                {255, 0, 0, 255}
        };

        std::vector<Level> lvlsInfos;

        //
        bool menuActive = true;
        bool dipSwitchActive = false;
        bool need2ExitProc = false;
        bool debugMode = false;

        bool lvlEditorActive = false;

        bool accesDebugMode = false;
        bool drawHitboxes = false;

        std::vector<Frame> frames;
    };


} // Utils