#include "MainMenuState.h"

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

    MainMenu::Option clickedOption =  MainMenu::Instance()->getClickedOption();

    if(clickedOption == MainMenu::Option::START) {
        MainMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new PlayingState());
    }
}

void MainMenuState::render() {
    MenuView::Instance()->renderMain();
}
