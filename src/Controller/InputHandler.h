#ifndef BOSCONIAN_INPUTHANDLER_H
#define BOSCONIAN_INPUTHANDLER_H

#include <SDL.h>

class InputHandler {
private:
    const Uint8* keyboardState; // State of the keyboard

public:
    InputHandler();
    void update(); // Capture the current state of input devices

    bool isKeyDown(SDL_Scancode key) const; // Check if a particular key is down
};

#endif //BOSCONIAN_INPUTHANDLER_H
