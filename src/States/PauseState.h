#ifndef BOSCONIAN_PAUSESTATE_H
#define BOSCONIAN_PAUSESTATE_H

#include "State.h"

#include "../Model/Menus/PauseMenu.h"
#include "../Model/GameModel.h"
#include "../View/Menus/PauseMenuView.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class PauseState : public State {
    PauseMenu* menuModel;
    PauseMenuView* menuView;

    GameModel* gameModel;
    GameView* gameView;

public:
    PauseState(GameModel* gameModel, GameView* gameView,
     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {
        menuModel = PauseMenu::Instance();
        menuView = new PauseMenuView(renderEngine, menuModel);
    };

    ~PauseState() {
        delete menuView;
    }
public:
    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_PAUSESTATE_H
