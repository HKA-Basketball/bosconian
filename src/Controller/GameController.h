#ifndef BOSCONIAN_GAMECONTROLLER_H
#define BOSCONIAN_GAMECONTROLLER_H

#include "../View/RenderEngine.h"
#include "../Sound/SoundEngine.h"
#include "../Controller/InputHandler.h"
#include "../States/StateMachine.h"
#include "../Utilities/FrameTimer.h"
#include "../Utilities/Settings.h"

#include "../Model/GameModel.h"
#include "../Model/LevelEditorModel.h"
#include "../View/GameView.h"
#include "../View/LevelEditorView.h"

/**
 * @class GameController
 * @brief Main controller class for the game.
 *
 * This class initializes, controls, and updates the main components of the game, such as rendering,
 * sound, input, states, and timing. It also serves as the main game loop driver.
 */
class GameController {
    RenderEngine* renderEngine;       ///< The rendering engine.
    SoundEngine* soundEngine;         ///< The sound engine.
    InputHandler* inputHandler;       ///< Input handler for player's actions.
    StateMachine* stateMachine;      ///< The state machine for game states.
    FrameTimer* frameTimer;           ///< Timer to control frame rates.

    bool levelEditor{false};          ///< Flag to determine if level editor mode is active.

    GameModel* gameModel{nullptr};    ///< Model representing game's state.
    GameView* gameView{nullptr};      ///< View for the game model.

    LevelEditorModel* levelEditorModel{nullptr};   ///< Model for level editor.
    LevelEditorView* levelEditorView{nullptr};     ///< View for the level editor model.

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the main game components and engines.
     */
    GameController();

    /**
     * @brief Destructor.
     *
     * Cleans up dynamically allocated resources.
     */
    ~GameController();

    /**
     * @brief Starts the main game loop.
     */
    void start();

private:
    /**
     * @brief Main game loop method.
     *
     * This method updates the input, state, and rendering each frame.
     */
    void loop();

    /**
     * @brief Updates the current game state.
     *
     * Checks for state changes and transitions to new states when necessary.
     */
    void updateState();
};


#endif //BOSCONIAN_GAMECONTROLLER_H
