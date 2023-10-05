#ifndef BOSCONIAN_ROUNDCLEAR_H
#define BOSCONIAN_ROUNDCLEAR_H

#include "State.h"

#include "../Controller/InputHandler.h"
#include "../Model/GameModel.h"
#include "../View/GameView.h"

class RoundClearState : public State {
    GameModel* gameModel;
    GameView* gameView;

public:
    RoundClearState(GameModel* gameModel, GameView* gameView,
     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {};

    ~RoundClearState() {}

    void onEnter() override;

    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_ROUNDCLEAR_H