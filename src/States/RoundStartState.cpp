#include "RoundStartState.h"

#include "StateMachine.h"
#include "PlayingState.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"

void RoundStartState::onEnter() {

}

void RoundStartState::onExit() {

}

void RoundStartState::handleInput(float deltaTime) {}

void RoundStartState::update(float deltaTime) {
    TextAnimation* readyAnimation = GameModel::Instance()->getReadyAnimation();

    if (readyAnimation->isDone()) {
        readyAnimation->start();
    }

    readyAnimation->update(deltaTime);

    if (readyAnimation->isDone()) {
        StateMachine::Instance()->changeState(new PlayingState());
    }
}

void RoundStartState::render() {
    GameView::Instance()->render(0);
}
