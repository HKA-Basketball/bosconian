#include "PauseOptionState.h"

#include "StateMachine.h"
#include "PauseState.h"
#include "PlayingState.h"

void PauseOptionState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState());
    }

    //menuModel->handleHover(inputHandler->getMousePosition());
    //menuModel->handleClick(inputHandler->isMouseButtonPressed());
}

void PauseOptionState::update(float deltaTime) {
    //menuModel->update();

    //PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    /*if(clickedOption == Menu::Option::EXIT) {
        StateMachine::Instance()->changeState(new PauseState(gameModel, gameView));
    }*/
}

void PauseOptionState::render() {
    gameView->render(0);
    menuView->render();
}
