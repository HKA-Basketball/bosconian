#include <fileapi.h>
#include "./src/Utilities/Logging.h"
#include "./src/Utilities/GlobalVars.h"

#include "./src/Renderer/Window.h"
#include "./src/Renderer/Renderer.h"
#include "./src/Drawing/Graphics.h"
#include "./src/Event/EventManager.h"
#include "./src/Game/Entity.h"
#include "./src/Game/Hitbox.h"
#include "./src/Game/World.h"
#include "./src/Sound/SoundManager.h"

#include "./Resources/imgs.h"


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

int main(int argc, char* args[])
{
    CreateDirectoryA(".\\Logs", NULL);

    Renderer::Window* g_window = new Renderer::Window("Bosconian - Playing", Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);

    if (!g_window) {
        LOG(std::string("Could not create window: ") + SDL_GetError());
        return 0;
    }

    Renderer::RendererSDL* g_renderer = new Renderer::RendererSDL(g_window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!g_renderer) {
        g_renderer->clearAll();
        SDL_DestroyWindow(g_window->sdl_HWND);
        SDL_Quit();
        return 0;
    }


    Drawing::Graphics* g_drawing = new Drawing::Graphics(g_renderer);
    if (!g_drawing) {
        g_renderer->clearAll();
        SDL_DestroyWindow(g_window->sdl_HWND);
        SDL_Quit();
        return 0;
    }

    Game::World* g_world = new Game::World(g_drawing);
    if (!g_world) {
        g_renderer->clearAll();
        SDL_DestroyWindow(g_window->sdl_HWND);
        SDL_Quit();
        return 0;
    }

    Event::EventManager* g_event = new Event::EventManager();
    if (!g_event)
    {
        LOG(std::string("Error: EventManager"));
        g_renderer->clearAll();
        SDL_DestroyWindow(g_window->sdl_HWND);
        SDL_Quit();
        return 0;
    }

    Sound::SoundManager* g_sound = new Sound::SoundManager();
    if (!g_sound)
    {
        LOG(std::string("Error: EventManager"));
        g_renderer->clearAll();
        SDL_DestroyWindow(g_window->sdl_HWND);
        SDL_Quit();
        return 0;
    }

    g_sound->playSound(Sound::SOUND_BG, 4);

    g_world->initBackground();

    // TODO: Move
    // Only for testing
    // -------------------------------------------------------------------------------------
    std::vector<std::pair<Game::Entity*, Drawing::Image*>> nonMovingEntitys;
    nonMovingEntitys.resize(50);

    std::vector<float> list{0.f, 45.f, 90.f, 135.f, 180.f, -45.f, -90.f, -135.f};
    std::vector<const char*> listIMG{"../Resources/bomb.png", "../Resources/astroid-01.png", "../Resources/astroid-02.png", "../Resources/astroid-03.png"};
    for (int i = 0; i < nonMovingEntitys.size(); i++)
    {
        float ang = list[rand() % list.size()];
        Utils::Vector2D pos = Utils::Vector2D(std::rand() % (Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth), std::rand() % (Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth));
        Drawing::Image* img = new Drawing::Image(g_renderer->renderer, listIMG[rand() % listIMG.size()], ang);
        img->setPos(Utils::Vector2D(pos.x, pos.y) - Utils::GlobalVars::playerPos);
        img->worldPos = Utils::Vector2D(pos.x, pos.y);
        nonMovingEntitys[i].second = img;

        nonMovingEntitys[i].first = new Game::Entity(pos - Utils::GlobalVars::playerPos, ang, img);
        nonMovingEntitys[i].first->setAngle(ang);
        nonMovingEntitys[i].first->getHitbox()->updateHitboxPos(Utils::Vector2D(pos.x, pos.y) - Utils::GlobalVars::playerPos);
    }

    Drawing::Image* spaceShip = new Drawing::Image(g_renderer->renderer, space_ship, sizeof(space_ship), Utils::Vector2D(60.f, 64.f), 0.f);
    spaceShip->setPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
    Game::Entity* player1 = new Game::Entity(Utils::GlobalVars::playerPos, Utils::GlobalVars::playerAngle, spaceShip);

    player1->getHitbox()->updateHitboxPos(Utils::Vector2D(Utils::GlobalVars::windowWidth / 2 - (60 / 2), Utils::GlobalVars::windowHeight / 2 - (64 / 2)));
    // -------------------------------------------------------------------------------------

    char text[32];
    char pos[256];

    //Loop
    while (!g_event->startLogging())
    {
        g_event->manageGameVars();
        g_renderer->beginScene();

        //Drawing
        g_world->runBackground(Utils::GlobalVars::playerPos.x, Utils::GlobalVars::playerPos.y);

        // Only for testing
        // -------------------------------------------------------------------------------------
        player1->setAngle(Utils::GlobalVars::playerAngle);

        for (int i = 0; i < nonMovingEntitys.size(); i++) {
            nonMovingEntitys[i].first->update();
            Utils::Vector2D newPos = Utils::Vector2D(nonMovingEntitys[i].second->worldPos - Utils::GlobalVars::playerPos);
            nonMovingEntitys[i].first->setOrigin(newPos);

            //SDL_SetRenderDrawColor(g_renderer->renderer, 255, 0, 255, 48);
            //SDL_RenderDrawLines(g_renderer->renderer, nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().data(), nonMovingEntitys[i].first->getHitbox()->getHitboxPolygon().size());
        }

        //player1->move2Pos(Utils::GlobalVars::playerPos, 1.f);
        player1->update();

        //SDL_SetRenderDrawColor(g_renderer->renderer, 255, 0, 255, 48);
        //SDL_RenderDrawLines(g_renderer->renderer, player1->getHitbox()->getHitboxPolygon().data(), player1->getHitbox()->getHitboxPolygon().size());


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


        snprintf(text, sizeof(text), "FPS: %i", getFPS());
        g_drawing->string(std::string(text), g_renderer->m_fonts[0], {255, 255, 255}, { 10, 5 });

        snprintf(pos, sizeof(pos), "Pos: ( %i - %i )", (int)Utils::GlobalVars::playerPos.x, (int)Utils::GlobalVars::playerPos.y);
        SDL_Rect destR = { 0, 0, 0, 0 };
        TTF_SizeText(g_renderer->m_fonts[0], pos, &destR.w, &destR.h);
        g_drawing->string(std::string(pos), g_renderer->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(Utils::GlobalVars::windowWidth - (destR.w + 15), 5));

        // -------------------------------------------------------------------------------------


        // TODO: Move to UI Class
        SDL_Rect rec3 = { Utils::GlobalVars::windowWidth, 0, Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight };
        g_drawing->fillRectangle2({ 0, 0, 0, 255 }, rec3);

        SDL_Rect destScor = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destScor.x = Utils::GlobalVars::windowWidth + 10;
        destScor.y = 1;
        g_drawing->string(std::string("HI-SCORE"), g_renderer->m_fonts[0], { 255, 0, 0 }, Utils::Vector2D(destScor.x, destScor.y));


        SDL_Rect destCon = { 0, 0, Utils::GlobalVars::infoWidth, 0 };
        destCon.x = Utils::GlobalVars::windowWidth + 10;
        destCon.y = 192 - destCon.h;
        g_drawing->string(std::string("CONDITION"), g_renderer->m_fonts[0], { 255, 255, 255 }, Utils::Vector2D(destCon.x, destCon.y));

        SDL_Rect rec4 = { Utils::GlobalVars::windowWidth, 240, Utils::GlobalVars::infoWidth, 64 };
        g_drawing->fillRectangle2({ 0, 255, 0, 255 }, rec4);

        g_world->draw2DRadar(Utils::Vector2D(Utils::GlobalVars::windowWidth, 320), Utils::Vector2D(Utils::GlobalVars::infoWidth - 8, 448 - 8), (int)Utils::GlobalVars::playerPos.x, (int)Utils::GlobalVars::playerPos.y, Utils::Vector2D(Utils::GlobalVars::lvlWidth, Utils::GlobalVars::lvlHeight));


        g_renderer->endScene();
    }

    g_renderer->clearAll();
    SDL_DestroyWindow(g_window->sdl_HWND);
    SDL_Quit();

    return 0;
}
