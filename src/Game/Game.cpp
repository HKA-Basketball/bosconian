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
        const float minDistance = 100.f; // minimum distance between non-moving entities
        const int cellSize = 500; // size of each cell in the grid
        const int numCols = (Utils::GlobalVars::lvlWidth - 20 + cellSize - 1) / cellSize; // number of columns in the grid
        const int numRows = (Utils::GlobalVars::lvlWidth - 20 + cellSize - 1) / cellSize; // number of rows in the grid
        std::vector<std::vector<std::vector<Entity*>>> grid(numCols, std::vector<std::vector<Entity*>>(numRows)); // 3D grid to store non-moving entities

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            int ranImg = rand() % listIMG.size();
            float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];

            Utils::Vector2D pos;
            bool positionValid = false;
            while (!positionValid) {
                int col = rand() % numCols;
                int row = rand() % numRows;
                int x = col * cellSize + rand() % cellSize;
                int y = row * cellSize + rand() % cellSize;
                pos = Utils::Vector2D(x, y);

                // check distance from entities in the same and adjacent cells
                positionValid = true;
                int startCol = std::max(0, col - 1);
                int endCol = std::min(numCols - 1, col + 1);
                int startRow = std::max(0, row - 1);
                int endRow = std::min(numRows - 1, row + 1);
                for (int c = startCol; c <= endCol; c++) {
                    for (int r = startRow; r <= endRow; r++) {
                        for (const auto &entity: grid[c][r]) {
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

            Drawing::Image *img = new Drawing::Image(g->drawing(), listIMG[ranImg], ang, true, "spritesheet.png");

            nonMovingEntitys[i].first = new Entity(pos, ang, img);
            nonMovingEntitys[i].first->setAngle(ang);

            // add entity to the grid
            int col = pos.x / cellSize;
            int row = pos.y / cellSize;
            grid[col][row].push_back(nonMovingEntitys[i].first);
        }

        Drawing::Image* spaceShip = new Drawing::Image(g->drawing(), std::string("ship"), 0.f, true, "spritesheet.png");
        spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        player1 = new Entity(Utils::GlobalVars::cameraPos, Utils::GlobalVars::playerAngle, spaceShip);

        // -------------------------------------------------------------------------------------


        g->sound()->playSound(Sound::SOUND_BG, 2);

        g->world()->initBackground();
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
        player1->setAngle(Utils::GlobalVars::playerAngle);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            Utils::Vector2D newPos = Utils::Vector2D(nonMovingEntitys[i].first->getOrigin());

            nonMovingEntitys[i].first->setOrigin(newPos);

            /*SDL_Rect worldPosRec = nonMovingEntitys[i].first->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::GlobalVars::WorldToScreen(worldPos, screenPos);

            SDL_Rect screenPosRect = {static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), worldPosRec.w, worldPosRec.h};

            char pos[256];
            snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)worldPosRec.x, (int)worldPosRec.y);
            SDL_Rect destR = { 0, 0, 0, 0 };
            TTF_SizeText(g->renderer()->m_fonts[1], pos, &destR.w, &destR.h);
            g->drawing()->string(std::string(pos), g->renderer()->m_fonts[1], { 255, 255, 255 }, Utils::Vector2D(screenPos.x, screenPos.y));

            if (nonMovingEntitys[i].second)
                g->drawing()->rectangle({255, 0, 0, 255}, screenPosRect);
            else
                g->drawing()->rectangle({0, 255, 0, 255}, screenPosRect);*/

            //SDL_SetRenderDrawColor(g->renderer()->renderer, 255, 0, 255, 48);
            //SDL_RenderDrawLines(g->renderer()->renderer, nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().data(), nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().size());
        }

        static Uint32 timeSinceLastProjectile = 0;
        const Uint32 projectileInterval = 250;

        if (g->event()->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint32 currentTime = SDL_GetTicks();
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
            playersProjectiles[i]->update();
            // Check if the projectile is out of bounds
            if (playersProjectiles[i]->isOffscreen() || !playersProjectiles[i]->getActiv()) {
                std::swap(playersProjectiles[i], playersProjectiles.back());
                playersProjectiles.pop_back();
            }
        }
    }

    void Game::postUpdate(float deltaTime) {
        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            SDL_Rect worldPosRec = nonMovingEntitys[i].first->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::GlobalVars::WorldToScreen(worldPos, screenPos);
            if (!isOnScreen)
                continue;

            for (int y = 0; y < playersProjectiles.size(); y++){
                if (!playersProjectiles[y]->getActiv())
                    continue;

                if (!nonMovingEntitys[i].second && playersProjectiles[y]->ProjectileHitsEntity(worldPosRec)) {
                    nonMovingEntitys[i].second = true;
                    playersProjectiles[y]->setActiv(false);
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
        g->world()->runBackground(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y, deltaTime);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            nonMovingEntitys[i].first->update();
        }

        player1->update();

        // Render the player's projectiles
        for (auto& projectile : playersProjectiles) {
            projectile->render();
        }

        /*if (Utils::GlobalVars::accesDebugMode)
        {
            g_drawing->string(std::string("Debug Mode:"), g_renderer->m_fonts[1], {255, 255, 255}, { 10, 45 });

            snprintf(pos, sizeof(pos), "1. Draw Hitboxes: %s", Utils::GlobalVars::drawHitboxes ? "On" : "Off");
            std::string strInfo = pos;
            g_drawing->string(strInfo, g_renderer->m_fonts[1], {255, 255, 255}, { 10, 65 });

            // Draw Hitbox Only for Debug Purposes
            if (Utils::GlobalVars::drawHitboxes) {
                SDL_SetRenderDrawColor(g_renderer->renderer, 48, 255, 48, 48);
                SDL_RenderDrawLines(g_renderer->renderer, player1->getHitbox()->hitbox_Polygon.data(), player1->getHitbox()->hitbox_Polygon.size());
            }
        }*/

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
        destScor.x = Utils::GlobalVars::windowWidth + 10;
        destScor.y = 1;
        g->drawing()->string(std::string("HI-SCORE"), g->renderer()->m_fonts[0], { 255, 0, 0 }, Utils::Vector2D(destScor.x, destScor.y));


        SDL_Rect destCon = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destCon.x = Utils::GlobalVars::windowWidth + 10;
        destCon.y = 192 - destCon.h;
        g->drawing()->string(std::string("CONDITION"), g->renderer()->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(destCon.x, destCon.y));

        SDL_Rect rec4 = { Utils::GlobalVars::windowWidth, 240, Utils::GlobalVars::infoWidth, 64 };
        g->drawing()->fillRectangle2({ 0, 255, 0, 255 }, rec4);

        g->world()->draw2DRadar(Utils::Vector2D(Utils::GlobalVars::windowWidth, 320), Utils::Vector2D(Utils::GlobalVars::infoWidth - 8, 448 - 8), (int)Utils::GlobalVars::cameraPos.x, (int)Utils::GlobalVars::cameraPos.y, Utils::Vector2D(Utils::GlobalVars::lvlWidth, Utils::GlobalVars::lvlHeight));
    }
} // Game