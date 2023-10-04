#ifndef BOSCONIAN_MENU_H
#define BOSCONIAN_MENU_H

#include <map>

#include "Items/MenuItem.h"

class Menu {
public:
    enum Option {
        NONE,
        START,
        CONTINUE,
        MAIN_MENU,

        OPTIONS,
        SWA,
        SWB,
        DEBUG,
        CUSTOMLEVELS,

        EXIT
    };

protected:
    std::map<Option, MenuItem> menuItems;

    Option clickedOption{NONE};

    Vector2D mousePosition;
    bool isMouseButtonPressed{false};

    Menu() = default;
    ~Menu() = default;

public:
    virtual void update() {
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
        Option currentClickedOption = clickedOption;
        clickedOption = NONE;
        return currentClickedOption;
    }

};

#endif //BOSCONIAN_MENU_H
