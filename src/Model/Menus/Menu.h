#ifndef BOSCONIAN_MENU_H
#define BOSCONIAN_MENU_H

#include <map>

#include "MenuItem.h"

class Menu {
public:
    enum Option : uint32_t {
        NONE = 0,
        START,
        CONTINUE,
        OPTIONS,
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
    void reset() {
        clickedOption = NONE;
        isMouseButtonPressed = false;
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

#endif //BOSCONIAN_MENU_H