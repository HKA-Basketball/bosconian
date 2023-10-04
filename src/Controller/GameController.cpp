#include "GameController.h"

#include "../States/MainMenuState.h"
#include "../States/MainMenuOptionState.h"
#include "../States/PauseState.h"
#include "../States/PauseOptionState.h"
#include "../States/RoundStartState.h"
#include "../States/RoundClearState.h"
#include "../States/GameOverState.h"
#include "../States/PlayingState.h"
#include "../States/LevelEditorState.h"

GameController::GameController() {
    renderEngine = new RenderEngine();

    soundEngine = new SoundEngine();
    soundEngine->startBackgroundMusic("sounds/loop.wav");

    inputHandler = new InputHandler();

    stateMachine = new StateMachine(renderEngine, soundEngine, inputHandler);

    frameTimer = new FrameTimer(60);
}

GameController::~GameController() {
    soundEngine->stopBackgroundMusic();
    Settings::DestroyInstance();

    delete renderEngine;
    delete soundEngine;
    delete inputHandler;
    delete stateMachine;
    delete frameTimer;

    delete gameModel;
    delete gameView;
    delete levelEditorModel;
    delete levelEditorView;
}

void GameController::start() {
    while(!inputHandler->hasQuit()) loop();
}

void GameController::loop() {

    frameTimer->startFrame();

    inputHandler->update();

    stateMachine->getCurrentState()->handleInput(frameTimer->getDeltaTime());

    stateMachine->getCurrentState()->update(frameTimer->getDeltaTime());

    renderEngine->beginScene();

    stateMachine->getCurrentState()->render();

    renderEngine->endScene();

    this->updateState();

    frameTimer->delayFrame();
}

void GameController::updateState() {
    switch (stateMachine->getCurrentState()->stateChanged()) {
        case States::NONE: default: break;

        case States::MAIN_MENU:
            delete gameModel;
            delete gameView;
            gameModel = nullptr;
            gameView = nullptr;

            delete levelEditorModel;
            delete levelEditorView;
            levelEditorModel = nullptr;
            levelEditorView = nullptr;

            stateMachine->changeState(
                    new MainMenuState(renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::MAIN_MENU_OPTION:
            stateMachine->changeState(
                    new MainMenuOptionState(renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::PAUSE_MENU:
            stateMachine->changeState(
                    new PauseState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::PAUSE_MENU_OPTION:
            stateMachine->changeState(
                    new PauseOptionState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::ROUND_START:
            if (gameModel == nullptr || gameView == nullptr) {
                gameModel = new GameModel(soundEngine);
                gameView = new GameView(renderEngine, gameModel);
            }

            stateMachine->changeState(
                    new RoundStartState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::ROUND_CLEAR:
            stateMachine->changeState(
                    new RoundClearState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::GAME_OVER:
            stateMachine->changeState(
                    new GameOverState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::PLAYING:
            stateMachine->changeState(
                    new PlayingState(gameModel, gameView, renderEngine, soundEngine, inputHandler)
            );
            break;

        case States::LEVEL_EDITOR:
            if (levelEditorModel == nullptr || levelEditorView == nullptr) {
                levelEditorModel = new LevelEditorModel(soundEngine);
                levelEditorView = new LevelEditorView(renderEngine, levelEditorModel);
                gameModel = levelEditorModel;
                gameView = levelEditorView;
            }
            stateMachine->changeState(
                    new LevelEditorState(levelEditorModel, levelEditorView, renderEngine, soundEngine, inputHandler)
            );
            break;
    }
}