#ifndef BOSCONIAN_MENUITEM_H
#define BOSCONIAN_MENUITEM_H

#include <string>
#include <SDL.h>
#include "../../Utilities/Vector2D.h"

class MenuItem {
private:
    std::string text;
    SDL_FRect bounds;
    bool hovered;

public:
    MenuItem(const std::string& text, const SDL_FRect& bounds)
            : text(text), bounds(bounds), hovered(false) {}

    bool containsPoint(Vector2D mousePosition) const {
        SDL_FPoint point{mousePosition.x, mousePosition.y};
        return SDL_PointInFRect(&point, &bounds);
    }

    std::string getText() {
        return text;
    };

    SDL_FRect getBounds() {
        return bounds;
    };

    bool isHovered() {
        return hovered;
    }

    void setHovered(bool newHovered) {
        hovered = newHovered;
    }
};


#endif //BOSCONIAN_MENUITEM_H
