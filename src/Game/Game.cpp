#include "Game.h"
#include "../../Resources/imgs.h"
#include "../Utilities/GlobalVars.h"

namespace Game {
    Game::Game(Initialization::Initializer *g) : g(g) {
        lvlmgn = new LevelManager(Utils::GlobalVars::lvlsInfos);

        std::shared_ptr<Drawing::Texture> spaceShip = std::make_shared<Drawing::Texture>(g->drawing(), std::string("ship"), 0.f, true, "spritesheet.png");
        spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        player1 = new Player(Utils::GlobalVars::cameraPos, Utils::GlobalVars::playerAngle, spaceShip);

        for (size_t i = 0; i < 5; i++) {
            Drawing::Texture* miniSpaceShip = new Drawing::Texture(g->drawing(), "ship", 0.f, true, "spritesheet.png");

            miniSpaceShip->setSize({42, 42});
            miniSpaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth + (i * 45), Utils::GlobalVars::windowHeight - 50));
            lives.push_back(miniSpaceShip);
        }

        g->sound()->playSound(Sound::SOUND_BG, 2);
    }

    void Game::init()
    {
        std::vector<float> list{0.f, 90.f, 45.f, 135.f, 180.f, -45.f, -90.f, -135.f};
        std::vector<std::string> listIMG{"bomb", "astroid-01", "astroid-02", "astroid-03"};
        std::vector<int> listPTS{20, 10, 10, 10};
        const float minDistance = 100.f; // minimum distance between non-moving entities
        const int cellSize = 500; // size of each cell in the grid
        const int numCols = (Utils::GlobalVars::lvlWidth + cellSize - 1) / cellSize; // number of columns in the grid
        const int numRows = (Utils::GlobalVars::lvlHeight + cellSize - 1) / cellSize; // number of rows in the grid
        std::vector<std::vector<std::vector<Entity*>>> grid(numCols, std::vector<std::vector<Entity*>>(numRows)); // 3D grid to store non-moving entities


        Utils::GlobalVars::cameraPos = lvlmgn->getPlayerSpawnLocation();

        baseShipEntitys.resize(lvlmgn->getBaseShipsSpawnLocations().size());
        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (baseShipEntitys[i]) {
                delete baseShipEntitys[i];
                baseShipEntitys[i] = nullptr;
            }

            float ang = list[rand() % 2];

            baseShipEntitys[i] = new BaseEntity(lvlmgn->getBaseShipsSpawnLocations().at(i), ang, g->drawing());

            // Mark the grid cells around the base ship as occupied
            int col = baseShipEntitys[i]->getEntitys()[0]->getOrigin().x / cellSize;
            int row = baseShipEntitys[i]->getEntitys()[0]->getOrigin().y / cellSize;

            int startCol = std::max(0, col - 1);
            int endCol = std::min(numCols - 1, col + 1);
            int startRow = std::max(0, row - 1);
            int endRow = std::min(numRows - 1, row + 1);

            for (int c = startCol; c <= endCol; c++) {
                for (int r = startRow; r <= endRow; r++) {
                    grid[c][r].push_back(baseShipEntitys[i]->getEntitys()[0]);
                }
            }
        }


        playersProjectiles.clear();
        // TODO: Move
        // Only for testing
        // -------------------------------------------------------------------------------------
        nonMovingEntitys.resize(50);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            if (nonMovingEntitys[i]) {
                delete nonMovingEntitys[i];
                nonMovingEntitys[i] = nullptr;
            }

            int ranImg = rand() % listIMG.size();
            float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];

            Utils::Vector2D pos;
            bool positionValid = false;
            int maxAttempts = 100; // Maximum number of attempts to find a valid position
            std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(g->drawing(), listIMG[ranImg], ang, true, "spritesheet.png");

            while (!positionValid && maxAttempts > 0) {
                int col = rand() % numCols;
                int row = rand() % numRows;
                int x = col * cellSize + rand() % cellSize;
                int y = row * cellSize + rand() % cellSize;
                pos = Utils::Vector2D(x, y);

                // Check if the position is within the map boundaries
                if (pos.x >= 0 && pos.x < Utils::GlobalVars::lvlWidth - img->getSize().x && pos.y >= 0 && pos.y < Utils::GlobalVars::lvlHeight - img->getSize().y) {

                    float distToPlayer = (pos - Utils::GlobalVars::cameraPos).length();
                    if (distToPlayer >= minDistance) {
                        // Check distance from entities in the same and adjacent cells
                        positionValid = true;
                        int startCol = std::max(0, col - 1);
                        int endCol = std::min(numCols - 1, col + 1);
                        int startRow = std::max(0, row - 1);
                        int endRow = std::min(numRows - 1, row + 1);

                        for (int c = startCol; c <= endCol; c++) {
                            for (int r = startRow; r <= endRow; r++) {
                                for (const auto &entity: grid[c][r]) {
                                    float distX = std::abs(pos.x - entity->getOrigin().x);
                                    float distY = std::abs(pos.y - entity->getOrigin().y);
                                    int otherEntityWidth = entity->getSize().x;
                                    int otherEntityHeight = entity->getSize().y;
                                    float minDistanceWithSizeX = minDistance + img->getSize().x + otherEntityWidth;
                                    float minDistanceWithSizeY = minDistance + img->getSize().y + otherEntityHeight;

                                    if (distX < minDistanceWithSizeX && distY < minDistanceWithSizeY) {
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
                }

                maxAttempts--;
            }

            nonMovingEntitys[i] = new Entity(pos, ang, img, listPTS[ranImg]);
            nonMovingEntitys[i]->setAngle(ang);
            nonMovingEntitys[i]->setBehavior(new NonMovingBehavior());

            // add entity to the grid
            int col = pos.x / cellSize;
            int row = pos.y / cellSize;
            grid[col][row].push_back(nonMovingEntitys[i]);
        }
        // -------------------------------------------------------------------------------------
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
        player1->update(deltaTime);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            if (!nonMovingEntitys[i]->isActive())
                continue;

            nonMovingEntitys[i]->update(deltaTime);
        }

        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (!baseShipEntitys[i]->isActive())
                continue;

            baseShipEntitys[i]->update(deltaTime);
        }

        static Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 250;

        if (g->event()->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint64 currentTime = SDL_GetTicks64();
            if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                g->sound()->playSound(Sound::SOUND_SHOOT, 3, 0);
                // Add a new Projectile object to the vector
                Projectile* newProjectile1 = new Projectile(g->drawing(), Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y
                                                            , 1000 * deltaTime, Utils::GlobalVars::playerAngle);
                Projectile* newProjectile2 = new Projectile(g->drawing(), Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y
                                                            , 1000 * deltaTime, Utils::GlobalVars::playerAngle + 180);
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
            if (!nonMovingEntitys[i]->isActive())
                continue;

            SDL_Rect worldPosRec = nonMovingEntitys[i]->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::render::WorldToScreen(worldPos, screenPos);
            if (!isOnScreen)
                continue;

            for (int y = 0; y < playersProjectiles.size(); y++){
                if (!playersProjectiles[y]->getActive())
                    continue;

                if (nonMovingEntitys[i]->isActive() && playersProjectiles[y]->ProjectileHitsEntity(worldPosRec)) {
                    nonMovingEntitys[i]->setTriggerAnimation(true);
                    playersProjectiles[y]->setActive(false);
                    Utils::GlobalVars::currenPTS += nonMovingEntitys[i]->getPTS();
                    if (Utils::GlobalVars::currenHiScore < Utils::GlobalVars::currenPTS) {
                        Utils::GlobalVars::currenHiScore = Utils::GlobalVars::currenPTS;
                    }

                    break;
                }
            }

            if (Utils::Math::rectIntersect(player1->getHitbox()->getHitbox(), worldPosRec))
            {
                // TODO: trigger Dead screen if ...
                player1->setLives(player1->getLives()-1);

                if (player1->getLives() <= 0) {
                    player1->setLives(3);
                    lvlmgn->selectLevel(1);
                    Utils::GlobalVars::currenPTS = 0;
                }

                //player1->setActive(false);
                this->init();

                Utils::Config sw_cfg(".\\cfg\\config.ini");
                sw_cfg.add_item("HallOfFame", "hi-score", Utils::GlobalVars::currenHiScore);
                sw_cfg.write();
                sw_cfg.read();
            }

            /*if (!nonMovingEntitys[i]->isActive()) {
                std::swap(nonMovingEntitys[i], nonMovingEntitys.back());
                nonMovingEntitys.pop_back();
            }*/
        }

        int count = 0;

        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (!baseShipEntitys[i]->isActive())
                continue;
            count++;

            std::vector<Entity*> ent = baseShipEntitys[i]->getEntitys();
            for (int x = 0; x < ent.size(); x++) {

                SDL_Rect worldPosRec = ent[x]->getHitbox()->getHitbox();
                Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
                Utils::Vector2D screenPos;
                bool isOnScreen = Utils::render::WorldToScreen(worldPos, screenPos);

                for (int y = 0; y < playersProjectiles.size(); y++) {
                    if (!playersProjectiles[y]->getActive())
                        continue;

                    if (ent[x]->isActive() && playersProjectiles[y]->ProjectileHitsEntity(worldPosRec)) {
                        ent[x]->setTriggerAnimation(true);
                        playersProjectiles[y]->setActive(false);
                        Utils::GlobalVars::currenPTS += ent[x]->getPTS();
                        if (Utils::GlobalVars::currenHiScore < Utils::GlobalVars::currenPTS) {
                            Utils::GlobalVars::currenHiScore = Utils::GlobalVars::currenPTS;
                        }

                        break;
                    }
                    if (ent[x]->isTriggerAnimation() && playersProjectiles[y]->ProjectileHitsEntity(worldPosRec)) {
                        playersProjectiles[y]->setActive(false);
                        break;
                    }
                }
            }
        }

        if (count == 0) {
            lvlmgn->increaseRound();
            this->init();

            Utils::Config sw_cfg(".\\cfg\\config.ini");
            sw_cfg.add_item("HallOfFame", "hi-score", Utils::GlobalVars::currenHiScore);
            sw_cfg.write();
            sw_cfg.read();
        }
    }

    void Game::render(float deltaTime) {
        //Drawing
        g->world()->renderBackground();

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            if (!nonMovingEntitys[i]->isActive())
                continue;

            nonMovingEntitys[i]->draw(deltaTime);

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

            if (!nonMovingEntitys[i]->isActive())
                g->drawing()->rectangle({255, 0, 0, 255}, screenPosRect);
            else
                g->drawing()->rectangle({0, 255, 0, 255}, screenPosRect);*/
        }

        std::vector<Utils::Vector2D> baseShipPos;
        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (!baseShipEntitys[i]->isActive())
                continue;

            baseShipEntitys[i]->draw(deltaTime);
            baseShipPos.push_back(baseShipEntitys[i]->getEntitys()[0]->getOrigin());

            /*std::vector<Entity*> ent = baseShipEntitys[i]->getEntitys();
            for (int x = 0; x < ent.size(); x++) {
                SDL_Rect worldPosRec = ent[x]->getHitbox()->getHitbox();
                Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
                Utils::Vector2D screenPos;
                bool isOnScreen = Utils::render::WorldToScreen(worldPos, screenPos);

                SDL_Rect screenPosRect = {static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), worldPosRec.w,
                                          worldPosRec.h};

                char pos[256];
                snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int) worldPosRec.x, (int) worldPosRec.y);
                SDL_Rect destR = {0, 0, 0, 0};
                TTF_SizeText(g->renderer()->m_fonts[1], pos, &destR.w, &destR.h);
                g->drawing()->string(std::string(pos), g->renderer()->m_fonts[1], {255, 255, 255},
                                     Utils::Vector2D(screenPos.x, screenPos.y));

                if (!ent[x]->isActive())
                    g->drawing()->rectangle({255, 0, 0, 255}, screenPosRect);
                else
                    g->drawing()->rectangle({0, 255, 0, 255}, screenPosRect);
            }*/
        }

        player1->draw(deltaTime);

        // Render the player's projectiles
        for (auto& projectile : playersProjectiles) {
            projectile->render();
        }

        // -------------------------------------------------------------------------------------
        char text[32];
        char pos[256];

        snprintf(text, sizeof(text), "FPS: %i", getFPS());
        g->drawing()->string(std::string(text), g->renderer()->m_fonts[0], {255, 255, 255}, { 10, 5 });

        snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)Utils::GlobalVars::cameraPos.x, (int)Utils::GlobalVars::cameraPos.y);
        SDL_Rect destR = { 0, 0, 0, 0 };
        TTF_SizeText(g->renderer()->m_fonts[0], pos, &destR.w, &destR.h);
        g->drawing()->string(std::string(pos), g->renderer()->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(Utils::GlobalVars::windowWidth - (destR.w + 15), 5));

        // -------------------------------------------------------------------------------------

        HUD(baseShipPos);
    }

    void Game::HUD(std::vector<Utils::Vector2D> baseShipPos) {
        g->drawing()->fillRectangle2({ 0, 0, 0, 255 }
                , { Utils::GlobalVars::windowWidth, 0, Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight });

        SDL_Rect destScor = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destScor.x = Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10;
        destScor.y = 1;
        g->drawing()->string(std::string("HI-SCORE"), g->renderer()->m_fonts[0], { 255, 0, 0 }
                , Utils::Vector2D(destScor.x, destScor.y), 1);


        g->drawing()->string(std::to_string(Utils::GlobalVars::currenHiScore), g->renderer()->m_fonts[0], { 255, 255, 255 }
                , Utils::Vector2D(destScor.x, destScor.y + 28), 1);


        g->drawing()->string(std::to_string(Utils::GlobalVars::currenPTS), g->renderer()->m_fonts[0], { 255, 255, 255 }
                , Utils::Vector2D(destScor.x, destScor.y + (28 + (38*2))), 1);


        g->drawing()->string(std::string("CONDITION"), g->renderer()->m_fonts[0], { 255, 255, 255 }
                , Utils::Vector2D(Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10, 192), 1);

        g->drawing()->fillRectangle2({ 0, 255, 0, 255 }, { Utils::GlobalVars::windowWidth, 240, Utils::GlobalVars::infoWidth, 64 });

        g->world()->render2DRadar(Utils::Vector2D(Utils::GlobalVars::windowWidth, 320)
                                  , Utils::Vector2D(Utils::GlobalVars::infoWidth, 448), baseShipPos);

        for (size_t i = 0; i < player1->getLives(); i++) {
            if (!lives[i])
                continue;

            lives[i]->draw();
        }

    }
} // Game