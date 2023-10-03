#include "MainMenuOptionState.h"

#include "StateMachine.h"
#include "MainMenuState.h"

#include "../Utilities/Settings.h"

void MainMenuOptionState::onEnter() {
    Settings* gameSettings = Settings::Instance();
    menuModel->getSwitchItems()->at(Menu::Option::SWA).setState(gameSettings->getSWA());
    menuModel->getSwitchItems()->at(Menu::Option::SWB).setState(gameSettings->getSWB());
}

void MainMenuOptionState::onExit() {
    Settings* gameSettings = Settings::Instance();
    gameSettings->setSWA(menuModel->getSwitchItems()->at(Menu::Option::SWA).getState());
    gameSettings->setSWB(menuModel->getSwitchItems()->at(Menu::Option::SWB).getState());
    menuModel->reset();
}

void MainMenuOptionState::handleInput(float deltaTime) {
    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void MainMenuOptionState::update(float deltaTime) {
    menuModel->update();

    Menu::Option clickedOption = menuModel->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        StateMachine::Instance()->changeState(new MainMenuState(renderEngine, soundEngine, inputHandler));
    }
}

void MainMenuOptionState::render() {
    menuView->render();
}
