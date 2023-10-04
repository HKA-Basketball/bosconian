#include "MainMenuState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuOptionState.h"
#include "LevelEditorState.h"

void MainMenuState::handleInput(float deltaTime) {
    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void MainMenuState::update(float deltaTime) {
    menuModel->update();

    Menu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::START) {
        changedState = States::ROUND_START;

    } else if(clickedOption == Menu::Option::LEVEL_EDITOR) {
        changedState = States::LEVEL_EDITOR;

    } else if(clickedOption == Menu::Option::OPTIONS) {
        changedState = States::MAIN_MENU_OPTION;

    } else if(clickedOption == Menu::Option::EXIT) {
        inputHandler->setQuit();
    }
}

void MainMenuState::render() {
    menuView->render();
}
