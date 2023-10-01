#include "PauseState.h"

#include "StateMachine.h"
#include "PlayingState.h"
#include "MainMenuState.h"

#include "../Model/Menus/PauseMenu.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"
#include "../View/MenuView.h"

void PauseState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState());
    }

    PauseMenu::Instance()->handleHover(inputHandler->getMousePosition());
    PauseMenu::Instance()->handleClick(inputHandler->isMouseButtonPressed());
}

void PauseState::update(float deltaTime) {
    PauseMenu::Instance()->update();

    PauseMenu::Option clickedOption =  PauseMenu::Instance()->getClickedOption();

    if(clickedOption == PauseMenu::Option::CONTINUE) {
        PauseMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new PlayingState());

    } else if(clickedOption == PauseMenu::Option::EXIT) {
        PauseMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new MainMenuState());
    }
}

void PauseState::render() {
    GameView::Instance()->render(0);
    MenuView::Instance()->renderPause();
}