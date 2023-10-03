#ifndef BOSCONIAN_GAMEOVERSTATE_H
#define BOSCONIAN_GAMEOVERSTATE_H

#include "State.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class GameOverState : public State {
    GameModel* gameModel;
    GameView* gameView;

public:
    GameOverState(GameModel* gameModel, GameView* gameView,
     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
     : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {};

    ~GameOverState() {}

    void onEnter() override;

    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_GAMEOVERSTATE_H
