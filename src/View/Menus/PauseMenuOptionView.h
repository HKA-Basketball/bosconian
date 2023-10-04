#ifndef BOSCONIAN_PAUSEMENUOPTIONVIEW_H
#define BOSCONIAN_PAUSEMENUOPTIONVIEW_H

#include "MenuView.h"

#include "../../Model/Menus/PauseMenuOption.h"

class PauseMenuOptionView : public MenuView {
private:
    PauseMenuOption* menuModel;

public:
    PauseMenuOptionView(RenderEngine* renderEngine, PauseMenuOption* menuModel) : MenuView(renderEngine), menuModel(menuModel) {}

    void render() override {
        for (auto& item : menuModel->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }

        for (auto& item : *menuModel->getSwitchItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            renderEngine->renderSwitchItem(item.second, color);
        }
    }
};


#endif //BOSCONIAN_PAUSEMENUOPTIONVIEW_H
