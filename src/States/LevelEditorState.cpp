#include "LevelEditorState.h"

#include <iostream>

#include "PauseState.h"
#include "StateMachine.h"

void LevelEditorState::handleInput(float deltaTime) {

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
        gameModel->getPlayer()->update(deltaTime);
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        //StateMachine::Instance()->changeState(new PauseState());
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_b)) {
        gameModel->placeBase(gameModel->getCurrentLevel(),
                             gameModel->getPlayer()->getPosition());
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_p)) {
        gameModel->setPlayerSpawnPos(gameModel->getCurrentLevel(),
                                     gameModel->getPlayer()->getPosition());
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_u)) {
        gameModel->undoBase(gameModel->getCurrentLevel());
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_k)) {
        gameModel->saveLevels();
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_c)) {
        gameModel->readLevels();
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_m)) {
        gameModel->increaseLevel();
        gameModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_n)) {
        gameModel->decreaseLevel();
        gameModel->updateLevel();
    }
}

void LevelEditorState::update(float deltaTime) {
    // Update GameState
    gameModel->update(deltaTime);
}

void LevelEditorState::render() {
    // Render GameStateState
    gameView->render(0);
}
