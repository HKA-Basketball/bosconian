#include "Game.h"
#include "../../Resources/imgs.h"

namespace Game {
    Game::Game(Initialization::Initializer *g) : g(g) { }

    void Game::init()
    {
        // TODO: Move
        // Only for testing
        // -------------------------------------------------------------------------------------
        nonMovingEntitys.resize(50);

        std::vector<float> list{0.f, 90.f, 45.f, 135.f, 180.f, -45.f, -90.f, -135.f};
        std::vector<std::string> listIMG{"bomb", "astroid-01", "astroid-02", "astroid-03"};
        std::vector<int> listPTS{20, 10, 10, 10};
        const float minDistance = 100.f; // minimum distance between non-moving entities
        const int cellSize = 500; // size of each cell in the grid
        const int numCols = (Utils::GlobalVars::lvlWidth + cellSize - 1) / cellSize; // number of columns in the grid
        const int numRows = (Utils::GlobalVars::lvlHeight + cellSize - 1) / cellSize; // number of rows in the grid
        std::vector<std::vector<std::vector<Entity*>>> grid(numCols, std::vector<std::vector<Entity*>>(numRows)); // 3D grid to store non-moving entities

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            int ranImg = rand() % listIMG.size();
            float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];

            Utils::Vector2D pos;
            bool positionValid = false;
            int maxAttempts = 100; // Maximum number of attempts to find a valid position

            while (!positionValid && maxAttempts > 0) {
                int col = rand() % numCols;
                int row = rand() % numRows;
                int x = col * cellSize + rand() % cellSize;
                int y = row * cellSize + rand() % cellSize;
                pos = Utils::Vector2D(x, y);

                // Check if the position is within the map boundaries
                if (pos.x >= 0 && pos.x < Utils::GlobalVars::lvlWidth && pos.y >= 0 && pos.y < Utils::GlobalVars::lvlHeight) {
                    // Check distance from entities in the same and adjacent cells
                    positionValid = true;
                    int startCol = std::max(0, col - 1);
                    int endCol = std::min(numCols - 1, col + 1);
                    int startRow = std::max(0, row - 1);
                    int endRow = std::min(numRows - 1, row + 1);

                    for (int c = startCol; c <= endCol; c++) {
                        for (int r = startRow; r <= endRow; r++) {
                            for (const auto& entity : grid[c][r]) {
                                float dist = (pos - entity->getOrigin()).length();
                                if (dist < minDistance) {
                                    positionValid = false;
                                    break;
                                }
                            }
                            if (!positionValid) {
                                break;
                            }
                        }
                        if (!positionValid) {
                            break;
                        }
                    }
                }

                maxAttempts--;
            }

            /*if (!positionValid) {

            }*/

            Drawing::Image* img = new Drawing::Image(g->drawing(), listIMG[ranImg], ang, true, "spritesheet.png");

            nonMovingEntitys[i] = new Entity(pos, ang, img, listPTS[ranImg]);
            nonMovingEntitys[i]->setAngle(ang);

