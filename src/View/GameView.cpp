#include "GameView.h"

#include "RenderEngine.h"
#include "Background.h"
#include "HUD.h"

GameView* GameView::instance = nullptr;

bool GameView::drawBackground() {
    SDL_Renderer* renderer = RenderEngine::Instance()->getRenderer();
    Background::Instance()->drawStars(renderer);

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
