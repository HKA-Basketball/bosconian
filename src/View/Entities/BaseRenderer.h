#ifndef BOSCONIAN_CANNONRENDERER_H
#define BOSCONIAN_CANNONRENDERER_H

#include "EntityRenderer.h"
#include "../../Model/Entities/Base.h"

class BaseRenderer : public EntityRenderer {
public:
    BaseRenderer(RenderEngine* renderEngine, Camera* camera) : EntityRenderer(renderEngine, camera) {}

    void drawBase(Base* base) {
        drawEntity(base);

        /*std::optional<Vector2D> renderPosition = camera->IsInView(*base);
        if (renderPosition) {
            Vector2D position = camera->WorldToScreen(renderPosition.value());
            renderEngine->renderRotatedRectangle(position, base->getTotalSize(), base->getHitbox().getAngle(), Config::ColorGrey);
        }*/

        if (base->getSpy()->isLoaded()) {
            drawEntity(base->getSpy());
        }

        for (Cannon* cannon : *base->getCannons()) {
            std::optional<Vector2D> renderPosition = camera->IsInView(*cannon);
            if (renderPosition.has_value()) {
                Vector2D position = camera->WorldToScreen(renderPosition.value());
                Sprite entitySprite(cannon->getSpriteInfo(), position);
                renderEngine->renderSprite(entitySprite, base->getAngle().getDegree(), true);

                if (Settings::Instance()->getDebugMode()) {
                    drawCannonHitbox(cannon, position);

                    if (!cannon->isDefeated()) {
                        drawCannonView(cannon, position);
                    }
                }
            }

            for (Projectile* projectile : *cannon->getProjectiles()) {
                drawEntity(projectile);
            }
        }
    }
private:

    void drawCannonHitbox(Cannon* cannon, const Vector2D& position) {
        renderEngine->renderRotatedRectangle(position, cannon->getHitbox().getSize(), cannon->getHitbox().getAngle(), Config::ColorGreen);
    }

    void drawCannonView(Cannon* cannon, const Vector2D& position) {
        Vector2D playerPosition = Camera::Instance()->WorldToScreen(cannon->getPlayerPositions()->getCenterPosition());

        // Calculate the start and end angles of the view cone
        float startAngle = Math::normalizeAngle360(cannon->getAngle().getDegree() - (cannon->getViewAngle() / 2.0f));
        float endAngle = Math::normalizeAngle360(cannon->getAngle().getDegree() + (cannon->getViewAngle() / 2.0f));

        // Calculate points for view cone lines
        auto M_FPI = static_cast<float>(M_PI);
        Vector2D startCone = {
                position.x + cannon->getViewLength() * std::cos(startAngle * (M_FPI / 180.0f)),
                position.y + cannon->getViewLength() * std::sin(startAngle * (M_FPI / 180.0f))
        };
        Vector2D endCone = {
                position.x + cannon->getViewLength() * std::cos(endAngle * (M_FPI / 180.0f)),
                position.y + cannon->getViewLength() * std::sin(endAngle * (M_FPI / 180.0f))
        };

        // Draw view cone
        renderEngine->renderCone(startCone, position, endCone, Config::ColorWhite);

        // Calculate the angle between the Cannon and the player
        float angleToPlayer = atan2(playerPosition.y - position.y, playerPosition.x - position.x);
        angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
        angleToPlayer = Math::normalizeAngle360(angleToPlayer);

        // Check if the player's angle is within the view cone
        bool playerInCone = (startAngle <= endAngle) ?
                (angleToPlayer >= startAngle && angleToPlayer <= endAngle) :
                (angleToPlayer >= startAngle || angleToPlayer <= endAngle);

        if (playerInCone) {
            Vector2D playerLineEnd = {
                    static_cast<float>(position.x + cannon->getViewLength() * std::cos(angleToPlayer * (M_PI / 180.0f))),
                    static_cast<float>(position.y + cannon->getViewLength() * std::sin(angleToPlayer * (M_PI / 180.0f)))
            };
            renderEngine->renderLine(position, playerLineEnd, Config::ColorRed);
        }
    }
};

#endif //BOSCONIAN_CANNONRENDERER_H
