#include <fileapi.h>

#include "./src/Utilities/Initializer.h"
#include "./src/Game/Game.h"
#include "./src/GUI/Menu.h"

int main(int argc, char* args[])
{
    CreateDirectoryA(".\\Logs", NULL);
    CreateDirectoryA(".\\cfg", NULL);


    Utils::Config lvl_cfg(".\\cfg\\level.ini");

    Utils::Level level1;
    level1.lvlNum = 1;
    level1.baseShipsPos = {{10, 20}, {30, 40}};
    level1.playerPos = {100, 200};
    Utils::GlobalVars::lvlsInfos.push_back(level1);

    Utils::Level level2;
    level2.lvlNum = 2;
    level2.baseShipsPos = {{50, 60}, {70, 80}};
    level2.playerPos = {300, 400};
    Utils::GlobalVars::lvlsInfos.push_back(level2);

    lvl_cfg.add_item("Level", "baseShipPos", Utils::GlobalVars::lvlsInfos);

    //lvl_cfg.write();
    lvl_cfg.read();

    printf("LOG: lvlNum: %d, baseShipsPos: %f, %f, playerPos: %f, %f \n", Utils::GlobalVars::lvlsInfos.at(0).lvlNum
           , Utils::GlobalVars::lvlsInfos.at(0).baseShipsPos.at(0).x
           , Utils::GlobalVars::lvlsInfos.at(0).baseShipsPos.at(0).y
           , Utils::GlobalVars::lvlsInfos.at(0).playerPos.x
           , Utils::GlobalVars::lvlsInfos.at(0).playerPos.y);

    Utils::Config frames_cfg(".\\cfg\\frame.ini");
    frames_cfg.add_item("Frames", "frame", Utils::GlobalVars::frames);
    //frames_cfg.write();
    frames_cfg.read();

    /*printf("LOG: filename: %s, frame: %d, %d, %d, %d \n", Utils::GlobalVars::frames.at(1).filename.c_str()
            , Utils::GlobalVars::frames.at(1).frame.x
            , Utils::GlobalVars::frames.at(1).frame.y
            , Utils::GlobalVars::frames.at(1).frame.w
            , Utils::GlobalVars::frames.at(1).frame.h);*/

    Utils::Config sw_cfg(".\\cfg\\config.ini");

    sw_cfg.add_item("player", "cameraPos", Utils::GlobalVars::cameraPos);
    sw_cfg.add_item("player", "points", Utils::GlobalVars::currenPTS);
    sw_cfg.add_item("HallOfFame", "hi-score", Utils::GlobalVars::currenHiScore);
    //sw_cfg.write();
    sw_cfg.read();

    Initialization::Initializer* g = Initialization::Initializer::getInstance();
    if (!g->initGameObjs())
    {
        LOG(std::string("Initialization failed!"));
        delete g;
        SDL_Quit();
        throw std::runtime_error("Initialization failed");
    }

    Game::Game g_game(g);
    g_game.init();
    g_game.update(0.f);

    SDL_Rect menuRect = {Utils::GlobalVars::windowWidth/2, Utils::GlobalVars::windowHeight/2, 250, 250};
    menuRect.x -= menuRect.w/2;
    menuRect.y -= menuRect.h/2;

    Menu::Menu menu(g->drawing(), g->event(), g->renderer()->m_fonts[0]
                    , menuRect, {48, 48, 48, 255}
                    , {255, 255, 255, 255}, 45);

    menu.addOption("Start");
    menu.addOption("Options");
    menu.addOption("Exit");


    Uint64 previousTime = SDL_GetTicks64();
    //Loop
    while (!g->event()->logging())
    {
        Uint64 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        g->event()->manageGameVars(deltaTime);

        if (!Utils::GlobalVars::menuActive) {
            g_game.update(deltaTime);
            g_game.postUpdate(deltaTime);
        }
        else {
            // Update menu
            menu.handleEvent();

            // for our background if needed
            g->world()->update(deltaTime);
        }

        g->renderer()->beginScene();

        g_game.render(deltaTime);

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

    delete g;
    SDL_Quit();

    return 0;
}
