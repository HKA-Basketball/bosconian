#include "PauseOptionState.h"

#include "StateMachine.h"
#include "PauseState.h"
#include "PlayingState.h"

void PauseOptionState::onEnter() {
    Settings* gameSettings = Settings::Instance();
    menuModel->getSwitchItems()->at(Menu::Option::DEBUG).setState(gameSettings->getDebugMode());
}

void PauseOptionState::onExit() {
    Settings* gameSettings = Settings::Instance();
    gameSettings->setDebugMode(menuModel->getSwitchItems()->at(Menu::Option::DEBUG).getState());
}

void PauseOptionState::handleInput(float deltaTime) {
    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState(renderEngine, soundEngine, inputHandler));
    }

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void PauseOptionState::update(float deltaTime) {
    menuModel->update();

    PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        StateMachine::Instance()->changeState(new PauseState(gameModel, gameView,
                        renderEngine, soundEngine, inputHandler));
    }
}

void PauseOptionState::render() {
    gameView->render(0);
    menuView->render();
}
