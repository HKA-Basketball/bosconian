#ifndef BOSCONIAN_EVENTMANAGER_H
#define BOSCONIAN_EVENTMANAGER_H

#include "../../includes.h"

namespace Event {

    enum class KeyboardState
    {
        Unknown,
        KeyDown,
        Character,
        KeyUp
    };

    enum class MouseState
    {
        Unknown,
        Move,
        Down,
        Up,
        Scroll
    };

    enum class MouseButton
    {
        None = 0,
        Left,
        Right,
        Middle,
        XButton1,
        XButton2
    };

    class EventManager {
    private:
        MouseState mState;
        MouseButton mButton;
        KeyboardState kState[SDL_NUM_SCANCODES];

        SDL_Event event;

        bool kDown[256] = { false };
        bool kClicked[256] = { false };
        bool mDown[6] = { false };
        bool mClicked[6] = { false };

    public:
        /**
         * Constructor for the EventManager class.
         */
        EventManager();

        /**
         * Check whether event logging is enabled.
         * \return True if event logging is enabled, otherwise false.
         */
        bool logging();

        /**
         * Manage game variables based on the time passed.
         * \param deltaTime Time passed since the last update.
         */
        void manageGameVars(float deltaTime);

        /**
         * Check if a mouse button is clicked.
         * \param button The mouse button to check.
         * \param clicked Flag indicating whether to check for click or down state.
         * \return True if the specified mouse button is clicked or down, otherwise false.
         */
        bool isMouseClicked(int button, bool clicked = true)
        {
            bool& is_down = mDown[button];
            bool& is_clicked = mClicked[button];

            if (mState == MouseState::Down && static_cast<int>(mButton) == button)
            {
                is_clicked = false;
                is_down = true;
            }
            else if (mState == MouseState::Up && is_down && static_cast<int>(mButton) == button)
            {
                is_clicked = true;
                is_down = false;
            }
            else
            {
                is_clicked = false;
                is_down = false;
            }

            if (clicked)
            {
                return is_clicked;
            }
            else
            {
                return is_down;
            }
        }

        /**
         * Check if a keyboard key is clicked.
         * \param iKey The keyboard key to check.
         * \param clicked Flag indicating whether to check for click or down state.
         * \return True if the specified keyboard key is clicked or down, otherwise false.
         */
        bool isKeyClicked(int iKey, bool clicked = true)
        {
            bool& is_down = kDown[iKey];
            bool& is_clicked = kClicked[iKey];

            if (kState[iKey] == KeyboardState::KeyDown)
            {
                is_clicked = false;
                is_down = true;
            }
            else if (kState[iKey] == KeyboardState::KeyUp && is_down)
            {
                is_clicked = true;
                is_down = false;
            }
            else
            {
                is_clicked = false;
                is_down = false;
            }

            if (clicked)
            {
                return is_clicked;
            }
            else
            {
                return is_down;
            }
        }

    }; extern EventManager* g_event;

} // Event

#endif //BOSCONIAN_EVENTMANAGER_H
