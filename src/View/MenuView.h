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
                Font::Type::JOYSTIX_128PX,
                true);

        for (auto& item : MainMenu::Instance()->getMenuItems()) {
            RenderEngine::Instance()->renderMenuItem(item.second,
             item.second.isHovered() ? Config::ColorRed : Config::ColorWhite,
             Font::Type::JOYSTIX_38PX);
        }
    }

};

#endif //BOSCONIAN_MENUVIEW_H