#ifndef BOSCONIAN_INPUTHANDLER_H
#define BOSCONIAN_INPUTHANDLER_H

#include <SDL.h>
#include <unordered_set>

#include "../Utilities/Vector2D.h"

/**
 * @class InputHandler
 * @brief Handles user input from keyboard and mouse.
 *
 * This class captures and stores the state of keyboard keys, mouse position, and mouse buttons.
 * It provides methods to check for specific key presses, mouse button presses, and retrieve the
 * current mouse position.
 */
class InputHandler {
private:
    bool quit{false};                                     ///< Flag to indicate if application should quit.
    std::unordered_set<SDL_Keycode> keysPressed;          ///< Set of currently pressed keys.
    Vector2D mousePosition;                               ///< Current position of the mouse.
    bool mouseButtonPressed{false};                       ///< State of the left mouse button.

public:
    /**
     * @brief Default constructor.
     */
    InputHandler() = default;

    /**
     * @brief Default destructor.
     */
    ~InputHandler() = default;

    /**
     * @brief Polls and processes pending SDL events.
     */
    void update();

    /**
     * @brief Checks if a quit event has occurred.
     * @return True if a quit event has occurred, otherwise false.
     */
    bool hasQuit() const;

    /**
     * @brief Sets the quit flag to true.
     */
    void setQuit();

    /**
     * @brief Checks if a specific key is currently pressed.
     * @param key The key to check.
     * @return True if the key is pressed, otherwise false.
     */
    bool isKeyPressed(SDL_Keycode key) const;

    /**
     * @brief Checks if a specific key is pressed and removes it from the set.
     * @param key The key to check.
     * @return True if the key was pressed, otherwise false.
     */
    bool isKeyPressedAndErase(SDL_Keycode key);

    /**
     * @brief Retrieves the current mouse position.
     * @return The current mouse position as a Vector2D.
     */
    Vector2D getMousePosition() const;

    /**
     * @brief Checks if the left mouse button is pressed.
     * @return True if the left mouse button is pressed, otherwise false.
     */
    bool isMouseButtonPressed() const;

    /**
     * @brief Checks if the left mouse button was pressed and resets its state.
     * @return True if the left mouse button was pressed, otherwise false.
     */
    bool isMouseButtonPressedAndErase();
};

#endif //BOSCONIAN_INPUTHANDLER_H
