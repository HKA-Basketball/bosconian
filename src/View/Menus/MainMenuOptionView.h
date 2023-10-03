#ifndef BOSCONIAN_MAINMENUOPTIONVIEW_H
#define BOSCONIAN_MAINMENUOPTIONVIEW_H

#include "MenuView.h"
#include "../../Model/Menus/MainMenuOption.h"

class MainMenuOptionView : public MenuView {
private:
    MainMenuOption* mainMenuOption;

public:
    MainMenuOptionView(RenderEngine* renderEngine, MainMenuOption* mainMenuOption) :
        MenuView(renderEngine), mainMenuOption(mainMenuOption) {}

    void render() override {
        for (auto& item : mainMenuOption->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }

        for (auto& item : *mainMenuOption->getSwitchItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderSwitchItem(item.second, color);
        }
    }

};

#endif //BOSCONIAN_MAINMENUOPTIONVIEW_H
