#ifndef BOSCONIAN_MENUVIEW_H
#define BOSCONIAN_MENUVIEW_H

#include "RenderEngine.h"
#include "../Utilities/Config.h"
#include "../Graphic/Fonts.h"
#include "../Model/Menus/MainMenu.h"

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

    void render() {
        RenderEngine::Instance()->renderText(
                "Bosconian",
                {Config::titlePositionX, Config::titlePositionY},
                Config::ColorRed,
                Font::JOYSTIX_128PX,
                true);

        for (auto& item : MainMenu::Instance()->getMenuItems()) {
            SDL_FRect rect = item.second.getBounds();
            RenderEngine::Instance()->renderText(
                    item.second.getText(),
                    {rect.x, rect.y},
                    item.second.isHovered() ? Config::ColorRed : Config::ColorWhite,
                    Font::JOYSTIX_38PX,
                    true);
        }
    }

};

#endif //BOSCONIAN_MENUVIEW_H