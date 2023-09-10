#include "InputHandler.h"

InputHandler::InputHandler() {
    // Initialize the keyboard state to the current state of the keyboard
    keyboardState = SDL_GetKeyboardState(NULL);
}

void InputHandler::update() {
    // Update the keyboard state
    SDL_PumpEvents();
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    return keyboardState[key];
}
