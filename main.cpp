#include <fileapi.h>

#include "./src/Utilities/Initializer.h"
#include "./src/Game/Game.h"

int main(int argc, char* args[])
{
    CreateDirectoryA(".\\Logs", NULL);

    Initialization::Initializer* g = Initialization::Initializer::getInstance();
    if (!g->initGameObjs())
    {
        LOG(std::string("Initialization failed!"));
        return 0;
    }

    Game::Game* g_game = new Game::Game(g);
    g_game->init();
    g_game->update(0.f);

    Uint32 previousTime = SDL_GetTicks64();
    //Loop
    while (!g->event()->logging())
    {
        Uint32 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        g->event()->manageGameVars(deltaTime);

        if (!Utils::GlobalVars::menuActive) {
            g_game->update(deltaTime);
            g_game->postUpdate(deltaTime);
        }
        else {
            // Update menu data?
        }

        g->renderer()->beginScene();

        g_game->render(deltaTime);

        if (Utils::GlobalVars::menuActive) {
            // Render Menu
            g->drawing()->string(std::string("Menu WIP"), g->renderer()->m_fonts[0], { 255, 0, 0 }, Utils::Vector2D(100, 100));

        }

        g->renderer()->endScene();

        /*Uint32 frameTime = SDL_GetTicks64() - currentTime;
        if (frameTime < 1000 / 120) {
            SDL_Delay((1000 / 120) - frameTime);
        }*/
    }

    g->renderer()->clearAll();
    SDL_DestroyWindow(g->window()->sdl_HWND);
    SDL_Quit();

    return 0;
}
