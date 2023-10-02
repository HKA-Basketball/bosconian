#ifndef BOSCONIAN_MENUITEM_H
#define BOSCONIAN_MENUITEM_H

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "../../../Utilities/Vector2D.h"

class MenuItem {
private:
    std::string text;
    SDL_FRect bounds;
    bool centered;
    bool hovered;

public:
    MenuItem(const std::string& text, const Vector2D& position, const Vector2D& size, bool centered = false)
            : text(text), centered(centered), hovered(false) {
        bounds.x = position.x;
        bounds.y = position.y;
        bounds.w = size.x;
        bounds.h = size.y;
    }

    bool containsPoint(const Vector2D& mousePosition) const {
        SDL_FPoint point{mousePosition.x, mousePosition.y};

        if(centered) {
            point.x = point.x + (bounds.w/2);
            point.y = point.y + (bounds.h/2);
        }

        return SDL_PointInFRect(&point, &bounds);
    }

    std::string getText() const {
        return text;
    };

    SDL_FRect getBounds() const {
        return bounds;
    };

    bool isCentered() const {
        return centered;
    }

    bool isHovered() const {
        return hovered;
    }

    void setHovered(bool newHovered) {
        hovered = newHovered;
    }
};


#endif //BOSCONIAN_MENUITEM_H
