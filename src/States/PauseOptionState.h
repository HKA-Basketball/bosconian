#ifndef BOSCONIAN_PAUSEOPTIONSTATE_H
#define BOSCONIAN_PAUSEOPTIONSTATE_H

#include "State.h"

/* TODO Pause Option */

#include "../Model/Menus/PauseMenuOption.h"
#include "../Model/GameModel.h"
#include "../View/Menus/PauseMenuOptionView.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class PauseOptionState : public State {
    PauseMenuOption* menuModel;
    PauseMenuOptionView* menuView;

    GameModel* gameModel;
    GameView* gameView;

public:
    PauseOptionState(GameModel* gameModel, GameView* gameView,
     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {
        menuModel = new PauseMenuOption();
        menuView = new PauseMenuOptionView(renderEngine, menuModel);
    };

    ~PauseOptionState() {
        delete menuView;
    }

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_PAUSEOPTIONSTATE_H
