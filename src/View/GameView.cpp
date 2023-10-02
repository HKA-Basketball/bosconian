#include "GameView.h"

#include "RenderEngine.h"
#include "Background.h"
#include "HUD.h"

GameView* GameView::instance = nullptr;

bool GameView::drawBackground() {
    Vector2D cameraCenter = Camera::Instance()->getCenter();
    for (const auto& star : Background::Instance()->getStars()) {
        // Calculate parallax effect for each star
        float parallaxX = fmod(star.rect.x - Config::parallaxFactor * cameraCenter.x, Config::levelWidth * Config::parallaxFactor);
        if (parallaxX < 0) parallaxX += Config::levelWidth * Config::parallaxFactor;

        float parallaxY = fmod(star.rect.y - Config::parallaxFactor * cameraCenter.y, Config::levelHeight * Config::parallaxFactor);
        if (parallaxY < 0) parallaxY += Config::levelHeight * Config::parallaxFactor;

        // Draw star with parallax effect
        RenderEngine::Instance()->renderRectangle({parallaxX, parallaxY}, {star.rect.w, star.rect.h}, star.color, true);
    }

    return true;
}

void GameView::drawChunks() {
    World* world = GameModel::Instance()->getWorld();
    for (Chunk chunk : world->getUnoccupiedChunks()) {
        Vector2D position = Camera::Instance()->WorldToScreen({chunk.x, chunk.y});
        RenderEngine::Instance()->renderRectangle(position, {chunk.width, chunk.height}, Config::ColorGrey);
    }
    for (Chunk chunk : world->getOccupiedChunks()) {
        Vector2D position = Camera::Instance()->WorldToScreen({chunk.x, chunk.y});
        RenderEngine::Instance()->renderRectangle(position, {chunk.width, chunk.height}, Config::ColorRed);
    }
}

void GameView::drawEnemies() {
    for (Entity* enemy : *GameModel::Instance()->getEnemies()) {
        entityRenderer->drawEntity(enemy);
    }
}

void GameView::drawBases() {
    for (Base* base : *GameModel::Instance()->getBases()) {
        baseRenderer->drawBase(base);
    }
}

void GameView::drawPlayer() {
    Player* player = GameModel::Instance()->getPlayer();
    playerRenderer->drawPlayer(player);
}

void GameView::render(float deltaTime) {
    drawBackground();
    drawChunks();
    drawEnemies();
    drawBases();
    drawPlayer();
    HUD::render();
}
