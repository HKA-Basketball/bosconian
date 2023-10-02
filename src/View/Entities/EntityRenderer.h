#ifndef BOSCONIAN_ENTITYRENDERER_H
#define BOSCONIAN_ENTITYRENDERER_H

#include "../RenderEngine.h"
#include "../../Model/Camera.h"
#include "../../Model/Entities/Entity.h"
#include "../../Model/Entities/Base.h"

class EntityRenderer {
protected:
    RenderEngine* renderEngine;
    Camera* camera;

public:
    EntityRenderer(RenderEngine* renderEngine, Camera* camera) : renderEngine(renderEngine), camera(camera) {}

    virtual void drawEntity(Entity* entity) {
        std::optional<Vector2D> renderPosition = camera->IsInView(*entity);
        if (renderPosition.has_value()) {
            Vector2D position = camera->WorldToScreen(renderPosition.value());

            Sprite entitySprite(entity->getSpriteInfo(), position);
            renderEngine->renderSprite(entitySprite, entity->getAngle().getDegree(), true);

            // TODO: Config
            Hitbox hitbox = entity->getHitbox();
            renderEngine->renderRotatedRectangle(position, hitbox.getSize(), hitbox.getAngle(), Config::ColorGreen);
        }
    }
};

#endif //BOSCONIAN_ENTITYRENDERER_H
