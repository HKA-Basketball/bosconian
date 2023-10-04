#include "PauseState.h"

#include "StateMachine.h"
#include "PlayingState.h"
#include "PauseOptionState.h"
#include "MainMenuState.h"

void PauseState::handleInput(float deltaTime) {
    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState(gameModel, gameView,
                       renderEngine, soundEngine, inputHandler));
    }

    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressed());
}

void PauseState::update(float deltaTime) {
    menuModel->update();

    PauseMenu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::CONTINUE) {
        StateMachine::Instance()->changeState(new PlayingState(gameModel, gameView,
                       renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::OPTIONS) {
        //StateMachine::Instance()->changeState(new PauseOptionState(gameModel, gameView,
        //              renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::MAIN_MENU) {
        StateMachine::Instance()->changeState(new MainMenuState(renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::EXIT) {
        inputHandler->setQuit();
    }
}

void PauseState::render() {
    gameView->render(0);
    menuView->render();
}
