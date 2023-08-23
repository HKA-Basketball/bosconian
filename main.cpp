#include <fileapi.h>

#include "./src/Utilities/Initializer.h"
#include "./src/Game/Game.h"
#include "./src/GUI/Menu.h"
#include "src/GUI/DipSwitch.h"

int main(int argc, char* args[])
{
    CreateDirectoryA(".\\Logs", NULL);
    CreateDirectoryA(".\\cfg", NULL);

    Utils::Config lvl_cfg(".\\cfg\\level.ini");
    lvl_cfg.add_item("Levels", "levels", Utils::GlobalVars::lvlsInfos);
    //lvl_cfg.write();
    lvl_cfg.read();

    /*printf("LOG: lvlNum: %d, baseShipsPos: %f, %f, playerPos: %f, %f \n", Utils::GlobalVars::lvlsInfos.at(0).lvlNum
           , Utils::GlobalVars::lvlsInfos.at(0).baseShipsPos.at(0).x
           , Utils::GlobalVars::lvlsInfos.at(0).baseShipsPos.at(0).y
           , Utils::GlobalVars::lvlsInfos.at(0).playerPos.x
           , Utils::GlobalVars::lvlsInfos.at(0).playerPos.y);*/

    Utils::Config frames_cfg(".\\cfg\\frame.ini");
    frames_cfg.add_item("Frames", "frames", Utils::GlobalVars::frames);
    //frames_cfg.write();
    frames_cfg.read();

    /*for (auto& in : Utils::GlobalVars::frames) {
        printf("LOG: filename: %s, frame: %d, %d, %d, %d \n", in.filename.c_str()
                , in.frame.x
                , in.frame.y
                , in.frame.w
                , in.frame.h);
    }*/

    Utils::Config sw_cfg(".\\cfg\\config.ini");

    int frameCap = 0;
    sw_cfg.add_item("Settings", "max-fps", frameCap);
    //sw_cfg.write();
    sw_cfg.read();

    Init::Initializer* init = Init::Initializer::getInstance();
    if (!init->initGameObjs())
    {
        LOG(std::string("Init failed!"));
        SDL_Quit();
        throw std::runtime_error("Init failed");
    }

    Game::Game g_game;
    g_game.init();
    g_game.update(0.f);

    SDL_Rect menuRect = {Utils::GlobalVars::windowWidth/2, Utils::GlobalVars::windowHeight/2, 350, 250};
    menuRect.x -= menuRect.w/2;
    menuRect.y -= menuRect.h/2;

    Menu::Menu menu(Renderer::g_renderer->m_fonts[0]
                    , menuRect, {148, 148, 148, 255}
                    , {255, 255, 255, 255}, 45);

    Menu::DipSwitch swa(Renderer::g_renderer->m_fonts[0], "SWA", 200, 200, {&Utils::PlayOptions::swa_0, &Utils::PlayOptions::swa_1, &Utils::PlayOptions::swa_2, &Utils::PlayOptions::swa_3, &Utils::PlayOptions::swa_4, &Utils::PlayOptions::swa_5, &Utils::PlayOptions::swa_6, &Utils::PlayOptions::swa_7});
    Menu::DipSwitch swb(Renderer::g_renderer->m_fonts[0], "SWB", 600, 200, {&Utils::PlayOptions::swb_0, &Utils::PlayOptions::swb_1, &Utils::PlayOptions::swb_2, &Utils::PlayOptions::swb_3, &Utils::PlayOptions::swb_4, &Utils::PlayOptions::swb_5, &Utils::PlayOptions::swb_6, &Utils::PlayOptions::swb_7});
    Menu::DipSwitch db(Renderer::g_renderer->m_fonts[0], "Debug Mode", 200, 400, {&Utils::GlobalVars::debugMode});

    menu.addOption("Start", []() {
        Utils::GlobalVars::menuActive = false;
    });
    menu.addOption("Restart", [&g_game]() {
        g_game.init();
        g_game.update(0.f);
    });
    menu.addOption("Level Editor", []() {
        Utils::GlobalVars::lvlEditorActive = !Utils::GlobalVars::lvlEditorActive;
    });
    menu.addOption("Options", []() {
        Utils::GlobalVars::dipSwitchActive = !Utils::GlobalVars::dipSwitchActive;
    });
    menu.addOption("Exit", []() {
        Utils::GlobalVars::need2ExitProc = true;
    });


    Uint64 previousTime = SDL_GetTicks64();
    //Loop
    while (!Event::g_event->logging())
    {
        Uint64 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        Event::g_event->manageGameVars(deltaTime);

        if (!Utils::GlobalVars::menuActive) {
            g_game.update(deltaTime);
            g_game.postUpdate(deltaTime);
        }
        else {
            // Update menu
            if (Utils::GlobalVars::dipSwitchActive) {
                swa.handleEvent();
                swb.handleEvent();
                db.handleEvent();

                Utils::PlayOptions::updateSettings();

                if (Event::g_event->isKeyClicked(SDL_SCANCODE_ESCAPE, true)) {
                    Utils::GlobalVars::dipSwitchActive = false;
                    /*printf("LOG: lives: %d, conage: %d, bonusFighter: %d, difficulty: %d \n", Utils::PlayOptions::lives
                            , Utils::PlayOptions::conage
                            , Utils::PlayOptions::bonusFighter
                            , Utils::PlayOptions::difficulty);*/
                }
            }
            else
                menu.handleEvent();

            // for our background if needed
            Game::g_world->update(deltaTime);
        }

        Renderer::g_renderer->beginScene();

        g_game.render(deltaTime);

        if (Utils::GlobalVars::menuActive) {
            // Render Menu
            menu.render();

            if (Utils::GlobalVars::dipSwitchActive) {
                swa.render();
                swb.render();
                db.render();
            }
        }

        Renderer::g_renderer->endScene();

        if (frameCap > 0) {
            Uint32 frameTime = SDL_GetTicks64() - currentTime;
            if (frameTime < 1000 / frameCap) {
                SDL_Delay((1000 / frameCap) - frameTime);
            }
        }
    }

    delete init;
    SDL_Quit();

    return 0;
}
