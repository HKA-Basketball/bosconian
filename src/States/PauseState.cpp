#include "PauseState.h"

#include "StateMachine.h"
#include "PlayingState.h"
#include "PauseOptionState.h"
#include "MainMenuState.h"

void PauseState::handleInput(float deltaTime) {
    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        changedState = States::PLAYING;
    }

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void PauseState::update(float deltaTime) {
    menuModel->update();

    PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::CONTINUE) {
        changedState = States::PLAYING;

    } else if(clickedOption == Menu::Option::OPTIONS) {
        changedState = States::PAUSE_MENU_OPTION;

    } else if(clickedOption == Menu::Option::MAIN_MENU) {
        changedState = States::MAIN_MENU;

    } else if(clickedOption == Menu::Option::EXIT) {
        inputHandler->setQuit();
    }
}

void PauseState::render() {
    gameView->render(0);
    menuView->render();
}
