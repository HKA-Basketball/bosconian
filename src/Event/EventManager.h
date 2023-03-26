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
        unsigned long long oldTCount;
        int inputDelay;

        MouseState mState;
        MouseButton mButton;
        KeyboardState kState[SDL_NUM_SCANCODES];

        SDL_Event event;

    public:
        EventManager();

        bool startLogging();

        // TODO: manage all things where they belong
        void manageGameVars();
        // TODO: add an KeyManager and move it there
        bool isKeyClicked(int iKey, bool clicked = true)
        {
            static bool is_down = false;
            static bool is_clicked = false;

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

    };

} // Event

#endif //BOSCONIAN_EVENTMANAGER_H
