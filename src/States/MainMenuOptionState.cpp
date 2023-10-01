#include "MainMenuOptionState.h"

#include "StateMachine.h"
#include "MainMenuState.h"

#include "../View/MenuView.h"
#include "../Controller/InputHandler.h"
#include "../Utilities/Settings.h"

MainMenuOptionState::MainMenuOptionState() {
    MainMenuOption* obj = MainMenuOption::Instance();

    Settings* gameSettings = Settings::Instance();
    obj->getSwitchItems()->at(Menu::Option::SWA).setState(gameSettings->getSWA());
    obj->getSwitchItems()->at(Menu::Option::SWB).setState(gameSettings->getSWB());
}

void MainMenuOptionState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    MainMenuOption::Instance()->handleHover(inputHandler->getMousePosition());
    MainMenuOption::Instance()->handleClick(inputHandler->isMouseButtonPressedAndErase());
}

void MainMenuOptionState::update(float deltaTime) {
    MainMenuOption::Instance()->update();

    Menu::Option clickedOption = MainMenuOption::Instance()->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        MainMenuOption* obj = MainMenuOption::Instance();

        Settings* gameSettings = Settings::Instance();
        gameSettings->setSWA(obj->getSwitchItems()->at(Menu::Option::SWA).getState());
        gameSettings->setSWB(obj->getSwitchItems()->at(Menu::Option::SWB).getState());

        MainMenuOption::Instance()->reset();
        StateMachine::Instance()->changeState(new MainMenuState());
    }
}

void MainMenuOptionState::render() {
    MenuView::Instance()->renderMainOption();
}