#include "PauseState.h"

#include "StateMachine.h"
#include "PlayingState.h"
#include "PauseOptionState.h"
#include "MainMenuState.h"

void PauseState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState());
    }

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressed());
}

void PauseState::update(float deltaTime) {
    menuModel->update();

    PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::CONTINUE) {
        StateMachine::Instance()->changeState(new PlayingState(gameModel, gameView));

    } else if(clickedOption == Menu::Option::OPTIONS) {
        //StateMachine::Instance()->changeState(new PauseOptionState(gameModel, gameView));

    } else if(clickedOption == Menu::Option::EXIT) {
        StateMachine::Instance()->changeState(new MainMenuState());
    }
}

void PauseState::render() {
    gameView->render(0);
    menuView->render();
}
