#ifndef BOSCONIAN_LEVELEDITORVIEW_H
#define BOSCONIAN_LEVELEDITORVIEW_H

#include "GameView.h"

class LevelEditorView : public GameView {
public:
    explicit LevelEditorView(RenderEngine* renderEngine, GameModel* gameModel) : GameView(renderEngine, gameModel) {}

    void render(float deltaTime) override {
        drawBackground();

        if (Settings::Instance()->getDebugMode()) {
            drawChunks();
        }

        drawBases();
        drawPlayer();
        hud->render();
    }

};


#endif //BOSCONIAN_LEVELEDITORVIEW_H
