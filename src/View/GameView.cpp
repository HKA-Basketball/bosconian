#include "GameView.h"

#include "RenderEngine.h"
#include "Background.h"
#include "HUD.h"
#include "../Model/GameModel.h"
#include "../Graphic/Sprite.h"

GameView* GameView::instance = nullptr;

bool GameView::drawBackground() {
    SDL_Renderer* renderer = RenderEngine::Instance()->getRenderer();
    Background::Instance()->drawStars(renderer);

    return true;
}

void drawCannonHitbox(Cannon* cannon) {
    RenderEngine* renderEngine = RenderEngine::Instance();

    std::optional<Vector2D> renderPosition = Camera::Instance()->IsInView(*cannon);
    if (!renderPosition) {
        return;
    }

    Player* player = GameModel::Instance()->getPlayer();

    Vector2D screenPosition = Camera::Instance()->WorldToScreen(renderPosition.value());
    Vector2D playerPosition = Camera::Instance()->WorldToScreen(player->getPosition());

    // Calculate the start and end angles of the view cone
    float startAngle = Math::normalizeAngle360(cannon->getAngle().getDegree() - (cannon->getViewAngle() / 2.0f));
    float endAngle = Math::normalizeAngle360(cannon->getAngle().getDegree() + (cannon->getViewAngle() / 2.0f));

    // Calculate points for view cone lines
    auto M_FPI = static_cast<float>(M_PI);
    Vector2D startCone = {
        screenPosition.x + cannon->getViewLength() * std::cos(startAngle * (M_FPI / 180.0f)),
        screenPosition.y + cannon->getViewLength() * std::sin(startAngle * (M_FPI / 180.0f))
    };
    Vector2D endCone = {
        screenPosition.x + cannon->getViewLength() * std::cos(endAngle * (M_FPI / 180.0f)),
        screenPosition.y + cannon->getViewLength() * std::sin(endAngle * (M_FPI / 180.0f))
    };

    // Draw view cone
    renderEngine->renderCone(startCone, screenPosition, endCone, Config::ColorWhite);

    // Calculate the angle between the Cannon and the player
    float angleToPlayer = atan2(playerPosition.y - screenPosition.y, playerPosition.x - screenPosition.x);
    angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
    angleToPlayer = Math::normalizeAngle360(angleToPlayer);

    // Check if the player's angle is within the view cone
    bool playerInCone = (startAngle <= endAngle) ? (angleToPlayer >= startAngle && angleToPlayer <= endAngle) : (angleToPlayer >= startAngle || angleToPlayer <= endAngle);

    if (playerInCone) {
        Vector2D playerLineEnd = {
                static_cast<float>(screenPosition.x + cannon->getViewLength() * std::cos(angleToPlayer * (M_PI / 180.0f))),
                static_cast<float>(screenPosition.y + cannon->getViewLength() * std::sin(angleToPlayer * (M_PI / 180.0f)))
        };
        renderEngine->renderLine(screenPosition, playerLineEnd, Config::ColorRed);
    }

    Hitbox hitbox = cannon->getHitbox();
    Vector2D pos = Camera::Instance()->WorldToScreen(cannon->getPosition());
    renderEngine->renderRotatedRectangle(pos, hitbox.getSize(), hitbox.getAngle(), Config::ColorGreen);
}

void drawEntity(Entity* entity) {
    std::optional<Vector2D> renderPosition = Camera::Instance()->IsInView(*entity);
    if (renderPosition) {
        Vector2D position = Camera::Instance()->WorldToScreen(renderPosition.value());
        Sprite entitySprite(entity->getSpriteInfo(), position);
        RenderEngine::Instance()->renderSprite(entitySprite, entity->getAngle().getDegree(), true);
        RenderEngine::Instance()->renderRotatedRectangle(position, entity->getHitbox().getSize(), entity->getHitbox().getAngle(), Config::ColorGreen);
    }
}

void drawProjectile(Projectile* projectile) {
    std::optional<Vector2D> renderPosition = Camera::Instance()->IsInView(*projectile);
    if (renderPosition) {
        Vector2D position = Camera::Instance()->WorldToScreen(renderPosition.value());
        Sprite entitySprite(projectile->getSpriteInfo(), position);
        RenderEngine::Instance()->renderSprite(entitySprite, projectile->getAngle().getDegree(), true);
        RenderEngine::Instance()->renderRotatedRectangle(position, projectile->getHitbox().getSize(), projectile->getHitbox().getAngle(), Config::ColorGreen);
    }
}

void GameView::drawHitbox() {
    Player* player = GameModel::Instance()->getPlayer();

    for (Projectile* projectile : *player->getProjectiles()) {
        drawProjectile(projectile);
    }


    for (Ship* enemy : *GameModel::Instance()->getEnemies()) {
        drawEntity(enemy);
    }

    for (Obstacle* enemy : *GameModel::Instance()->getObstacles()) {
        drawEntity(enemy);
    }

    for (Base* base : *GameModel::Instance()->getBases()) {
        drawEntity(base);

        for (Cannon* cannon : *base->getCannons()) {
            std::optional<Vector2D> renderPosition = Camera::Instance()->IsInView(*cannon);
            if (renderPosition) {
                Vector2D position = Camera::Instance()->WorldToScreen(renderPosition.value());
                Sprite entitySprite(cannon->getSpriteInfo(), position);
                RenderEngine::Instance()->renderSprite(entitySprite, base->getAngle().getDegree(), true);
                RenderEngine::Instance()->renderRotatedRectangle(position, cannon->getHitbox().getSize(), cannon->getHitbox().getAngle(), Config::ColorGreen);
                drawCannonHitbox(cannon);
            }

            for (Projectile* projectile : *cannon->getProjectiles()) {
                drawProjectile(projectile);
            }
        }
    }
}

void GameView::drawPlayer() {
    Player* player = GameModel::Instance()->getPlayer();
    Vector2D position = Camera::Instance()->WorldToScreen(player->getPosition());
    Hitbox hitbox = player->getHitbox();

    Sprite entitySprite(player->getSpriteInfo(), position);
    RenderEngine::Instance()->renderSprite(entitySprite, player->getAngle().getDegree(), true);
    RenderEngine::Instance()->renderRotatedRectangle(position, hitbox.getSize(), hitbox.getAngle(), Config::ColorGreen);
}


void GameView::render(float deltaTime) {
    drawBackground();
    drawPlayer();
    drawHitbox();
    HUD::render();
}
