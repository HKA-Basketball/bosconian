#include "GameView.h"

bool GameView::drawBackground() {
    Vector2D cameraCenter = Camera::Instance()->getCenter();
    for (const auto& star : Background::Instance()->getStars()) {
        // Calculate parallax effect for each star
        float parallaxX = fmod(star.rect.x - Config::parallaxFactor * cameraCenter.x, Config::levelWidth * Config::parallaxFactor);
        if (parallaxX < 0) parallaxX += Config::levelWidth * Config::parallaxFactor;

        float parallaxY = fmod(star.rect.y - Config::parallaxFactor * cameraCenter.y, Config::levelHeight * Config::parallaxFactor);
        if (parallaxY < 0) parallaxY += Config::levelHeight * Config::parallaxFactor;

        // Draw star with parallax effect
        renderEngine->renderRectangle({parallaxX, parallaxY}, {star.rect.w, star.rect.h}, star.color, true);
    }

    return true;
}

void GameView::drawChunks() {
    World* world = gameModel->getWorld();
    Camera* camera = gameModel->getCamera();

    for (Chunk chunk : world->getUnoccupiedChunks()) {
        Vector2D position = camera->WorldToScreen({chunk.x, chunk.y});
        renderEngine->renderRectangle(position, {chunk.width, chunk.height}, Config::ColorGrey);
    }
    for (Chunk chunk : world->getOccupiedChunks()) {
        Vector2D position = camera->WorldToScreen({chunk.x, chunk.y});
        renderEngine->renderRectangle(position, {chunk.width, chunk.height}, Config::ColorRed);
    }
}

void GameView::drawEnemies() {
    for (Entity* enemy : *gameModel->getEnemies()) {
        entityRenderer->drawEntity(enemy);
    }
}

void GameView::drawBases() {
    for (Base* base : *gameModel->getBases()) {
        baseRenderer->drawBase(base);
    }
}

void GameView::drawPlayer() {
    Player* player = gameModel->getPlayer();
    playerRenderer->drawPlayer(player);
}

void GameView::render(float deltaTime) {
    drawBackground();

    if (Settings::Instance()->getDebugMode()) {
        drawChunks();
    }

    drawEnemies();
    drawBases();
    drawPlayer();
    drawTextAnimations();
    hud->render();
}

void GameView::drawTextAnimation(TextAnimation* textAnimation) {
    renderEngine->renderText(textAnimation->getText(), {Config::screenCenterX, Config::screenCenterY/2},
                             Config::ColorWhite, Font::JOYSTIX_64PX, TextAlign::CENTER);
}

void GameView::drawTextAnimations() {
    auto* readyAnimation = gameModel->getReadyAnimation();

    if(!readyAnimation->isDone()) {
        drawTextAnimation(readyAnimation);
    }

    auto* roundClearAnimation = gameModel->getRoundClearAnimation();

    if(!roundClearAnimation->isDone()) {
        drawTextAnimation(roundClearAnimation);
    }

    auto* gameOverAnimation = gameModel->getGameOverAnimation();

    if(!gameOverAnimation->isDone()) {
        drawTextAnimation(gameOverAnimation);
    }
}
