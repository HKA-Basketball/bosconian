#ifndef BOSCONIAN_PAUSEMENU_H
#define BOSCONIAN_PAUSEMENU_H

#include "Menu.h"

#include "../../Utilities/Config.h"
#include "../../Utilities/Vector2D.h"

class PauseMenu : public Menu {
public:
    PauseMenu() {
        menuItems = {
                {CONTINUE, {"Continue", {Config::titlePositionX, 350}, {250, 30}, true}},
                {OPTIONS, {"Options", {Config::titlePositionX, 400}, {220, 30}, true}},
                {EXIT, {"Exit", {Config::titlePositionX, 450}, {140, 30}, true}}
        };
    };

    ~PauseMenu() = default;
};


#endif //BOSCONIAN_PAUSEMENU_H
