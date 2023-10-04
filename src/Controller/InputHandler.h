#ifndef BOSCONIAN_INPUTHANDLER_H
#define BOSCONIAN_INPUTHANDLER_H

#include <SDL.h>
#include <unordered_set>

#include "../Utilities/Vector2D.h"

class InputHandler {
private:
    bool quit{false};
    std::unordered_set<SDL_Keycode> keysPressed;
    Vector2D mousePosition;
    bool mouseButtonPressed;


public:
    InputHandler() = default;
    ~InputHandler() = default;

    void update();
    bool hasQuit() const;
    void setQuit();
    bool isKeyPressed(SDL_Keycode key) const;
    bool isKeyPressedAndErase(SDL_Keycode key);
    Vector2D getMousePosition() const;
    bool isMouseButtonPressed() const;
    bool isMouseButtonPressedAndErase();
};

#endif //BOSCONIAN_INPUTHANDLER_H
