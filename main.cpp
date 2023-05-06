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

    //Loop
    while (!g->event()->logging())
    {
        g->event()->manageGameVars();
        g->renderer()->beginScene();

        g_game->playTest();

        g->renderer()->endScene();
    }

    g->renderer()->clearAll();
    SDL_DestroyWindow(g->window()->sdl_HWND);
    SDL_Quit();

    return 0;
}
