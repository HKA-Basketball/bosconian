#ifndef BOSCONIAN_MAINMENUVIEW_H
#define BOSCONIAN_MAINMENUVIEW_H

#include "MenuView.h"
#include "../../Model/Menus/MainMenu.h"

class MainMenuView : public MenuView {
private:
    MainMenu* mainMenu;

public:
    MainMenuView(RenderEngine* renderEngine, MainMenu* mainMenu) : MenuView(renderEngine), mainMenu(mainMenu) {}

    void render() override {
        renderEngine->renderText(
                "Bosconian",
                {Config::windowCenterX, Config::titlePositionY},
                Config::ColorRed,
                Font::Type::JOYSTIX_128PX,
                TextAlign::CENTER);

        for (auto& item : mainMenu->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }
    }
};


#endif //BOSCONIAN_MAINMENUVIEW_H
