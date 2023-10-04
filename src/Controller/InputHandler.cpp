#include "InputHandler.h"

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                keysPressed.insert(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                keysPressed.erase(event.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                mousePosition.x = event.motion.x;
                mousePosition.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseButtonPressed = true;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseButtonPressed = false;
                }
                break;
        }
    }
}

bool InputHandler::hasQuit() const {
    return quit;
}

void InputHandler::setQuit() {
    quit = true;
}

bool InputHandler::isKeyPressed(SDL_Keycode key) const {
    return keysPressed.find(key) != keysPressed.end();
}

bool InputHandler::isKeyPressedAndErase(SDL_Keycode key) {
    if (isKeyPressed(key)) {
        keysPressed.erase(key);
        return true;
    }

    return false;
}

Vector2D InputHandler::getMousePosition() const {
    return mousePosition;
}

bool InputHandler::isMouseButtonPressed() const {
    return mouseButtonPressed;
}

bool InputHandler::isMouseButtonPressedAndErase() {
    bool wasPressed = mouseButtonPressed;
    mouseButtonPressed = false;
    return wasPressed;
}