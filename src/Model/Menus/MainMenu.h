#ifndef BOSCONIAN_MAINMENU_H
#define BOSCONIAN_MAINMENU_H

#include <vector>
#include <map>
#include <SDL.h>
#include "MenuItem.h"

#include "../../Utilities/Config.h"
#include "../../Utilities/Vector2D.h"

class MainMenu {
public:
    enum Option : uint32_t {
        NONE = 0,
        START,
        EXIT
    };

private:
    static MainMenu* instance;

    std::map<Option, MenuItem> menuItems = {
            {START, {"Start", SDL_FRect{Config::titlePositionX, 550, 500, 20}}}
    };

    Option clickedOption{NONE};

    Vector2D mousePosition;
    bool isMouseButtonPressed{false};

    MainMenu() = default;
    ~MainMenu() = default;

public:
    static MainMenu* Instance() {
        if (!instance) {
            instance = new MainMenu();
            return instance;
        }
        return instance;
    }

    void update() {
        clickedOption = NONE;

        for (auto& item : menuItems) {
            bool isHovered = item.second.containsPoint(mousePosition);

            item.second.setHovered(isHovered);

            if(isHovered && isMouseButtonPressed) {
                clickedOption = item.first;
            }
        }
    }

    void handleHover(const Vector2D& newMousePosition) {
        mousePosition = newMousePosition;
    }

    void handleClick(bool clicked) {
        isMouseButtonPressed = clicked;
    }

    std::map<Option, MenuItem> getMenuItems() {
        return menuItems;
    }

    Option getClickedOption() {
        return clickedOption;
    }
};


#endif //BOSCONIAN_MAINMENU_H
