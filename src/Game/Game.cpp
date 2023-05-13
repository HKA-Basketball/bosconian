#include "Game.h"
#include "../../Resources/imgs.h"

namespace Game {
    Game::Game(Initialization::Initializer *g) : g(g) { }

    void Game::initOnce()
    {
        // TODO: Move
        // Only for testing
        // -------------------------------------------------------------------------------------
        nonMovingEntitys.resize(50);

        std::vector<float> list{0.f, 90.f, 45.f, 135.f, 180.f, -45.f, -90.f, -135.f};
        std::vector<const char*> listIMG{"../Resources/bomb.png", "../Resources/astroid-01.png", "../Resources/astroid-02.png", "../Resources/astroid-03.png", "../Resources/base.png"};
        for (int i = 0; i < nonMovingEntitys.size(); i++)
        {
            int ranImg = rand() % listIMG.size();
            float ang = ranImg == 4 ? list[rand() % 2] : list[rand() % list.size()];
            Utils::Vector2D pos = Utils::Vector2D(std::rand() % (Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth), std::rand() % (Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth));
            Drawing::Image* img = new Drawing::Image(g->renderer()->renderer, listIMG[ranImg], ang);
            img->setPos(Utils::Vector2D(pos.x, pos.y) - Utils::GlobalVars::cameraPos);
            img->worldPos = Utils::Vector2D(pos.x, pos.y);
            nonMovingEntitys[i].second = img;

            nonMovingEntitys[i].first = new Entity(pos - Utils::GlobalVars::cameraPos, ang, img);
            nonMovingEntitys[i].first->setAngle(ang);
            nonMovingEntitys[i].first->getHitbox()->updateHitboxPos(Utils::Vector2D(pos.x, pos.y) - Utils::GlobalVars::cameraPos);
        }

        Drawing::Image* spaceShip = new Drawing::Image(g->renderer()->renderer, space_ship, sizeof(space_ship), Utils::Vector2D(60.f, 64.f), 0.f);
        spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        player1 = new Entity(Utils::GlobalVars::cameraPos, Utils::GlobalVars::playerAngle, spaceShip);

        player1->getHitbox()->updateHitboxPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
        // -------------------------------------------------------------------------------------


        g->sound()->playSound(Sound::SOUND_BG, 4);

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

    void Game::playTest(float deltaTime) {
        static bool once = false;
        if (!once) {
            initOnce();
            once = true;
        }

        static Uint32 timeSinceLastProjectile = 0;
        const Uint32 projectileInterval = 500;

        if (g->event()->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                // Add a new Projectile object to the vector
                Utils::Vector2D screenPos;
                Utils::GlobalVars::WorldToScreen(Utils::GlobalVars::cameraPos, screenPos);
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
            if (playersProjectiles[i]->isOffscreen()) {
                std::swap(playersProjectiles[i], playersProjectiles.back());
                playersProjectiles.pop_back();
            }
        }


        //Drawing
        g->world()->runBackground(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y, deltaTime);

        // Only for testing
        // -------------------------------------------------------------------------------------
        player1->setAngle(Utils::GlobalVars::playerAngle);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            nonMovingEntitys[i].first->update();

            Utils::Vector2D newPos = Utils::Vector2D(nonMovingEntitys[i].second->worldPos);
            Utils::Vector2D newPosScreen;
            Utils::GlobalVars::WorldToScreen(newPos, newPosScreen);

            nonMovingEntitys[i].first->setOrigin(newPosScreen);

            //SDL_SetRenderDrawColor(g->renderer()->renderer, 255, 0, 255, 48);
            //SDL_RenderDrawLines(g->renderer()->renderer, nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().data(), nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().size());
        }

        //player1->move2Pos(Utils::GlobalVars::cameraPos, 1.f);
        player1->update();

        //SDL_SetRenderDrawColor(g_renderer->renderer, 255, 0, 255, 48);
        //SDL_RenderDrawLines(g_renderer->renderer, player1->getHitbox()->getHitboxPolygon().data(), player1->getHitbox()->getHitboxPolygon().size());



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