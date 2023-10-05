#ifndef BOSCONIAN_GAMEVIEW_H
#define BOSCONIAN_GAMEVIEW_H

#include "../Model/GameModel.h"

#include "Entities/EntityRenderer.h"
#include "Entities/PlayerRenderer.h"
#include "Entities/BaseRenderer.h"

#include "HUD.h"

#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"

class GameView {
protected:
    RenderEngine* renderEngine;
    GameModel* gameModel;

    EntityRenderer* entityRenderer;
    PlayerRenderer* playerRenderer;
    BaseRenderer* baseRenderer;

    HUD* hud;

public:

    explicit GameView(RenderEngine* renderEngine, GameModel* gameModel)
    : renderEngine(renderEngine), gameModel(gameModel) {
        entityRenderer = new EntityRenderer(renderEngine, gameModel->getCamera());
        playerRenderer = new PlayerRenderer(renderEngine, gameModel->getCamera());
        baseRenderer = new BaseRenderer(renderEngine, gameModel->getCamera());
        hud = new HUD(renderEngine, gameModel);
    }

    ~GameView() = default;

    virtual void render(float deltaTime);

protected:
    bool drawBackground();

    void drawChunks();

    void drawEnemies();

    void drawBases();

    void drawPlayer();

    void drawTextAnimations();

    void drawTextAnimation(TextAnimation *textAnimation);
};

#endif //BOSCONIAN_GAMEVIEW_H
