#ifndef BOSCONIAN_PAUSEMENUVIEW_H
#define BOSCONIAN_PAUSEMENUVIEW_H

#include "MenuView.h"

#include "../../Model/Menus/PauseMenu.h"

class PauseMenuView : public MenuView {
private:
    PauseMenu* pauseMenu;

public:
    PauseMenuView(RenderEngine* renderEngine, PauseMenu* pauseMenu) : MenuView(renderEngine), pauseMenu(pauseMenu) {}

    void render() override {
        renderEngine->renderRectangle({Config::pauseBoxPositionX, Config::pauseBoxPositionY},
              {Config::pauseBoxWidth, Config::pauseBoxHeight}, Config::ColorDarkGrey, true);
        renderEngine->renderRectangle({Config::pauseBoxPositionX, Config::pauseBoxPositionY},
              {Config::pauseBoxWidth, Config::pauseBoxHeight}, Config::ColorLightGrey);

        renderEngine->renderText("Pause", {Config::pausePositionX, Config::pausePositionY},
                Config::ColorRed, Font::Type::JOYSTIX_64PX, TextAlign::CENTER);

        for (auto& item : pauseMenu->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }
    }
};


#endif //BOSCONIAN_PAUSEMENUVIEW_H
