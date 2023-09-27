#include "PauseState.h"

#include "PlayingState.h"
#include "StateMachine.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

void PauseState::handleInput(float deltaTime) {

    InputHandler* inputHandler = InputHandler::Instance();

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState());
    }
}

void PauseState::update(float deltaTime) {
    // Update GameState
}

void PauseState::render() {
    // Render GameStateState
    GameView::Instance()->render(0);
}