#include "PauseOptionState.h"

#include "StateMachine.h"
#include "PauseState.h"
#include "PlayingState.h"

void PauseOptionState::onEnter() {
    Settings* gameSettings = Settings::Instance();
    menuModel->getSwitchItems()->at(Menu::Option::DEBUG).setState(gameSettings->getDebugMode());
}

void PauseOptionState::handleInput(float deltaTime) {
    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        changedState = States::PLAYING;
    }

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void PauseOptionState::update(float deltaTime) {
    menuModel->update();

    Settings* gameSettings = Settings::Instance();
    gameSettings->setDebugMode(menuModel->getSwitchItems()->at(Menu::Option::DEBUG).getState());

    PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        changedState = States::PAUSE_MENU;
    }
}

void PauseOptionState::render() {
    gameView->render(0);
    menuView->render();
}
