#ifndef BOSCONIAN_MENUVIEW_H
#define BOSCONIAN_MENUVIEW_H

#include "RenderEngine.h"
#include "../Utilities/Config.h"
#include "../Graphic/Fonts.h"
#include "../Model/Menus/MainMenu.h"
#include "../Model/Menus/PauseMenu.h"
#include "../Model/Menus/MainMenuOption.h"

class MenuView {
private:
    static MenuView* instance;

    MenuView() = default;
    ~MenuView() = default;

public:
    static MenuView* Instance() {
        if (!instance) {
            instance = new MenuView();
            return instance;
        }
        return instance;
    }

    void renderMain() {
        RenderEngine::Instance()->renderText(
                "Bosconian",
                {Config::windowCenterX, Config::titlePositionY},
                Config::ColorRed,
                Font::Type::JOYSTIX_128PX,
                TextAlign::CENTER);

        for (auto& item : MainMenu::Instance()->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            RenderEngine::Instance()->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }
    }

    void renderMainOption() {
        for (auto& item : MainMenuOption::Instance()->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            RenderEngine::Instance()->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }

        for (auto& item : MainMenuOption::Instance()->getSwitchItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            RenderEngine::Instance()->renderSwitchItem(item.second, color);
        }
    }

    void renderPause() {
        RenderEngine::Instance()->renderRectangle({325, 325}, {500, 500}, Config::ColorBlack, true);
        RenderEngine::Instance()->renderRectangle({325, 325}, {500, 500}, Config::ColorWhite);

        for (auto& item : PauseMenu::Instance()->getMenuItems()) {
            SDL_Color color = item.second.isHovered() ? Config::ColorRed : Config::ColorWhite;
            RenderEngine::Instance()->renderMenuItem(item.second, color, Font::Type::JOYSTIX_38PX);
        }
    }

};

#endif //BOSCONIAN_MENUVIEW_H