#ifndef BOSCONIAN_SWITCHITEM_H
#define BOSCONIAN_SWITCHITEM_H

#include <string>
#include <vector>

#include <SDL.h>
#include "../../../Utilities/Vector2D.h"

class SwitchItem {
private:
    const float SWITCH_SPACE = 2;

    std::vector<bool> switches; // Each element represents a switch (true: active, false: inactive)
    std::vector<SDL_FRect> switchBounds; // Bounding box for each switch
    std::string text; // Text to render over the middle of the switches
    SDL_FRect textBounds;
    bool hovered{false};

public:
    SwitchItem(size_t numSwitches, const Vector2D& position, const Vector2D& switchSize, const std::string& text = "")
            : switches(numSwitches, false), text(text) {
        for (size_t i = 0; i < numSwitches; ++i) {
            SDL_FRect switchBound;
            switchBound.x = position.x + i * (switchSize.x + SWITCH_SPACE);
            switchBound.y = position.y;
            switchBound.w = switchSize.x;
            switchBound.h = switchSize.y;
            switchBounds.push_back(switchBound);
        }

        textBounds.x = switchBounds.front().x;
        textBounds.y = switchBounds.front().y - switchBounds.front().h;
        textBounds.w = switchBounds.back().x + switchBounds.back().w - switchBounds.front().x;
        textBounds.h = switchBounds.front().h; // Assuming all switches have the same height
    }

    int containsPoint(const Vector2D& mousePosition) const {
        SDL_FPoint point{mousePosition.x, mousePosition.y};
        for (size_t i = 0; i < switchBounds.size(); ++i) {
            if (SDL_PointInFRect(&point, &switchBounds[i])) {
                return static_cast<int>(i);
            }
        }
        return -1; // No switch contains the point
    }

    void toggleSwitch(size_t index) {
        if (index < switches.size()) {
            switches[index] = !switches[index];
        }
    }

    int getState() const {
        int state = 0;
        for (size_t i = 0; i < switches.size(); ++i) {
            if (switches[i]) {
                state |= (1 << i);
            }
        }
        return state;
    }

    std::string getText() const {
        return text;
    }

    bool isHovered() const {
        return hovered;
    }

    void setHovered(bool newHovered) {
        hovered = newHovered;
    }

    size_t getNumSwitches() const {
        return switches.size();
    }

    std::vector<SDL_FRect> getSwitchBounds() const {
        return switchBounds;
    }

    SDL_FRect getTextBounds() const {
        return textBounds;
    }
};

#endif //BOSCONIAN_SWITCHITEM_H
