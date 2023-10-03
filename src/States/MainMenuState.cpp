#include "MainMenuState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuOptionState.h"

void MainMenuState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressed());
}

void MainMenuState::update(float deltaTime) {
    menuModel->update();

    Menu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::START) {
        menuModel->reset();
        StateMachine::Instance()->changeState(new RoundStartState());
    } else if(clickedOption == Menu::Option::OPTIONS) {
        menuModel->reset();
        StateMachine::Instance()->changeState(new MainMenuOptionState());
    }
}

void MainMenuState::render() {
    menuView->render();
}
