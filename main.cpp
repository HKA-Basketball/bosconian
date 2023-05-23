#include <fileapi.h>

#include "./src/Utilities/Initializer.h"
#include "./src/Game/Game.h"
#include "./src/GUI/Menu.h"

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

    SDL_Rect menuRect = {Utils::GlobalVars::windowWidth/2, Utils::GlobalVars::windowHeight/2, 250, 250};
    menuRect.x -= menuRect.w/2;
    menuRect.y -= menuRect.h/2;

    Menu::Menu menu(g->drawing(), g->event(), g->renderer()->m_fonts[0]
                    , menuRect, {48, 48, 48, 255}
                    , {255, 255, 255, 255}, 45);
    menu.addOption("Start");
    menu.addOption("Options");
    menu.addOption("Exit");


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
            // Update menu
            menu.handleEvent();

            // for our background if needed
            g->world()->update(deltaTime);
        }

        g->renderer()->beginScene();

        g_game->render(deltaTime);

        if (Utils::GlobalVars::menuActive) {
            // Render Menu
            menu.render();
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
