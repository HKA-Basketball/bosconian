#ifndef BOSCONIAN_GLOBALVARS_H
#define BOSCONIAN_GLOBALVARS_H

#include "Vector2D.h"
#include <SDL.h>
#include <string>
#include <vector>

namespace Utils {
    // Represents a frame of an animation or image.
    struct Frame {
        std::string filename;   // The filename of the image associated with this frame.
        struct {
            int x, y, w, h;     // The coordinates and dimensions of the frame within the image.
        } frame;                // Information about the frame's position and size.
    };

    // Represents information about a game level.
    struct Level {
        int lvlNum;                         // The level number.
        std::vector<Vector2D> baseShipsPos; // Positions of base ships in the level.
        Vector2D playerPos;                 // Position of the player in the level.
    };

    namespace PlayOptions {
        // Coinage options for gameplay
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

        // Bonus fighter options for gameplay
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

        // Starting lives options
        enum class Lives
        {
            On = 1,
            Tow,
            Three, // Norm
            Five = 5
        };

        // Difficulty options
        enum class Difficulty
        {
            Medium = 0, // Norm
            Hardest,
            Easy,
            Auto
        };

        // Cabinet type options
        enum class Cabinet
        {
            Cocktail = 0,
            Upright // Norm & Only Supported
        };

        // Gameplay settings
        extern Coinage conage;
        extern BonusFighter bonusFighter;
        extern Lives lives;
        extern Difficulty difficulty;
        extern bool allowContinue;
        extern bool demoSound;
        extern bool freeze;
        extern Cabinet cabinet;

        // Maximum number of spies
        extern int maxSpy;

        // Switch settings (A)
        extern bool swa_0;
        extern bool swa_1;
        extern bool swa_2;
        extern bool swa_3;
        extern bool swa_4;
        extern bool swa_5;
        extern bool swa_6;
        extern bool swa_7;

        // Switch settings (B)
        extern bool swb_0;
        extern bool swb_1;
        extern bool swb_2;
        extern bool swb_3;
        extern bool swb_4;
        extern bool swb_5;
        extern bool swb_6;
        extern bool swb_7;

        extern Lives GetLivesFromBits(int bits);

        // Function to update gameplay settings
        extern void updateSettings();
    }

    namespace Math {
        /**
         * Normalizes an angle in degrees to the range [-180, 180].
         * \param angle The angle to normalize.
         * \return The normalized angle.
         */
        extern float normalizeAngle180(float angle);

        /**
         * Normalizes an angle in degrees to the range [0, 360].
         * \param angle The angle to normalize.
         * \return The normalized angle.
         */
        extern float normalizeAngle360(float angle);

        /**
         * Generates a random floating-point number within the specified range.
         * \param min The minimum value of the range.
         * \param max The maximum value of the range.
         * \return The random number generated.
         */
        extern float RandomFloat(float min, float max);

        /**
         * Checks if two SDL_Rectangles intersect.
         * \param rect1 The first rectangle.
         * \param rect2 The second rectangle.
         * \return True if the rectangles intersect, false otherwise.
         */
        extern bool rectIntersect(SDL_Rect rect1, SDL_Rect rect2);

        /**
         * Wraps the position of a Vector2D object, ensuring it stays within certain bounds.
         * \param newPosition Pointer to the new position vector to be wrapped.
         */
        extern void wrapPos(Vector2D* newPosition);
    }

    namespace render {
        /**
         * Converts a world point to its corresponding screen point.
         * \param worldPoint The point in world coordinates.
         * \param screenPoint The corresponding point in screen coordinates (output parameter).
         * \return True if the conversion was successful, false otherwise.
         */
        extern bool WorldToScreen(Utils::Vector2D worldPoint, Utils::Vector2D& screenPoint);

        /**
         * Converts a screen point to its corresponding world point.
         * \param screenPoint The point in screen coordinates.
         * \param worldPoint The corresponding point in world coordinates (output parameter).
         * \return True if the conversion was successful, false otherwise.
         */
        extern bool ScreenToWorld(Utils::Vector2D screenPoint, Utils::Vector2D& worldPoint);

        /**
         * Checks if the cursor is within a specified rectangle on the screen.
         * \param xy The top-left corner of the rectangle.
         * \param wh The width and height of the rectangle.
         * \return True if the cursor is inside the rectangle, false otherwise.
         */
        extern bool isCursorInRect(Utils::Vector2D xy, Utils::Vector2D wh);

        /**
         * Retrieves frame information for a given frame name.
         * \param name The name of the frame.
         * \return The SDL_Rect containing frame information.
         */
        extern SDL_Rect getFrameInfo(std::string name);
    }

    namespace GlobalVars {
        // Dimensions of the game window and information panel
        extern int windowWidth;
        extern int windowHeight;
        extern int infoWidth;

        // Dimensions of the game level
        extern int lvlWidth;
        extern int lvlHeight;

        // Current player's points and high score
        extern Uint64 currenPTS;
        extern Uint64 currenHiScore;

        // Camera position and player's facing angle
        extern Vector2D cameraPos;
        extern float playerAngle;

        // Game condition state and associated colors
        extern int condition;
        extern std::vector<SDL_Color> conditionColors;

        // Information about game levels
        extern std::vector<Level> lvlsInfos;

        // Information about frames for rendering
        extern std::vector<Frame> frames;

        // Various control and configuration flags
        extern bool menuActive;         // Is the menu active?
        extern bool dipSwitchActive;    // Is the dip switch active?
        extern bool need2ExitProc;      // Is there a need to exit the process?
        extern bool debugMode;          // Is the debug mode enabled?

        // Level editor mode and debugging flags
        extern bool lvlEditorActive;    // Is the level editor active?
        extern bool accesDebugMode;     // Is access to debug mode allowed?
        extern bool drawHitboxes;       // Should hitboxes be drawn?
    };



} // Utils

#endif //BOSCONIAN_GLOBALVARS_H
