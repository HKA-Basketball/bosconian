#ifndef BOSCONIAN_LEVELEDITORSTATE_H
#define BOSCONIAN_LEVELEDITORSTATE_H

#include "State.h"

#include "../Model/LevelEditorModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"
#include "../View/LevelEditorView.h"

class LevelEditorState : public State {
    LevelEditorModel* levelEditorModel;
    LevelEditorView* levelEditorView;

public:

    LevelEditorState(LevelEditorModel* levelEditorModel, LevelEditorView* levelEditorView,
                     RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
            : State(renderEngine, soundEngine, inputHandler), levelEditorModel(levelEditorModel), levelEditorView(levelEditorView) {
    }

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};


#endif //BOSCONIAN_LEVELEDITORSTATE_H
