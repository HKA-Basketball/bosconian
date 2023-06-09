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
        EventManager();

        bool logging();

        // TODO: manage all things where they belong
        void manageGameVars(float deltaTime);
        // TODO: add an KeyManager and move it there
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
