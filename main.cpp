#include <fileapi.h>
#include <functional>

#include "src/Core/GameState.h"
#include "src/Core/StateManager.h"
#include "src/Menu/MainMenu.h"
#include "src/Model/GameSession.h"
#include "src/View/RenderEngine.h"
#include "src/Controller/GameController.h"

int main(int argc, char* args[]) {


    // Initialization code...
    StateManager stateManager;
    MainMenu mainMenu;
    GameSession session;
    RenderEngine view(800, 600);
    GameController controller;


    Uint32 lastFrameTime = SDL_GetTicks();  // Gets the number of milliseconds since the SDL library initialization

    while (controller.isRunning()) {
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = static_cast<float>(currentFrameTime - lastFrameTime) / 1000.0f;  // Dividing by 1000 to convert ms to seconds
        lastFrameTime = currentFrameTime;

        // Handle events and user inputs
        controller.HandleInput();

        // Update game state
        //session.update();

        // Render the game state
        //view.render(session.getGameState());
        view.beginScene();

        // ... (event handling, etc.)

        switch (stateManager.getGameState()) {
            case GameState::MainMenu:
                // Update and render main menu
                mainMenu.update();
                view.Render(mainMenu);
                break;
            case GameState::PauseMenu:
                // Update and render pause menu
                break;
            case GameState::GameSession:
                // Update and render game session
                session.Update(deltaTime);
                break;
        }

        // ... (any other update/render logic)
        view.endScene();

        // Swap buffers, etc.
    }

    // Cleanup and exit...

    return 0;

}
