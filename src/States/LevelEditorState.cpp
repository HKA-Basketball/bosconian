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
        levelEditorModel->getPlayer()->setAngle(angle);
        levelEditorModel->getPlayer()->update(deltaTime);
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PauseState(levelEditorModel, levelEditorView,
                                                             renderEngine, soundEngine, inputHandler));
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_b)) {
        levelEditorModel->placeBase(levelEditorModel->getCurrentLevel(),
                             levelEditorModel->getPlayer()->getPosition());
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_p)) {
        levelEditorModel->setPlayerSpawnPos(levelEditorModel->getCurrentLevel(),
                                            levelEditorModel->getPlayer()->getPosition());
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_u)) {
        levelEditorModel->undoBase(levelEditorModel->getCurrentLevel());
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_k)) {
        levelEditorModel->saveLevels();
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_c)) {
        levelEditorModel->readLevels();
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_m)) {
        levelEditorModel->increaseLevel();
        levelEditorModel->updateLevel();
    }
    if (inputHandler->isKeyPressedAndErase(SDLK_n)) {
        levelEditorModel->decreaseLevel();
        levelEditorModel->updateLevel();
    }
}

void LevelEditorState::update(float deltaTime) {
    // Update GameState
    levelEditorModel->update(deltaTime);
}

void LevelEditorState::render() {
    // Render GameStateState
    levelEditorView->render(0);
}
