#include "RoundClearState.h"

#include "StateMachine.h"
#include "RoundStartState.h"

#include "../Controller/InputHandler.h"
#include "../Model/GameModel.h"
#include "../View/GameView.h"

void RoundClearState::onEnter() {
    TextAnimation* roundClearAnimation = GameModel::Instance()->getRoundClearAnimation();
    roundClearAnimation->start();
}

void RoundClearState::onExit() {

}

void RoundClearState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();
}

void RoundClearState::update(float deltaTime) {
    // Update GameState

    TextAnimation* roundClearAnimation = GameModel::Instance()->getRoundClearAnimation();

    roundClearAnimation->update(deltaTime);

    if (roundClearAnimation->isDone()) {
        GameModel::Instance()->nextRound();
        StateMachine::Instance()->changeState(new RoundStartState());
    }
}

void RoundClearState::render() {
    // Render GameStateState
    GameView::Instance()->render(0);
}
