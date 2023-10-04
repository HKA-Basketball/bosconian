#include "MainMenuState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuOptionState.h"
#include "LevelEditorState.h"

void MainMenuState::handleInput(float deltaTime) {
    menuModel->handleHover(inputHandler->getMousePosition());
    menuModel->handleClick(inputHandler->isMouseButtonPressed());
}

void MainMenuState::update(float deltaTime) {
    menuModel->update();

    Menu::Option clickedOption =  menuModel->getClickedOption();

    if(clickedOption == Menu::Option::START) {
        StateMachine::Instance()->changeState(new RoundStartState(renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::LEVEL_EDITOR) {
        StateMachine::Instance()->changeState(new LevelEditorState(renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::OPTIONS) {
        StateMachine::Instance()->changeState(new MainMenuOptionState(renderEngine, soundEngine, inputHandler));

    } else if(clickedOption == Menu::Option::EXIT) {
        inputHandler->setQuit();
    }
}

void MainMenuState::render() {
    menuView->render();
}
