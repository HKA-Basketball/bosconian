#include "MainMenuState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuOptionState.h"

#include "../Model/Menus/MainMenu.h"
#include "../View/MenuView.h"
#include "../Controller/InputHandler.h"

void MainMenuState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    MainMenu::Instance()->handleHover(inputHandler->getMousePosition());
    MainMenu::Instance()->handleClick(inputHandler->isMouseButtonPressed());
}

void MainMenuState::update(float deltaTime) {
    MainMenu::Instance()->update();

    Menu::Option clickedOption =  MainMenu::Instance()->getClickedOption();

    if(clickedOption == Menu::Option::START) {
        MainMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new RoundStartState());
    } else if(clickedOption == Menu::Option::OPTIONS) {
        MainMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new MainMenuOptionState());
    }
}

void MainMenuState::render() {
    MenuView::Instance()->renderMain();
}
