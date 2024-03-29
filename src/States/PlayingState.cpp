#include "PlayingState.h"

#include <iostream>

#include "PauseState.h"
#include "GameOverState.h"
#include "RoundClearState.h"

#include "StateMachine.h"

void PlayingState::handleInput(float deltaTime) {
    float angle = -1; // Initialize to an invalid angle
    if (inputHandler->isKeyPressed(SDLK_w) && inputHandler->isKeyPressed(SDLK_a)) {
        angle = 315; // up-left
    } else if (inputHandler->isKeyPressed(SDLK_w) && inputHandler->isKeyPressed(SDLK_d)) {
        angle = 45; // up-right
    } else if (inputHandler->isKeyPressed(SDLK_s) && inputHandler->isKeyPressed(SDLK_a)) {
        angle = 225; // down-left
    } else if (inputHandler->isKeyPressed(SDLK_s) && inputHandler->isKeyPressed(SDLK_d)) {
        angle = 135; // down-right
    } else if (inputHandler->isKeyPressed(SDLK_w)) {
        angle = 0; // up
    } else if (inputHandler->isKeyPressed(SDLK_s)) {
        angle = 180; // down
    } else if (inputHandler->isKeyPressed(SDLK_a)) {
        angle = 270; // left
    } else if (inputHandler->isKeyPressed(SDLK_d)) {
        angle = 90; // right
    }

    if (angle != -1) {
        gameModel->getPlayer()->setAngle(angle);
    }

    if (inputHandler->isKeyPressed(SDLK_LCTRL)) {
        bool hasShooted = gameModel->getPlayer()->shoot(deltaTime);
        if(hasShooted) {
            soundEngine->playSoundEffect("sounds/shoot.wav");
        }
    }

    if (inputHandler->isKeyPressed(SDLK_k)) {
        gameModel->getPlayer()->setDefeated();
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        changedState = States::PAUSE_MENU;
    }
}

void PlayingState::update(float deltaTime) {
    // Update GameState
    gameModel->update(deltaTime);

    if(gameModel->getPlayer()->isDead()) {
        changedState = States::GAME_OVER;

    } else if(gameModel->getBases()->empty()) {
        changedState = States::ROUND_CLEAR;
    }
}

void PlayingState::render() {
    // Render GameStateState
    gameView->render(0);
}
