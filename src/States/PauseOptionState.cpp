#include "PauseOptionState.h"

#include "StateMachine.h"
#include "PauseState.h"
#include "PlayingState.h"

#include "../Model/Menus/PauseMenu.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"
#include "../View/MenuView.h"

void PauseOptionState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PlayingState());
    }

    PauseMenu::Instance()->handleHover(inputHandler->getMousePosition());
    PauseMenu::Instance()->handleClick(inputHandler->isMouseButtonPressed());
}

void PauseOptionState::update(float deltaTime) {
    PauseMenu::Instance()->update();

    PauseMenu::Option clickedOption =  PauseMenu::Instance()->getClickedOption();

    if(clickedOption == Menu::Option::EXIT) {
        PauseMenu::Instance()->reset();
        StateMachine::Instance()->changeState(new PauseState());
    }
}

void PauseOptionState::render() {
    GameView::Instance()->render(0);
    MenuView::Instance()->renderPauseOption();
}
