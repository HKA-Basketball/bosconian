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

    Uint32 previousTime = SDL_GetTicks64();
    //Loop
    while (!g->event()->logging())
    {
        g->renderer()->beginScene();

        Uint32 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        g->event()->manageGameVars(deltaTime);

        g_game->playTest(deltaTime);

        g->renderer()->endScene();

        Uint32 frameTime = SDL_GetTicks64() - currentTime;
        if (frameTime < 1000 / 120) {
            SDL_Delay((1000 / 120) - frameTime);
        }
    }

    g->renderer()->clearAll();
    SDL_DestroyWindow(g->window()->sdl_HWND);
    SDL_Quit();

    return 0;
}
