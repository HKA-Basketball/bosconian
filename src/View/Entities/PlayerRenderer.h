#ifndef BOSCONIAN_PLAYERRENDERER_H
#define BOSCONIAN_PLAYERRENDERER_H

#include "EntityRenderer.h"
#include "../../Model/Entities/Player.h"

class PlayerRenderer : public EntityRenderer {
public:
    PlayerRenderer(RenderEngine *renderEngine, Camera *camera) : EntityRenderer(renderEngine, camera) {}

    void drawPlayer(Player *player) {
        Vector2D position = camera->WorldToScreen(player->getPosition());

        Sprite entitySprite(player->getSpriteInfo(), position);
        renderEngine->renderSprite(entitySprite, player->getAngle().getDegree(), true);

        Hitbox hitbox = player->getHitbox();
        renderEngine->renderRotatedRectangle(position, hitbox.getSize(), hitbox.getAngle(), Config::ColorGreen);

        for (Projectile* projectile : *player->getProjectiles()) {
            drawEntity(projectile);
        }
    }
};

#endif //BOSCONIAN_PLAYERRENDERER_H
