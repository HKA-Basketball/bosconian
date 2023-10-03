#include "LevelEditorState.h"

#include <iostream>

#include "PauseState.h"
#include "StateMachine.h"

void LevelEditorState::handleInput(float deltaTime) {

    InputHandler* inputHandler = InputHandler::Instance();

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
        LevelEditorModel::Instance()->getPlayer()->setAngle(angle);
        LevelEditorModel::Instance()->getPlayer()->update(deltaTime);
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        //StateMachine::Instance()->changeState(new PauseState());
    }


    if (inputHandler->isKeyPressed(SDLK_b))
        LevelEditorModel::Instance()->placeBase(LevelEditorModel::Instance()->getCurrentLevel(),
                                                LevelEditorModel::Instance()->getPlayer()->getPosition());

    if (inputHandler->isKeyPressed(SDLK_p)) {
        LevelEditorModel::Instance()->setPlayerSpawnPos(LevelEditorModel::Instance()->getCurrentLevel(),
                                                LevelEditorModel::Instance()->getPlayer()->getPosition());
    }
    if (inputHandler->isKeyPressed(SDLK_u)) {
        LevelEditorModel::Instance()->undoBase(LevelEditorModel::Instance()->getCurrentLevel());
    }
    if (inputHandler->isKeyPressed(SDLK_k)) {
        LevelEditorModel::Instance()->saveLevels();
    }
    if (inputHandler->isKeyPressed(SDLK_c)) {
        LevelEditorModel::Instance()->readLevels();
    }
    if (inputHandler->isKeyPressed(SDLK_m)) {
        LevelEditorModel::Instance()->increaseLevel();
    }
    if (inputHandler->isKeyPressed(SDLK_n)) {
        LevelEditorModel::Instance()->decreaseLevel();
    }
}

void LevelEditorState::update(float deltaTime) {
    // Update GameState
    LevelEditorModel::Instance()->update(deltaTime);
}

void LevelEditorState::render() {
    // Render GameStateState
    gameView->render(0);
}
