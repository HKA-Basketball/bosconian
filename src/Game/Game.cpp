#include "Game.h"
#include "../../Resources/imgs.h"
#include "../Utilities/GlobalVars.h"

namespace Game {
    Game::Game()
        : lvlEditor("lvl.ini")
        , lvlmgn(Utils::GlobalVars::lvlsInfos)
    {
        entities = new EntityManager();

        std::shared_ptr<Drawing::Texture> spaceShip = std::make_shared<Drawing::Texture>(std::string("ship"), 0.f, true, "spritesheet.png");
        spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        player1 = new Player(Utils::GlobalVars::cameraPos, Utils::GlobalVars::playerAngle, spaceShip);

        for (size_t i = 0; i < 5; i++) {
            Drawing::Texture* miniSpaceShip = new Drawing::Texture("ship", 0.f, true, "spritesheet.png");

            miniSpaceShip->setSize({42, 42});
            miniSpaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth + (i * 45), Utils::GlobalVars::windowHeight - 50));
            lives.push_back(miniSpaceShip);
        }

        Sound::g_sound->playSound(Sound::SOUND_BG, 2);
    }

    void Game::init()
    {
        player1->clearProjectiels();

        std::vector<float> list{0.f, 90.f, 45.f, 135.f, 180.f, -45.f, -90.f, -135.f};
        std::vector<std::string> listIMG{"bomb", "astroid-01", "astroid-02", "astroid-03"};
        std::vector<int> listPTS{20, 10, 10, 10};
        const float minDistance = 100.f; // minimum distance between non-moving entities
        const int cellSize = 500; // size of each cell in the grid
        const int numCols = (Utils::GlobalVars::lvlWidth + cellSize - 1) / cellSize; // number of columns in the grid
        const int numRows = (Utils::GlobalVars::lvlHeight + cellSize - 1) / cellSize; // number of rows in the grid
        std::vector<std::vector<std::vector<Entity*>>> grid(numCols, std::vector<std::vector<Entity*>>(numRows)); // 3D grid to store entities

        if (!Utils::GlobalVars::lvlEditorActive)
            Utils::GlobalVars::cameraPos = lvlmgn.getPlayerSpawnLocation();

        baseShipEntitys.resize(lvlmgn.getBaseShipsSpawnLocations().size());
        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (baseShipEntitys[i]) {
                delete baseShipEntitys[i];
                baseShipEntitys[i] = nullptr;
            }

            float ang = list[rand() % 2];

            baseShipEntitys[i] = new BaseEntity(lvlmgn.getBaseShipsSpawnLocations().at(i), ang);

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

        // -------------------------------------------------------------------------------------
        std::vector<Entity*> nonMovingEntitys;
        nonMovingEntitys.resize(50);
        entities->clearEntities();

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            if (nonMovingEntitys[i]) {
                LOG("Need to del!");
                delete nonMovingEntitys[i];
                nonMovingEntitys[i] = nullptr;
            }

            int ranImg = rand() % listIMG.size();
            float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];

            Utils::Vector2D pos;
            bool positionValid = false;
            int maxAttempts = 100; // Maximum number of attempts to find a valid position
            std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(listIMG[ranImg], ang, true, "spritesheet.png");

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
            entities->addEntity(nonMovingEntitys[i]);

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

    void Game::doLvlEditorStuff() {
        if (!Utils::GlobalVars::lvlEditorActive)
            return;

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_B)) {
            lvlEditor.placeBase(lvlmgn.getCurrentLevel(), Utils::GlobalVars::cameraPos);
            lvlmgn.updateLevels(Utils::GlobalVars::lvlsInfos);
            this->init();
        }
        if (Event::g_event->isKeyClicked(SDL_SCANCODE_P)) {
            lvlEditor.setPlayerSpawnPos(lvlmgn.getCurrentLevel(), Utils::GlobalVars::cameraPos);
            lvlmgn.updateLevels(Utils::GlobalVars::lvlsInfos);
            this->init();
        }
        if (Event::g_event->isKeyClicked(SDL_SCANCODE_U)) {
            lvlEditor.undoBase(lvlmgn.getCurrentLevel());
            lvlmgn.updateLevels(Utils::GlobalVars::lvlsInfos);
            this->init();
        }
        if (Event::g_event->isKeyClicked(SDL_SCANCODE_K)) {
            lvlEditor.saveLvls();
            lvlmgn.updateLevels(Utils::GlobalVars::lvlsInfos);
            this->init();
        }

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_M)) {
            lvlmgn.increaseLevel();
            this->init();
        }
        if (Event::g_event->isKeyClicked(SDL_SCANCODE_N)) {
            lvlmgn.decreaseLevel();
            this->init();
        }

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_C)) {
            Utils::GlobalVars::lvlEditorActive = false;
            lvlEditor.readLvls();
            lvlmgn.updateLevels(Utils::GlobalVars::lvlsInfos);
            lvlmgn.selectLevel(1);
            this->init();
        }
    }

    void Game::update(float deltaTime) {
        doLvlEditorStuff();

        g_world->update(deltaTime);

        player1->setOrigin(Utils::GlobalVars::cameraPos);
        player1->setAngle(Utils::GlobalVars::playerAngle);

        for (int i = 0; i < baseShipEntitys.size(); i++) {
            if (!baseShipEntitys[i]->isActive()) {
                delete baseShipEntitys[i];
                baseShipEntitys[i] = nullptr;
                std::swap(baseShipEntitys[i], baseShipEntitys.back());
                baseShipEntitys.pop_back();
                i--;
                continue;
            }

            baseShipEntitys[i]->update(deltaTime);
        }

        entities->update(deltaTime);

        player1->update(deltaTime);
        player1->updateProjectiels(deltaTime);

    }

    void Game::postUpdate(float deltaTime) {
        if (Utils::GlobalVars::lvlEditorActive)
            return;

        bool dead = false;

        for (int i = 0; i < entities->getEntities().size(); i++) {
            if (!entities->getEntities()[i]->isActive())
                continue;

            SDL_Rect worldPosRec = entities->getEntities()[i]->getHitbox()->getHitbox();
            Utils::Vector2D worldPos = {static_cast<float>(worldPosRec.x), static_cast<float>(worldPosRec.y)};
            Utils::Vector2D screenPos;
            bool isOnScreen = Utils::render::WorldToScreen(worldPos, screenPos);
            if (!isOnScreen)
                continue;

            if (player1->checkProjectiels(worldPosRec)) {
                entities->getEntities()[i]->setTriggerAnimation(true);
                Utils::GlobalVars::currenPTS += entities->getEntities()[i]->getPTS();
                if (Utils::GlobalVars::currenHiScore < Utils::GlobalVars::currenPTS) {
                    Utils::GlobalVars::currenHiScore = Utils::GlobalVars::currenPTS;
                }
            }

            if (Utils::Math::rectIntersect(player1->getHitbox()->getHitbox(), worldPosRec))
            {
                entities->getEntities()[i]->setTriggerAnimation(true);
                dead = true;
            }
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

                if (ent[x]->isActive() && player1->checkProjectiels(worldPosRec)) {
                    ent[x]->setTriggerAnimation(true);
                    Utils::GlobalVars::currenPTS += ent[x]->getPTS();
                    if (Utils::GlobalVars::currenHiScore < Utils::GlobalVars::currenPTS) {
                        Utils::GlobalVars::currenHiScore = Utils::GlobalVars::currenPTS;
                    }
                }
                if (ent[x]->isTriggerAnimation() && player1->checkProjectiels(worldPosRec)) {

                }

                if (Utils::Math::rectIntersect(player1->getHitbox()->getHitbox(), worldPosRec))
                {
                    ent[0]->setTriggerAnimation(true);
                    dead = true;
                }
            }

            if (baseShipEntitys[i]->getSpy()) {
                if (baseShipEntitys[i]->getSpy()->isActive() &&
                    player1->checkProjectiels(baseShipEntitys[i]->getSpy()->getHitbox()->getHitbox())) {
                    baseShipEntitys[i]->getSpy()->setTriggerAnimation(true);
                    Utils::GlobalVars::currenPTS += baseShipEntitys[i]->getSpy()->getPTS();
                    if (Utils::GlobalVars::currenHiScore < Utils::GlobalVars::currenPTS) {
                        Utils::GlobalVars::currenHiScore = Utils::GlobalVars::currenPTS;
                    }
                }

                if (Utils::Math::rectIntersect(player1->getHitbox()->getHitbox(),
                                               baseShipEntitys[i]->getSpy()->getHitbox()->getHitbox())) {
                    ent[0]->setTriggerAnimation(true);
                    dead = true;
                }
            }
        }

        if (dead)
        {
            // TODO: trigger Dead screen if ...
            player1->setLives(player1->getLives()-1);

            if (player1->getLives() <= 0) {
                player1->setLives(3);
                lvlmgn.selectLevel(1);
                Utils::GlobalVars::currenPTS = 0;
            }

            //player1->setActive(false);
            this->init();

            Utils::Config sw_cfg(".\\cfg\\config.ini");
            sw_cfg.add_item("HallOfFame", "hi-score", Utils::GlobalVars::currenHiScore);
            sw_cfg.write();
            sw_cfg.read();
        }

        if (count == 0) {
            lvlmgn.increaseRound();
            this->init();

            Utils::Config sw_cfg(".\\cfg\\config.ini");
            sw_cfg.add_item("HallOfFame", "hi-score", Utils::GlobalVars::currenHiScore);
            sw_cfg.write();
            sw_cfg.read();
        }
    }

    void Game::render(float deltaTime) {
        //Drawing
        g_world->renderBackground();


        entities->render(deltaTime);

        /*for (int i = 0; i < nonMovingEntitys.size(); i++) {
            if (!nonMovingEntitys[i]->isActive())
                continue;

            nonMovingEntitys[i]->draw(deltaTime);*/

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
        //}

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


        // -------------------------------------------------------------------------------------
        char text[32];
        char pos[256];

        snprintf(text, sizeof(text), "FPS: %i", getFPS());
        Drawing::g_drawing->string(std::string(text), Renderer::g_renderer->m_fonts[0], {255, 255, 255}, { 10, 5 });

        snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)Utils::GlobalVars::cameraPos.x, (int)Utils::GlobalVars::cameraPos.y);
        SDL_Rect destR = { 0, 0, 0, 0 };
        TTF_SizeText(Renderer::g_renderer->m_fonts[0], pos, &destR.w, &destR.h);
        Drawing::g_drawing->string(std::string(pos), Renderer::g_renderer->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(Utils::GlobalVars::windowWidth - (destR.w + 15), 5));

        // -------------------------------------------------------------------------------------

        HUD(baseShipPos);
    }

    void Game::HUD(std::vector<Utils::Vector2D> baseShipPos) {
        Drawing::g_drawing->fillRectangle2({ 0, 0, 0, 255 }
                , { Utils::GlobalVars::windowWidth, 0, Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight });

        SDL_Rect destScor = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destScor.x = Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10;
        destScor.y = 1;
        Drawing::g_drawing->string(std::string("HI-SCORE"), Renderer::g_renderer->m_fonts[0], { 255, 0, 0 }
                                    , Utils::Vector2D(destScor.x, destScor.y), 1);

        destScor.y += 28;

        Drawing::g_drawing->string(std::to_string(Utils::GlobalVars::currenHiScore), Renderer::g_renderer->m_fonts[0], { 255, 255, 255 }
                                    , Utils::Vector2D(destScor.x, destScor.y), 1);


        destScor.y += 38*2;
        Drawing::g_drawing->string(std::to_string(Utils::GlobalVars::currenPTS), Renderer::g_renderer->m_fonts[0], { 255, 255, 255 }
                                    , Utils::Vector2D(destScor.x, destScor.y), 1);


        Drawing::g_drawing->string(std::string("CONDITION"), Renderer::g_renderer->m_fonts[0], { 255, 255, 255 }
                                    , Utils::Vector2D(Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth - 10, 192), 1);

        Drawing::g_drawing->fillRectangle2(Utils::GlobalVars::conditionColors[Utils::GlobalVars::condition]
                                     , { Utils::GlobalVars::windowWidth, 240, Utils::GlobalVars::infoWidth, 64 });

        std::string condition = Utils::GlobalVars::condition == 0 ? "GREEN" : Utils::GlobalVars::condition == 1 ? "YELLOW" : "RED!!!";

        Drawing::g_drawing->string(condition, Renderer::g_renderer->m_fonts[0], { 0, 0, 0, 255 }
                , Utils::Vector2D(Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth/2, 240+32), 2);

        g_world->render2DRadar(Utils::Vector2D(Utils::GlobalVars::windowWidth, 320)
                                    , Utils::Vector2D(Utils::GlobalVars::infoWidth, 448), baseShipPos);

        for (size_t i = 0; i < player1->getLives(); i++) {
            if (!lives[i])
                continue;

            lives[i]->draw();
        }

        if (Utils::GlobalVars::lvlEditorActive)
        {
            int textWidth, textHeight;
            TTF_SizeText(Renderer::g_renderer->m_fonts[1], "C: Exit Editor Mode", &textWidth, &textHeight);
            textHeight += 2;
            int y_Offset = 50;

            Drawing::g_drawing->fillRectangle2({48, 48, 48, 150}, {5, y_Offset-5, textWidth+10, textHeight*9+10});

            Drawing::g_drawing->string(std::string("Editor Mode!"), Renderer::g_renderer->m_fonts[1], { 255, 0, 0 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("Current Level: ") + std::to_string(lvlmgn.getCurrentLevel()), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("B: Add Base"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("P: Set Player Spawn"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("U: Undo"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("K: Save in File"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("M: Next Level"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("N: Previous Level"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            y_Offset += textHeight;

            Drawing::g_drawing->string(std::string("C: Exit Editor Mode"), Renderer::g_renderer->m_fonts[1], { 255, 255, 255 }
                    , Utils::Vector2D(10, y_Offset), 0);
            //y_Offset += textHeight;
        }
    }
} // Game