            // add entity to the grid
            int col = pos.x / cellSize;
            int row = pos.y / cellSize;
            grid[col][row].push_back(nonMovingEntitys[i]);
        }


        Drawing::Image* spaceShip = new Drawing::Image(g->drawing(), std::string("ship"), 0.f, true, "spritesheet.png");
        spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        player1 = new Entity(Utils::GlobalVars::cameraPos, Utils::GlobalVars::playerAngle, spaceShip);

        // -------------------------------------------------------------------------------------


        g->sound()->playSound(Sound::SOUND_BG, 2);
    }

    int getFPS()
    {
        static int fps, lastFps;
        static float lastTickCount, tickCount;

        tickCount = SDL_GetTicks64() * 0.001f;
        fps++;

        if ((tickCount - lastTickCount) >= 1.0f)
        {
            lastTickCount = tickCount;
            lastFps = fps;
            fps = 0;
        }

        return lastFps;
    }

    void Game::update(float deltaTime) {
        g->world()->update(deltaTime);

        player1->setOrigin(Utils::GlobalVars::cameraPos);
        player1->setAngle(Utils::GlobalVars::playerAngle);
        player1->update();

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            Utils::Vector2D newPos = Utils::Vector2D(nonMovingEntitys[i]->getOrigin());

            nonMovingEntitys[i]->setOrigin(newPos);
            nonMovingEntitys[i]->update();
        }

        static Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 250;

        if (g->event()->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint64 currentTime = SDL_GetTicks64();
            if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                g->sound()->playSound(Sound::SOUND_SHOOT, 3, 0);
                // Add a new Projectile object to the vector
                Projectile* newProjectile1 = new Projectile(g->drawing(), Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y, 1000 * deltaTime, Utils::GlobalVars::playerAngle);
                Projectile* newProjectile2 = new Projectile(g->drawing(), Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y, 1000 * deltaTime, Utils::GlobalVars::playerAngle + 180);
                playersProjectiles.push_back(newProjectile1);
                playersProjectiles.push_back(newProjectile2);
                timeSinceLastProjectile = currentTime;
            }
        }

        // Update the positions of the player's projectiles
        for (int i = 0; i < playersProjectiles.size(); i++) {
            playersProjectiles[i]->update(1000 * deltaTime);
            // Check if the projectile is out of bounds
            if (playersProjectiles[i]->isOffscreen() || !playersProjectiles[i]->getActive()) {
                std::swap(playersProjectiles[i], playersProjectiles.back());
                playersProjectiles.pop_back();
            }
        }
    }

    void Game::postUpdate(float deltaTime) {
        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            SDL_Rect worldPosRec = nonMovingEntitys[i]->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::GlobalVars::WorldToScreen(worldPos, screenPos);
            if (!isOnScreen)
                continue;

            for (int y = 0; y < playersProjectiles.size(); y++){
                if (!playersProjectiles[y]->getActive())
                    continue;

                if (nonMovingEntitys[i]->isActiv() && playersProjectiles[y]->ProjectileHitsEntity(worldPosRec)) {
                    nonMovingEntitys[i]->setActive(false);
                    playersProjectiles[y]->setActive(false);
                    Utils::GlobalVars::currenPTS += nonMovingEntitys[i]->getPTS();
                    //Run Animation
                    std::swap(nonMovingEntitys[i], nonMovingEntitys.back());
                    nonMovingEntitys.pop_back();
                    break;
                }
            }
        }
    }

    void Game::render(float deltaTime) {
        //Drawing
        g->world()->renderBackground();

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            nonMovingEntitys[i]->draw();

            /*SDL_Rect worldPosRec = nonMovingEntitys[i]->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::GlobalVars::WorldToScreen(worldPos, screenPos);

            SDL_Rect screenPosRect = {static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), worldPosRec.w, worldPosRec.h};

            char pos[256];
            snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)worldPosRec.x, (int)worldPosRec.y);
            SDL_Rect destR = { 0, 0, 0, 0 };
            TTF_SizeText(g->renderer()->m_fonts[1], pos, &destR.w, &destR.h);
            g->drawing()->string(std::string(pos), g->renderer()->m_fonts[1], { 255, 255, 255 }, Utils::Vector2D(screenPos.x, screenPos.y));

            if (!nonMovingEntitys[i]->isActiv())
                g->drawing()->rectangle({255, 0, 0, 255}, screenPosRect);
            else
                g->drawing()->rectangle({0, 255, 0, 255}, screenPosRect);*/
        }

        player1->draw();

        // Render the player's projectiles
        for (auto& projectile : playersProjectiles) {
            projectile->render();
        }

        char text[32];
        char pos[256];

        snprintf(text, sizeof(text), "FPS: %i", getFPS());
        g->drawing()->string(std::string(text), g->renderer()->m_fonts[0], {255, 255, 255}, { 10, 5 });

        snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)Utils::GlobalVars::cameraPos.x, (int)Utils::GlobalVars::cameraPos.y);
        SDL_Rect destR = { 0, 0, 0, 0 };
        TTF_SizeText(g->renderer()->m_fonts[0], pos, &destR.w, &destR.h);
        g->drawing()->string(std::string(pos), g->renderer()->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(Utils::GlobalVars::windowWidth - (destR.w + 15), 5));

        // -------------------------------------------------------------------------------------

        // TODO: Move to UI Class
        SDL_Rect rec3 = { Utils::GlobalVars::windowWidth, 0, Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight };
        g->drawing()->fillRectangle2({ 0, 0, 0, 255 }, rec3);

        SDL_Rect destScor = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destScor.x = Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10;
        destScor.y = 1;
        g->drawing()->string(std::string("HI-SCORE"), g->renderer()->m_fonts[0], { 255, 0, 0 }
            , Utils::Vector2D(destScor.x, destScor.y), 1);

        g->drawing()->string(std::to_string(Utils::GlobalVars::currenPTS), g->renderer()->m_fonts[0], { 255, 255, 255 }
                , Utils::Vector2D(destScor.x, destScor.y + 28), 1);

        SDL_Rect destCon = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destCon.x = Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10;
        destCon.y = 192 - destCon.h;
        g->drawing()->string(std::string("CONDITION"), g->renderer()->m_fonts[0], { 255, 255, 255 }
            , Utils::Vector2D(destCon.x, destCon.y), 1);

        SDL_Rect rec4 = { Utils::GlobalVars::windowWidth, 240, Utils::GlobalVars::infoWidth, 64 };
        g->drawing()->fillRectangle2({ 0, 255, 0, 255 }, rec4);

        g->world()->render2DRadar(Utils::Vector2D(Utils::GlobalVars::windowWidth, 320), Utils::Vector2D(Utils::GlobalVars::infoWidth, 448));
    }
} // Game