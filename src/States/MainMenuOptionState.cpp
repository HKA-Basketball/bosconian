#include "MainMenuOptionState.h"

#include "../View/MenuView.h"
#include "../Controller/InputHandler.h"

void MainMenuOptionState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    MainMenuOption::Instance()->handleHover(inputHandler->getMousePosition());
    MainMenuOption::Instance()->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void MainMenuOptionState::update(float deltaTime) {
    MainMenuOption::Instance()->update();

    Menu::Option clickedOption =  MainMenuOption::Instance()->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        MainMenuOption::Instance()->reset();
        StateMachine::Instance()->changeState(new MainMenuState());
    }
}

void MainMenuOptionState::render() {
    MenuView::Instance()->renderMainOption();
}