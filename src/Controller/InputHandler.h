#ifndef BOSCONIAN_INPUTHANDLER_H
#define BOSCONIAN_INPUTHANDLER_H

#include <SDL.h>
#include <unordered_set>

#include "../States/StateMachine.h"
#include "../Utilities/Vector2D.h"

class InputHandler {
private:
    static InputHandler* instance;

    std::unordered_set<SDL_Keycode> keysPressed;
    Vector2D mousePosition;
    bool mouseButtonPressed;

    // Private constructor and destructor to prevent instantiation
    InputHandler() = default;
    ~InputHandler() = default;

    // Private copy constructor and assignment operator to prevent copying
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;


public:
    // Public method to get the singleton instance
    static InputHandler* Instance() {
        if (!instance) {
            instance = new InputHandler();
        }
        return instance;
    }

    static void DestroyInstance() {
        delete instance;
        instance = nullptr;
    }

    void update();
    bool isKeyPressed(SDL_Keycode key) const;
    bool isKeyPressedAndErase(SDL_Keycode key);
    Vector2D getMousePosition() const;
    bool isMouseButtonPressed() const;
};

#endif //BOSCONIAN_INPUTHANDLER_H
