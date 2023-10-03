#ifndef BOSCONIAN_LEVELEDITORSTATE_H
#define BOSCONIAN_LEVELEDITORSTATE_H

#include "State.h"

#include "../Model/LevelEditorModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class LevelEditorState : public State {
    LevelEditorModel* gameModel;
    GameView* gameView;

public:

    LevelEditorState() {
        gameModel = LevelEditorModel::Instance();
        gameView = new GameView(gameModel);
    }

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};


#endif //BOSCONIAN_LEVELEDITORSTATE_H
