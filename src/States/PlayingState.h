#ifndef BOSCONIAN_PLAYINGSTATE_H
#define BOSCONIAN_PLAYINGSTATE_H

#include "State.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class PlayingState : public State {
    GameModel* gameModel;
    GameView* gameView;

public:
    PlayingState(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler) {
        gameModel = new GameModel(soundEngine);
        gameView = new GameView(renderEngine, gameModel);
    };

    PlayingState(GameModel* gameModel, GameView* gameView,
     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
    : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {};

    ~PlayingState() {}

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_PLAYINGSTATE_H
