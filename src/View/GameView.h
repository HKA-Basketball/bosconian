#ifndef BOSCONIAN_GAMEVIEW_H
#define BOSCONIAN_GAMEVIEW_H

#include "../Model/GameModel.h"

#include "Entities/EntityRenderer.h"
#include "Entities/PlayerRenderer.h"
#include "Entities/BaseRenderer.h"

#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"

class GameView {
    static GameView* instance;
    RenderEngine* renderEngine;
    GameModel* gameModel;

    EntityRenderer* entityRenderer;
    PlayerRenderer* playerRenderer;
    BaseRenderer* baseRenderer;

    GameView() {
        renderEngine = RenderEngine::Instance();
        gameModel = GameModel::Instance();
        entityRenderer = new EntityRenderer(renderEngine, gameModel->getCamera());
        playerRenderer = new PlayerRenderer(renderEngine, gameModel->getCamera());
        baseRenderer = new BaseRenderer(renderEngine, gameModel->getCamera());
    }
    ~GameView() = default;

public:
    static GameView* Instance() {
        if (!instance) {
            instance = new GameView();
            return instance;
        }
        return instance;
    }

    void render(float deltaTime);

private:
    bool drawBackground();

    void drawChunks();

    void drawEnemies();

    void drawBases();

    void drawPlayer();

    void drawTextAnimations();

    void drawTextAnimation(TextAnimation *textAnimation);
};

#endif //BOSCONIAN_GAMEVIEW_H
