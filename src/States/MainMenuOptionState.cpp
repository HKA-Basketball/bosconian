#include "MainMenuOptionState.h"

#include "StateMachine.h"
#include "MainMenuState.h"

#include "../Utilities/Settings.h"

void MainMenuOptionState::onEnter() {
    Settings* gameSettings = Settings::Instance();
    menuModel->getSwitchItems()->at(Menu::Option::SWA).setState(gameSettings->getSWA());
    menuModel->getSwitchItems()->at(Menu::Option::SWB).setState(gameSettings->getSWB());
    menuModel->getSwitchItems()->at(Menu::Option::DEBUG).setState(gameSettings->getDebugMode());
    menuModel->getSwitchItems()->at(Menu::Option::CUSTOM_LEVELS).setState(gameSettings->getCustomLevelMode());
}

void MainMenuOptionState::onExit() {
    Settings* gameSettings = Settings::Instance();
    gameSettings->setSWA(menuModel->getSwitchItems()->at(Menu::Option::SWA).getState());
    gameSettings->setSWB(menuModel->getSwitchItems()->at(Menu::Option::SWB).getState());
    gameSettings->setDebugMode(menuModel->getSwitchItems()->at(Menu::Option::DEBUG).getState());
    gameSettings->setCustomLevelMode(menuModel->getSwitchItems()->at(Menu::Option::CUSTOM_LEVELS).getState());
}

void MainMenuOptionState::handleInput(float deltaTime) {
    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void MainMenuOptionState::update(float deltaTime) {
    menuModel->update();

    Menu::Option clickedOption = menuModel->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        changedState = States::MAIN_MENU;
    }
}

void MainMenuOptionState::render() {
    menuView->render();
}
